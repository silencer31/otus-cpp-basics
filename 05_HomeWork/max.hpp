#pragma once

#include "istatistics.hpp"

// Максимальное значение.
class Max : public IStatistics {
public:
	Max() : m_max{ std::numeric_limits<double>::lowest() } {
		
	}

	void update(double next) override {
		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override {
		return m_max;
	}

	const char* name() const override {
		return "max";
	}

private:
	double m_max;
};