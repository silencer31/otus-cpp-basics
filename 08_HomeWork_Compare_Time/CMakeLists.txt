cmake_minimum_required(VERSION 3.5)

project(08.homework_compare_time)

add_executable(topk_words
    "count_and_compare.cpp"
     "extra_functions.h" "extra_functions.cpp" "extra_data.h" "count_functions.h" "count_one_thred.cpp" "count_with_mutex.cpp" "count_sum_map.cpp")


set_target_properties(topk_words PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

