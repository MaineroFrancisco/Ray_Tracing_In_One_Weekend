#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <numbers>
#include <random>


// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = std::numbers::pi; // Only C++20 and above

// Utility Functions

inline double degrees_to_radians(double degrees) { return degrees * pi / 180.0; }

inline double random_double() {
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	std::random_device device; // Will be used to obtain a seed for the random number engine
	static std::mt19937 generator(
		device); // Standard mersenne_twister_engine seeded with device()
	return distribution(generator);
}

// Common Headers

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"