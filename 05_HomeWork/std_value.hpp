#pragma once

#include "istatistics.hpp"

#include <vector>

// Среднеквадратическое отклонение.
class StdValue : public IStatistics {
public:
	StdValue() : sum{ 0 }, total_number{ 0 } {
		allvalues.reserve(11);
	}

	void update(double next) override {
		sum += next;
		++total_number;

		allvalues.push_back(next);
	}

	double eval() const override {
		double std_sum = 0;

		for each (double value in allvalues)
		{
			std_sum += (value - sum / total_number) * (value - sum / total_number);
		}

		return std::sqrt(std_sum / total_number);
	}

	const char* name() const override {
		return "std value";
	}

private:
	double sum;
	int total_number;

	std::vector<double> allvalues;
};