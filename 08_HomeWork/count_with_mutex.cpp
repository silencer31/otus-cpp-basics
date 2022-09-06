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

std::string tolower(const std::string &str);

void count_words( std::istream& stream, Counter& counter, std::mutex& mtx);

void print_topk(std::ostream& stream, const Counter&, const size_t k);

// Вариант программы с мьютексом для словаря.

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now(); // Время начала подсчета.
    
    Counter the_only_dictionary; // Единственный словарь
    std::mutex dictionary_mtx; // Mutex для синхронизации внесения изменений в словарь.

    std::vector<std::thread> counting_threads; // Потоки для подсчета слов.
    std::vector<std::ifstream*> input_stream_ptrs; // Указатели на потоки чтения.
    
    unsigned int threads_number = 0; // Для подсчета кол-ва потоков, которые удалось запустить.
    
    for (int i = 1; i < argc; ++i) {
        std::ifstream* f = nullptr;
        f = new std::ifstream(argv[i]);

        if ( (f != nullptr) && (f->is_open())) {
            input_stream_ptrs.emplace_back(f);
            counting_threads.emplace_back(count_words, ref(*f), ref(the_only_dictionary), ref(dictionary_mtx));
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
    
    print_topk(std::cout, the_only_dictionary, TOPK); // Печать результатов подсчета.
   
    auto end = std::chrono::high_resolution_clock::now(); // Время окончания подсчета.
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // Вычисление времени, потраченного на подсчет.
    
    std::cout << "Elapsed time is " << elapsed_ms.count() << " ms\n";
}

std::string tolower(const std::string &str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

void count_words(std::istream& stream, Counter& counter, std::mutex& mtx) {
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter, &mtx](const std::string &s) 
        { 
            mtx.lock();
            ++counter[tolower(s)]; 
            mtx.unlock();
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
        [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });
    
    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                      << '\n';
        });
}