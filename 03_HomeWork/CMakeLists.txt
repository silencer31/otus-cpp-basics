cmake_minimum_required(VERSION 3.10)

project(03.guess_value)

add_executable(guess_value 
    main.cpp
 "game_functions.h" "game_functions.cpp" "check_arguments.h" "check_arguments.cpp" "table_functions.h" "table_functions.cpp")

set_target_properties(guess_value PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

install(TARGETS guess_value)