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

	explicit VeryLongInteger(const long long number) {
		// Check if number == 0
		if (number == 0) {
			digits.push_back(0);
			return;
		}
		// Calculate number of elements and reserve memory
		int count = 0;
		long long temp = number;
		while (temp != 0) {
			temp /= 10;
			++count;
		}
		digits.reserve(count);

		if (number < 0) {
			negative = true;
			temp = -number;
		}
		int digit;
		while (temp > 0) {
			digit = temp % 10;
			digits.push_back(digit);
			temp /= 10;
		}
	}

	VeryLongInteger(const VeryLongInteger& other) : digits(other.digits), negative(other.negative) {}

	VeryLongInteger(std::string& number) { // FIX ME HANDLE THE CASE IF STRING STARTS BY ZEROS
		if (!number.empty() && number[0] == '-') {
			negative = true;
			number.erase(number.begin());
		}
		digits.reserve(number.length());

		for (std::string::iterator it = number.begin(); it != number.end(); ++it) {
			if (!isdigit < *it) {
				throw std::invalid_argument("Invalid character in number string");
			}
			digits.push_back(*it - '0');
		}
		std::reverse(digits.begin(), digits.end());
	}

	~VeryLongInteger() = default;

	VeryLongInteger& operator = (const VeryLongInteger& other) {
		if (this == &other) return *this;
		digits = other.digits;
		negative = other.negative;
		return *this;
	}

	VeryLongInteger& operator += (const VeryLongInteger& other) {
		// if both numbers are positive or negative
		if (this->negative == other.negative) {
			addAbs(other);
		}
		else {
			if (absCompare(other) > 0) {
				subtractAbs(other);
			}
			else {
				VeryLongInteger temp = other;
				temp.subtractAbs(*this);
				this->digits = temp.digits;
				this->negative = temp.negative; // AI advises: this->negative = !other.negative ??
			}
		}
		return *this;
	}

	VeryLongInteger operator + (const VeryLongInteger& other) const {
		VeryLongInteger sum = *this;
		sum += other;
		return sum;
	}

	VeryLongInteger& operator -= (const VeryLongInteger& other) {
		if (negative) {
			if (other.negative) {
				addAbs(other);
			}
			else {
				if (absCompare(other) > 0) {
					subtractAbs(other);
				}
				else {
					VeryLongInteger temp = other;
					temp.subtractAbs(*this);
					this->digits = temp.digits;
					this->negative = temp.negative;
				}
			}
		}
		else {
			if (!other.negative) {
				if (absCompare(other) > 0) {
					subtractAbs(other);
				}
				else {
					VeryLongInteger temp = other;
					temp.subtractAbs(*this);
					this->digits = temp.digits;
					this->negative = true;
				}
			}
			else {
				absCompare(other);
			}
		}
		return *this;
	}

private:
	std::vector<int> digits; // the idea is to store digits in reverse order
	bool negative = false;

	void addAbs(const VeryLongInteger& other) {
		std::vector<int>::iterator itThis = digits.begin();
		std::vector<int>::const_iterator itOther = other.digits.begin();
		int carry = 0;
		int sum = 0;
		std::vector<int> result(std::max(digits.size(), other.digits.size()) + 1);

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
		std::vector<int> result(std::max(digits.size(), other.digits.size()));

		while (itThis != digits.end() || itOther != other.digits.end() || carry) {
			sub = (itThis != digits.end() ? *itThis : 0) - carry; // FIX ME DELETE LEEDING ZEROES
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

	int absCompare(const VeryLongInteger& other) const {
		if (digits.size() != other.digits.size()) {
			return digits.size() < other.digits.size() ? -1 : 1;
		}
		for (size_t i = 0; i < digits.size(); ++i) {
			if (digits[i] != other.digits[i]) {
				return digits[i] < other.digits[i] ? -1 : 1;
			}
		}
		return 0;
	}
};

#endif