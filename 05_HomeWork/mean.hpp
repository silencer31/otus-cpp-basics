#pragma once

#include "istatistics.hpp"

// Арифметическое среднее.
class Mean : public IStatistics {
public:
	Mean() : sum{ 0 }, total_number{ 0 } {

	}

	void update(double next) override {
		sum += next;
		++total_number;
	}

	double eval() const override {
		return sum / total_number;
	}

	const char* name() const override {
		return "mean";
	}

private:
	double sum;
	int total_number;
};