#include "random_number.h"

#include <cstdlib>
#include <ctime>

// Функция генерирует и возвращает случайное число, ограниченное max_value.
int get_random_number(int max_value)
{
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	const int random_value = std::rand() % max_value;

	return random_value;
}