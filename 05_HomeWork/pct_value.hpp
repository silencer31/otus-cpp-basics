#pragma once

#include "istatistics.hpp"

#include <vector>
#include <algorithm>

// Процентиль.
class PctValue : public IStatistics {
public:
	PctValue() : std_value{ 0 }, total_number{ 0 } {
		pct_to_find = 100;
		allvalues.reserve(11);

		prepare_full_name();
	}

	PctValue(int pct) : pct_to_find{ pct }, std_value { 0 }, total_number{ 0 } {
		if ((pct > 100) || (pct < 0)) {
			pct_to_find = 100;
			std::cout << "pct value must be between 0 and 100 percent! Default value 100 will be used." << std::endl;
		}
		
		allvalues.reserve(11);

		prepare_full_name();
	}

	void update(double next) override {
		allvalues.push_back(next); // Добавляем новый элемент в коллекцию.
		std::sort(allvalues.begin(), allvalues.end()); // Сортируем коллекцию в порядке возрастания значений.
				
		++total_number;
		
		double one_percent = static_cast<double>(total_number) / 100;
		double pct_border = one_percent * pct_to_find; // Номер искомого элемента коллекции должен совпадать или быть сразу после этого значения.

		for(int i = 0; i < total_number; ++i)
		{
			if (static_cast<double>(i + 1) >= pct_border) {
				std_value = allvalues.at(i);
				break;
			}
		}
	}

	double eval() const override {
		return std_value;
	}

	const char* name() const override {
		return fullname;
	}

private: // Functions
	void prepare_full_name() {
		for (int i = 0; i < 7; ++i) { fullname[i] = 0; }
		strcpy_s(fullname, "pct");
		char num_str[4];
		for (int i = 0; i < 4; ++i) { num_str[i] = 0; }
		_itoa_s(pct_to_find, num_str, 10);
		strcat_s(fullname, num_str);
	}

private:
	int pct_to_find; // Какой процентиль ищем.
	int total_number;

	double std_value;

	std::vector<double> allvalues;

	char fullname[7];
};