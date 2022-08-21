#include "extra_functions.h"

#include <iostream>
#include <string.h>

// Является ли число четным.
bool is_even(const int value)
{
    if ( value % 2 == 0) {
        return true;
    }

    return false;
}

// Читаем размер поля, переданный пользователем.
unsigned int read_user_size(int params_number, char *params_array[])
{
    if (params_number != 3) {
        std::cout << "Incorrect number of parameters" << std::endl;
        return 0;
    }

    if ( strncmp( *(params_array+1), "-l", 2) != 0) {
        std::cout << "Unknown parameter: " << *(params_array+1) << std::endl;
        return 0;
    }

    int value = 0;
    value = atoi( *(params_array+2));

    if ( value <= 0) {
        std::cout << "Incorrect size value: " << *(params_array+2) << std::endl;
        return 0;
    }

    return static_cast<unsigned int>(value);
}
