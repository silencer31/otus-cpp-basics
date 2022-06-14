#include <iostream>
#include <limits>

#include "istatistics.hpp"
#include "min.hpp"
#include "max.hpp"
#include "mean.hpp"
#include "std_value.hpp"
#include "pct_value.hpp"

int main() {

	const size_t statistics_count = 7;
	IStatistics *statistics[statistics_count]; // Массив указателей на базовый класс.

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new StdValue{};
	statistics[4] = new PctValue{ 90 };
	statistics[5] = new PctValue{ 95 };
	statistics[6] = new PctValue{ 102 }; // Для теста обработки ошибки.

	double val = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}