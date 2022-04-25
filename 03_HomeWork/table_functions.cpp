#include "table_functions.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

const std::string high_scores_filename = "high_scores.txt";

namespace fs = std::filesystem;

// ������� ������ � ������� ������� � ���������.
bool output_records_table()
{
	// ��������� ������� ����� � ���������.
	std::ifstream in_file{ high_scores_filename };
	if (!in_file.is_open()) {
		std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
		return false;
	}

	std::string user_name;
	int number;

	std::vector<std::string> names; // �����.
	std::vector<int> attempts;      // �������.

	// ������ ���� � ���������, ��������� ������ ������ � ������� ���������.
	while (true) {
		// Read the username first
		in_file >> user_name;
		// Read the high score next
		in_file >> number;
		// Ignore the end of line symbol
		in_file.ignore();

		// ���������, ���� �� ��� ��������� ������ � ����� �� ������.
		if (std::find(names.begin(), names.end(), user_name) != names.end()) { // ������ � ����� ������ ��� ����.
			for (int i = 0; i < names.size(); ++i) {
				if (names.at(i) == user_name) {
					if (attempts.at(i) > number) {
						attempts[i] = number; // �������� �� ������ ��������.
					}
					break;
				}
			}
		}
		else { // ������ � ����� ������ ��� ���.
			names.push_back(user_name);
			attempts.push_back(number);
		}

		if (in_file.fail()) {
			break;
		}
	}

	// ������� �������.
	std::cout << "High scores table :" << std::endl;

	// Print the information to the screen
	for (int i = 0; i < names.size(); ++i) {
		std::cout << names.at(i) << '\t' << attempts.at(i) << std::endl;
	}

	return true;
}


// ������� ������ � ���� � ���������.
bool make_table_record(std::string& player_name, int new_number)
{
	// ��������� �� ������ ��� ������ ���� � ���������.
	std::fstream io_file{ high_scores_filename, std::ios_base::in | std::ios_base::out | std::fstream::app };
	if (!io_file.is_open()) {
		std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
		return false;
	}

	std::string user_name;
	int rec_number;

	auto pos = io_file.tellg(); // ��� ����������� ������� � �����.
	bool record_found = false; // ���� �� ��� � ����� ������ � ������ player_name
	bool new_value_is_better = false; // ���� ����, ��� ����� �������� ����� ����, ��� ��� ���� � �����.

	// ������ ���� � ���������, ���� �� � �� ������ � ������ player_name
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

	// ������� � ����� ������ ���. ������ ���������� ����� ������ � �����.
	if ( !record_found) { 
		io_file.clear();

		// Append new results to the table:
		io_file << player_name << ' ';
		io_file << new_number;
		io_file << std::endl;
		return true;
	}

	// ������ �������, �� ������ ������ ����� �����. ������ �������.
	if (!new_value_is_better) {
		return true;
	}

	std::vector<std::string> names; // �����.
	std::vector<int> attempts;      // �������.

	while (!io_file.fail()) { // ������ � ���������� ���������� ����� �����.
		io_file >> user_name;
		io_file >> rec_number;
		io_file.ignore();
		names.push_back(user_name);
		attempts.push_back(rec_number);
	}

	io_file.clear();
	
	fs::resize_file(high_scores_filename, pos); // ������� ������ ����� �� �����, �� ������� ����� ������, ��������� ������.

	// ����� ���������� � ���� �� ��, ��� ���� ����� ��������� ������.
	for (int i = 0; i < names.size(); ++i) {
		io_file << names.at(i) << ' ';
		io_file << attempts.at(i);
		io_file << std::endl;
	}

	// � ����� ��������� ������ � ����� ��������.
	io_file << player_name << ' ';
	io_file << new_number;
	io_file << std::endl;
	return true;
}