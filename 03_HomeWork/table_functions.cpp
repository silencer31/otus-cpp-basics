#include "table_functions.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

const std::string high_scores_filename = "high_scores.txt";

namespace fs = std::filesystem;

// Функция вывода в консоль таблицы с рекордами.
bool output_records_table()
{
	// Проверяем наличие файла с рекордами.
	std::ifstream in_file{ high_scores_filename };
	if (!in_file.is_open()) {
		std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
		return false;
	}

	std::string user_name;
	int number;

	std::vector<std::string> names; // Имена.
	std::vector<int> attempts;      // Рекорды.

	// Читаем файл с рекордами, запоминая только записи с лучшими рекордами.
	while (true) {
		// Read the username first
		in_file >> user_name;
		// Read the high score next
		in_file >> number;
		// Ignore the end of line symbol
		in_file.ignore();

		// Проверяем, была ли уже прочитана запись с таким же именем.
		if (std::find(names.begin(), names.end(), user_name) != names.end()) { // Запись с таким именем уже есть.
			for (int i = 0; i < names.size(); ++i) {
				if (names.at(i) == user_name) {
					if (attempts.at(i) > number) {
						attempts[i] = number; // Заменяем на лучшее значение.
					}
					break;
				}
			}
		}
		else { // Записи с таким именем ещё нет.
			names.push_back(user_name);
			attempts.push_back(number);
		}

		if (in_file.fail()) {
			break;
		}
	}

	// Выводим таблицу.
	std::cout << "High scores table :" << std::endl;

	// Print the information to the screen
	for (int i = 0; i < names.size(); ++i) {
		std::cout << names.at(i) << '\t' << attempts.at(i) << std::endl;
	}

	return true;
}


// Функция записи в файл с рекордами.
bool make_table_record(std::string& player_name, int new_number)
{
	// Открываем на запись или создаём файл с рекордами.
	std::fstream io_file{ high_scores_filename, std::ios_base::in | std::ios_base::out | std::fstream::app };
	if (!io_file.is_open()) {
		std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
		return false;
	}

	std::string user_name;
	int rec_number;

	auto pos = io_file.tellg(); // Для запоминания позиции в файле.
	bool record_found = false; // Есть ли уже в файле запись с именем player_name
	bool new_value_is_better = false; // Флаг того, что новое значение лучше того, что уже есть в файле.

	// Читаем файл и проверяем, есть ли в нём запись с именем player_name
	while (true) {
		pos = io_file.tellg();

		// Read the username first
		io_file >> user_name;
		// Read the high score next
		io_file >> rec_number;
		// Ignore the end of line symbol
		io_file.ignore();

		if (user_name == player_name) {
			record_found = true;

			if (new_number < rec_number) {
				new_value_is_better = true;
			}

			break;
		}

		if (io_file.fail()) {
			break;
		}
	}

	// Записей с таким именем нет. Просто дописываем новую запись в конец.
	if ( !record_found) { 
		io_file.clear();

		// Append new results to the table:
		io_file << player_name << ' ';
		io_file << new_number;
		io_file << std::endl;
		return true;
	}

	// Запись найдена, но старая запись лучше новой. Просто выходим.
	if (!new_value_is_better) {
		return true;
	}

	std::vector<std::string> names; // Имена.
	std::vector<int> attempts;      // Рекорды.

	while (!io_file.fail()) { // Читаем и запоминаем оставшуюся часть файла.
		io_file >> user_name;
		io_file >> rec_number;
		io_file.ignore();
		names.push_back(user_name);
		attempts.push_back(rec_number);
	}

	io_file.clear();
	
	fs::resize_file(high_scores_filename, pos); // Урезаем размер файла до места, на котором нашли запись, требующую замены.

	// Вновь записываем в файл всё то, что было после найденной записи.
	for (int i = 0; i < names.size(); ++i) {
		io_file << names.at(i) << ' ';
		io_file << attempts.at(i);
		io_file << std::endl;
	}

	// В конце добавляем запись с новым рекордом.
	io_file << player_name << ' ';
	io_file << new_number;
	io_file << std::endl;
	return true;
}