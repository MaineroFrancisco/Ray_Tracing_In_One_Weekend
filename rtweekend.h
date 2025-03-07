#pragma once

#include <cmath>
#include <cstdlib>
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
	// Returns a random real in [0,1).
	return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
	// Returns a random real in [min,max).
	return min + (max - min) * random_double();
}

// Common Headers

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"