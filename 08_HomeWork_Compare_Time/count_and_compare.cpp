// Read files and prints top k word by frequency


#include <cctype>
#include <cstdlib>


#include "extra_data.h"
#include "extra_functions.h"
#include "count_functions.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    long long time_one_thread = 0;
    long long time_mutex = 0;
    long long time_sum_map = 0;

    int result = 0;

    // Чтение файлов в одном потоке.
    result = count_one_thread(argc, argv, time_one_thread);

    // Чтение файлов в нескольких потоках с мьютексом.
    result = count_with_mutex(argc, argv, time_mutex);

    // Чтение файлов в нескольких независимых потоках 
    result = count_sum_map(argc, argv, time_sum_map);

    std::cout << "Time elapsed in one thread " << time_one_thread << " us\n";
    std::cout << "Time elapsed with mutex    " << time_mutex << " us\n";
    std::cout << "Time elapsed with sum map  " << time_sum_map << " us\n";
}

