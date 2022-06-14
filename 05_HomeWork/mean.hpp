#pragma once

#include "istatistics.hpp"

// Арифметическое среднее.
class Mean : public IStatistics {
public:
	Mean() : mean_value{ 0 }, sum{ 0 }, total_number{ 0 } {

	}

	void update(double next) override {
		sum += next;
		++total_number;
		mean_value = sum / total_number;
	}

	double eval() const override {
		return mean_value;
	}

	const char* name() const override {
		return "mean";
	}

private:
	double mean_value;
	double sum;
	int total_number;
};