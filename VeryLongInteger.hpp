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

	~VeryLongInteger() = default;

	VeryLongInteger& operator = (const VeryLongInteger& other) {
		if (this == &other) return *this;

		digits = other.digits;
		negative = other.negative;
		return *this;
	}

	VeryLongInteger& operator += (const VeryLongInteger& other) {

	}

private:
	std::vector<int> digits; // the idea is to store digits in reverse order
	bool negative = false;

	void addAbs(const VeryLongInteger& other) {
		std::vector<int>::iterator itThis = digits.begin();
		std::vector<int>::const_iterator itOther = other.digits.begin();
		int carry = 0;
		int sum = 0;
		std::vector<int> result(std::max(digits.size(), other.digits.size()));

		while (itThis != digits.end() || itOther != other.digits.end() || carry) {
			sum = carry;
			if (itThis != digits.end()) sum += *itThis++;
			if (itOther != other.digits.end()) sum += *itOther++;
			result.push_back(sum % 10);
			carry = sum / 10;
		}

		digits = std::move(result);
	}

	void subtractAbs(const VeryLongInteger& other) {
		std::vector<int>::iterator itThis = digits.begin();
		std::vector<int>::const_iterator itOther = other.digits.begin();
		int carry = 0;
		int sub = 0;
		std::vector<int> result;

		while (itThis != digits.end() || itOther != other.digits.end() || carry) {
			sub = (itThis != digits.end() ? *itThis : 0) - carry; // FIX ME
			if (itOther != other.digits.end()) sub -= *itOther++;
			if (sub < 0) {
				sub += 10;
				carry = 1;
			}
			else {
				carry = 0;
			}
			if (itThis != digits.end()) ++itThis;
			result.push_back(sub);
		}
		digits = std::move(result);
	}
};

#endif