cmake_minimum_required(VERSION 3.5)

project(06.homework)

add_executable(sl_containers
    main.cpp
    "serial_container.h" "serial_container.cpp" "one_way_list_container.h" "one_way_list_container.cpp" "two_way_list_container.h" "two_way_list_container.cpp")

set_target_properties(sl_containers PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


