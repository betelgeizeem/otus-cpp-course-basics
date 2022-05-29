#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};

class Max : public IStatistics {
public:
	Max() : m_max{std::numeric_limits<double>::min()} {
	}

	void update(double next) override {
		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override {
		return m_max;
	}

	const char * name() const override {
		return "max";
	}

private:
	double m_max;
};


class Mean : public IStatistics {
public:
	Mean() : m_sum{0}, m_count{0} {
	}

	void update(double next) override {
		m_sum += next;
		m_count++;
	}

	double eval() const override {
		return m_sum / static_cast<double>(m_count);
	}

	const char * name() const override {
		return "mean";
	}

private:
	double m_sum;
	size_t m_count;
};

class Std : public IStatistics {
public:
	Std() {}

	void update(double next) override {
		m_data.push_back(next);
		m_mean.update(next);
	}

	double eval() const override {
		auto mean = m_mean.eval();

		auto std = 0.;
		for (auto& a : m_data)
			std += (a - mean) * (a - mean);

		std = m_data.empty() ? 0 : std::sqrt(std / static_cast<double>(m_data.size()));

		return std;
	}

	const char * name() const override {
		return "std";
	}

private:
	std::vector<double> m_data;
	Mean m_mean;
};

class Quantile : public IStatistics {
public:
	Quantile(double q, const char * name) : m_q{q} {
		strcpy(m_name, name);
	}

	void update(double next) override {
		m_data.push_back(next);
	}

	double eval() const override {
		auto data_copy = m_data;
		std::sort(data_copy.begin(), data_copy.end());
		auto& sorted = data_copy;
		auto n = sorted.size();
		sorted.push_back(sorted.back());
		
		auto k = m_q * (n - 1);

		if (std::abs(k + 1 - m_q * n) < 1 / static_cast<double>(n))
			return 0.5 * (sorted[k] + sorted[k + 1]);

		if (k + 1 < m_q * n)
			return sorted[k + 1];
		else
			return sorted[k];
	}

	const char * name() const override {
		return m_name;
	}

protected:
	std::vector<double> m_data;
	const double m_q;
	char m_name[4];
};


int main() {

	const size_t statistics_count = 6;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Std{};
	statistics[4] = new Quantile{0.9, "p90"};
	statistics[5] = new Quantile{0.95, "p95"};


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