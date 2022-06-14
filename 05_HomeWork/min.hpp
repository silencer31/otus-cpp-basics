#pragma once

#include "istatistics.hpp"

// Минимальное значение.
class Min : public IStatistics {
public:
	Min() : m_min{ std::numeric_limits<double>::max() } {
		
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char* name() const override {
		return "min";
	}

private:
	double m_min;
};