#include <iostream>
#include <string>

#include "check_arguments.h"
#include "game_functions.h"
#include "table_functions.h"

const int default_max_value = 100; // �������� �� ���������.

int main(int argc, char** argv)
{
	int second_value;
	int guess_value = 0;

	GameType game_type = get_game_type(argc, (const char**)argv, second_value);
	
	switch (game_type) {
	case GameType::UnknownType:
		return -1; // ��������� ��������� � �������.
		break;
	case GameType::SimpleGame:
		guess_value = get_random_number(default_max_value); 
		break;
	case GameType::WithMaxNumber:
		guess_value = get_random_number(second_value);
		break;
	case GameType::WithLevel: {
		if (second_value == 1) {
			second_value = 10;
		}
		else if (second_value == 2) {
			second_value = 50;
		}
		else {
			second_value = 100;
		}

		guess_value = get_random_number(second_value);
		}
		break;
	case GameType::OnlyTable:
		if (!output_records_table()) { // ������� � ������� �������.
			return -1;
		}
 
		return 0;
		break;
	default:
		return -1;
		break;
	}

	std::cout << "value:" <<guess_value << std::endl;

	// ������ ����� ������.
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;

	// �������� ����.
	int tries_number = play_game(guess_value);

	// ������ ������ � �������.
	if ( !make_table_record(user_name, tries_number)) {
		return -1;
	}

	// ������� � ������� �������.
	if ( !output_records_table()) {
		return -1;
	}

	return 0;
}