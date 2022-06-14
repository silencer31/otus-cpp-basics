#pragma once

#include "istatistics.hpp"

#include <vector>

// Среднеквадратическое отклонение.
class StdValue : public IStatistics {
public:
	StdValue() : std_value{ 0 }, mean_value{ 0 }, sum{ 0 }, total_number{ 0 } {
		allvalues.reserve(11);
	}

	void update(double next) override {
		sum += next;
		++total_number;
		mean_value = sum / total_number;

		allvalues.push_back(next);

		double std_sum = 0;

		for each (double value in allvalues)
		{
			std_sum += (value - mean_value) * (value - mean_value);
		}

		std_value = std::sqrt(std_sum/ total_number);
	}

	double eval() const override {
		return std_value;
	}

	const char* name() const override {
		return "std value";
	}

private:
	double std_value;
	double mean_value;
	
	double sum;
	int total_number;

	std::vector<double> allvalues;
};