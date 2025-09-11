#include "core/rtweekend.h"

#include <iomanip>
#include <iostream>

int main() {
	int a = 0;
	int b = 2;
	int N = 1000000;
	auto sum = 0.0;

	switch (0) {
	case 0: { // Integrate f(x) = x^2
		for (int i = 0; i < N; i++) {
			auto x = random_double(a, b);
			sum += x * x;
		}
		break;
	}
	case 1: { // Integrate f(x) = sin(x)^5
		for (int i = 0; i < N; i++) {
			auto x = random_double(a, b);
			sum += std::pow(std::sin(x), 5.0);
		}
		break;
	}
	case 2: { // Integrate f(x) = log(sin(x))
		for (int i = 0; i < N; i++) {
			auto x = random_double(a, b);
			sum += std::log(std::sin(x));
		}
		break;
	}
	}

	std::cout << std::fixed << std::setprecision(12);
	std::cout << "I = " << (b - a) * (sum / N) << '\n';
}