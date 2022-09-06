// Read files and prints top k word by frequency

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <chrono>

#include <thread>
#include <mutex>


const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string& str);

void count_words(std::istream& stream, Counter& counter);

void print_topk(std::ostream& stream, const Counter&, const size_t k);

bool dictionary_contains(Counter* cnt_ptr, const std::string& str); // Содержит ли коллекция map переданный ключ.


// Вариант программы без мьютекса и со сложением отдельных словарей.


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now(); // Время начала подсчета.
       
    std::vector<std::thread> counting_threads; // Потоки для подсчета слов.
    std::vector<std::ifstream*> input_stream_ptrs; // Указатели на потоки чтения.
    std::vector<Counter*> counter_ptrs;


    unsigned int threads_number = 0; // Для подсчета кол-ва потоков, которые удалось запустить.

    for (int i = 1; i < argc; ++i) {
        std::ifstream* f = nullptr;
        f = new std::ifstream(argv[i]);

        Counter* ctr_ptr = nullptr;
        ctr_ptr = new Counter;

        if ((f != nullptr) && (f->is_open()) && (ctr_ptr != nullptr)) {
            counter_ptrs.emplace_back(ctr_ptr);
            input_stream_ptrs.emplace_back(f);
            counting_threads.emplace_back(count_words, ref(*f), ref(*ctr_ptr));
            ++threads_number;
        }
        else {
            std::cerr << "Failed to open file " << argv[i] << '\n';
        }
    }

    if (threads_number == 0) {
        std::cout << "EXIT FAILURE" << std::endl;
        return EXIT_FAILURE;
    }


    for (auto& thread_item : counting_threads) {
        thread_item.join();
    }

    for (auto& isptr : input_stream_ptrs) {
        delete isptr;
    }

    Counter final_dictionary; // Результирующий словарь.

    // Создание результирующего словаря.
    for (auto& cntptr : counter_ptrs) {
        if (final_dictionary.empty()) {
            final_dictionary.merge(*cntptr);
        }
        else {
            for (std::map<std::string, std::size_t>::iterator it = cntptr->begin(); it != cntptr->end(); ++it) {
                /* Такой вариант работает слишком долго, что не удивительно.
                
                if (dictionary_contains(cntptr, it->first)) {
                    final_dictionary[it->first] = final_dictionary[it->first] + it->second;
                }
                else {
                    final_dictionary[it->first] = it->second;
                }*/

                // Хотел использовать метод contains у std::map, но он совсем новый и решил сделать через исключения. 

                try {
                    if (final_dictionary.at(it->first) != 0) {
                        final_dictionary[it->first] = final_dictionary.at(it->first) + it->second;
                    }
                }
                catch (std::out_of_range) {
                    final_dictionary[it->first] = it->second;
                 }
            }
        }

        delete cntptr;
    }

    print_topk(std::cout, final_dictionary, TOPK); // Печать результатов подсчета.

    auto end = std::chrono::high_resolution_clock::now(); // Время окончания подсчета.
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // Вычисление времени, потраченного на подсчет.

    std::cout << "Elapsed time is " << elapsed_ms.count() << " ms\n";
}

std::string tolower(const std::string& str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
        std::back_inserter(lower_str),
        [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

void count_words(std::istream& stream, Counter& counter) {
    std::for_each(std::istream_iterator<std::string>(stream),
        std::istream_iterator<std::string>(),
        [&counter](const std::string& s)
        {
            ++counter[tolower(s)];
        });
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {

    // На случай если подсунули пустой текстовый файл.
    if (counter.size() == 0) return;

    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto& rhs) { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator& pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                << '\n';
        });
}

// Содержит ли коллекция map переданный ключ.
bool dictionary_contains(Counter* cnt_ptr, const std::string& str)
{
    for (std::map<std::string, std::size_t>::iterator it = cnt_ptr->begin(); it != cnt_ptr->end(); ++it) {
        if (it->first == str) {
            return true;
        }
    }

    return false;
}