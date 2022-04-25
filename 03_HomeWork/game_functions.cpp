#include "game_functions.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

// Функция генерирует и возвращает случайное число, ограниченное max_value.
int get_random_number(int max_value)
{
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	const int random_value = std::rand() % max_value;

	return random_value;
}

// Функция проводит игру и возвращает кол-во попыток угадать число.
int play_game(int guess_value)
{
	int current_value = 0;
	int tries_number = 0;

	std::cout << "Enter your guess:" << std::endl;

	do {
		std::cin >> current_value;

		if (std::cin.fail()) {
			// Очищаем буфер ввода от ошибки.
			std::cin.clear();
			std::cin.ignore(32767, '\n');

			std::cout << "Bad value! Please, enter correct value:" << std::endl;
			continue;
		}

		tries_number++;

		if (current_value < guess_value) {
			std::cout << "Your value is less than" << std::endl;
		}
		else if (current_value > guess_value) {
			std::cout << "Your value is greater than" << std::endl;
		}
		else {
			std::cout << "You win! Attempts: " << tries_number << std::endl;
			break;
		}

	} while (true);

	return tries_number;
}