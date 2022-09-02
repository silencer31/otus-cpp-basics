cmake_minimum_required(VERSION 3.2)

project(07.homework)

# Lookup for pre-built gtest
find_package(GTest)

# Main target
add_executable(
    sl_containers
    src/main.cpp
    src/serial_container.h
    src/serial_container.cpp
    src/one_way_list_container.h
    src/one_way_list_container.cpp
    src/two_way_list_container.h
    src/two_way_list_container.cpp
)

# Test target
add_executable(
    containers_tests
    test/serial_container_tests.cpp
    test/two_way_list_tests.cpp
)

# Add src to the include directories for the test target
target_include_directories(
    containers_tests PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
# Add googletest to the include directories for the test target
target_include_directories(
    containers_tests PRIVATE
    ${GTEST_INCLUDE_DIRS}
)

# Link test target against gtest libraries
target_link_libraries(
    containers_tests PRIVATE
    ${GTEST_BOTH_LIBRARIES}
)

if (MSVC)
    target_compile_options(
        sl_containers PRIVATE
        /W4
    )
    target_compile_options(
        containers_tests PRIVATE
        /W4
    )
else ()
    target_compile_options(
        sl_containers PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(
        containers_tests PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()