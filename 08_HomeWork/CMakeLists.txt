cmake_minimum_required(VERSION 3.5)

project(08.homework)

add_executable(topk_words_mutex
    "count_with_mutex.cpp"
    )

add_executable(topk_words_sum_maps
    "count_sum_maps.cpp"
    )

set_target_properties(topk_words_mutex PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(topk_words_sum_maps PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


