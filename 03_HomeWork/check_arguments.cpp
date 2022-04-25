#include "check_arguments.h"

#include <iostream>
#include <string>

// Функция проверяет корректность переданных аргументов.
bool check_arguments(int args_number, const char** arguments)
{
	// Программа запущена без параметров.
	if (args_number == 1) {
		return true;
	}

	// Слишком много параметров.
	if (args_number > 3) {
		std::cout << "Too many arguments!" << std::endl;
		return false;
	}

	std::string arg1_value{ arguments[1]};
	
	// Анализ имени первого аргумента.
	if (arg1_value != "-max") {
		if (arg1_value != "-level") {
			if (arg1_value != "-table") {
				std::cout << "The first argument is NOT correct: " << arg1_value << std::endl;
				return false;
			}
		}
	}

	// Проверка -table
	if (arg1_value == "-table") {
		if (args_number == 2) {
			return true;
		}

		std::cout << "Argument -table doesn't need more arguments" << std::endl;
		return false;
	}

	// Проверка -max и -level
	if (args_number != 3) {
		std::cout << "Too few arguments!" << std::endl;
		return false;
	}


	int digital_value = 0;

	digital_value = std::stoi(arguments[2]);

	if (digital_value == 0) {
		std::cout << "Argument " << arguments[2] << " is NOT correct!" << std::endl;
		return false;
	}

	// Дополнительная проверка числа, если первый аргумента -level
	if (arg1_value == "-level") {
		if (digital_value > 3) {
			std::cout << "Level argument cannot be greater than 3! Your value: " << digital_value << std::endl;
			return false;
		}
	}

	return true;
}

// Функция определяет вид игры.
GameType get_game_type(int args_number, const char** arguments, int& second_value)
{
	// Сначала проверяется корректность переданных параметров.
	if (!check_arguments(args_number, arguments)) {
		return GameType::UnknownType;
	}

	if (args_number == 1) {
		return GameType::SimpleGame;
	}

	std::string arg1_value{ arguments[1] };

	if (arg1_value == "-table") {
		return GameType::OnlyTable;
	}

	second_value = std::stoi(arguments[2]);

	if (arg1_value == "-max") {
		return GameType::WithMaxNumber;
	}

	return GameType::WithLevel;
}