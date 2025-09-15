#include "core/rtweekend.h"

#include <iomanip>
#include <iostream>

double icd(double d) { return 8.0 * std::pow(d, 1.0 / 3.0); }

double pdf(double x) { return (3.0 / 8.0) * x * x; }

int main() {
	int N = 1;
	auto sum = 0.0;

	switch (0) {
	case 0: { // Integrate f(x) = x^2
		for (int i = 0; i < N; i++) {
			auto z = random_double();
			if (z == 0.0) // Ignore zero to avoid NaNs
				continue;

			auto x = icd(z);
			sum += x * x / pdf(x);
		}
		break;
	}
	case 1: { // Integrate f(x) = sin(x)^5
		break;
	}
	case 2: { // Integrate f(x) = log(sin(x))
		break;
	}
	}

	std::cout << std::fixed << std::setprecision(12);
	std::cout << "I = " << (sum / N) << '\n';
}