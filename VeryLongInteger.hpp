#ifndef VERY_LONG_INTEGER
#define VERY_LONG_INTEGER

// THE CODE NEEDS TO BE REWORKED TO CHANGE THE WAY DATA IS STORED IN THE VECTOR
// USE RESERVE FOR PRE-ALLOCATION MEMORY
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

class VeryLongInteger {
public:
	VeryLongInteger() = default;

	explicit VeryLongInteger(long long number) {
		digits.reserve(static_cast<int>(log10(abs(number))) + 1); // reserve memory for number length
		if (number < 0) negative = true;
		int digit;
		number = std::abs(number);
		while (number > 0) {
			digit = number % 10;
			digits.push_back(digit);
			number /= 10;
		}
	}

	VeryLongInteger(VeryLongInteger& other) : digits(other.digits), negative(other.negative) {}

	VeryLongInteger(std::string& number) {
		digits.reserve(number.length());
		int digit;
		for (std::string::iterator it = number.begin(); it != number.end(); ++it) {
			digit = *it - '0';
			digits.push_back(digit);
		}
	}

private:
	std::vector<int> digits; // the idea is to store digits in reverse order
	bool negative = false;
};

#endif