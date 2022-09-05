cmake_minimum_required(VERSION 3.5)

project(08.homework)

add_executable(topk_words
    main.cpp
    )

set_target_properties(topk_words PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


