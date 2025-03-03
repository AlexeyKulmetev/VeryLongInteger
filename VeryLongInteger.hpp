#ifndef VERY_LONG_INTEGER
#define VERY_LONG_INTEGER

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
		temp = number;
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

	VeryLongInteger(const std::string& str) { 
		if (str.empty()) { // handle empty string
			digits.push_back(0);
			return;
		}
		size_t start = str.find_first_not_of('0');
		if (start == std::string::npos) {
			digits.push_back(0);
			return;
		}
		digits.reserve(str.length());
		if (str[0] == '-') {
			negative = true;
			start = str.find_first_not_of('0', 1);
			if (start == std::string::npos) {
				digits.push_back(0);
				negative = false;
				return;
			}
		}
		for (size_t i = start; i < str.length(); ++i) {
			if (!isdigit(str[i])) {
				throw std::invalid_argument("Invalid character in number string");
			}
			digits.push_back(str[i] - '0');
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
				*this = std::move(temp);
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
		if (negative == other.negative) {
			if (absCompare(other) >= 0) {
				subtractAbs(other);
			}
			else {
				VeryLongInteger temp = other;
				temp.subtractAbs(*this);
				*this = std::move(temp);
				negative = !negative;
			}
		}
		else {
			addAbs(other);
		}
		return *this;
	}

	VeryLongInteger operator - (const VeryLongInteger& other) const {
		VeryLongInteger sub = *this;
		sub -= other;
		return sub;
	}

	VeryLongInteger& operator *= (const VeryLongInteger& other) {
		// check multiplication by zero
		if (digits.size() == 1 && digits[0] == 0) {
			return *this; 
		}
		if (other.digits.size() == 1 && other.digits[0] == 0) {
			digits = { 0 };
			negative = false;
			return *this;
		}
		// create vector for result
		std::vector<int> result(digits.size() + other.digits.size(), 0);
		// multiplication
		for (size_t i = 0; i < digits.size(); ++i) {
			int carry = 0;
			for (size_t j = 0; j < other.digits.size(); ++j) {
				int product = digits[i] * other.digits[j] + result[i + j] + carry;
				result[i + j] = product % 10;
				carry = product / 10;
			}
			if (carry) {
				result[i + other.digits.size()] += carry;
			}
		}
		// delete leading zeros
		while (result.size() > 1 && result.back() == 0) {
			result.pop_back();
		}
		if (result.empty()) result.push_back(0);
		digits = std::move(result);
		negative = (negative != other.negative);
		return *this;
	}

	VeryLongInteger operator * (const VeryLongInteger& other) {
		VeryLongInteger prod = *this;
		prod *= other;
		return prod;
	}

	friend std::ostream& operator << (std::ostream& out, const VeryLongInteger& num);

private:
	std::vector<int> digits; // the idea is to store digits in reverse order
	bool negative = false;

	void addAbs(const VeryLongInteger& other) {
		if (other.digits.empty()) return;

		std::vector<int>::iterator itThis = digits.begin();
		std::vector<int>::const_iterator itOther = other.digits.begin();
		int carry = 0;
		int sum = 0;
		std::vector<int> result;
		result.reserve(std::max(digits.size(), other.digits.size()) + 1);

		while (itThis != digits.end() || itOther != other.digits.end() || carry) {
			sum = carry;
			if (itThis != digits.end()) sum += *itThis++;
			if (itOther != other.digits.end()) sum += *itOther++;
			result.push_back(sum % 10);
			carry = sum / 10;
		}
		while (result.size() > 1 && result.back() == 0) {
			result.pop_back();
		}
		if (result.empty()) result.push_back(0);
		digits = std::move(result);
	}

	void subtractAbs(const VeryLongInteger& other) {
		if (other.digits.empty()) return;

		std::vector<int>::iterator itThis = digits.begin();
		std::vector<int>::const_iterator itOther = other.digits.begin();
		int carry = 0;
		int sub = 0;
		std::vector<int> result;
		result.reserve(std::max(digits.size(), other.digits.size()));

		while (itThis != digits.end() || itOther != other.digits.end() || carry) {
			sub = (itThis != digits.end() ? *itThis : 0) - carry;
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
		// Delete leading zeroes :
		while (result.size() > 1 && result.back() == 0) {
			result.pop_back();
		}
		if (result.empty()) result.push_back(0);
		digits = std::move(result);
	}

	int absCompare(const VeryLongInteger& other) const {
		if (digits.size() != other.digits.size()) {
			return digits.size() - other.digits.size(); // returns different between sizes
		}
		for (size_t i = 0; i < digits.size(); ++i) {
			if (digits[i] != other.digits[i]) {
				return digits[i] - other.digits[i];
			}
		}
		return 0;
	}
};

std::ostream& operator << (std::ostream& out, const VeryLongInteger& num) {
	if (num.negative) {
		out << "-";
		for (auto it = num.digits.rbegin(); it != num.digits.rend(); ++it) {
			out << *it;
		}
	}
	else {
		for (auto it = num.digits.rbegin(); it != num.digits.rend(); ++it) {
			out << *it;
		}
	}
	return out;
}

#endif