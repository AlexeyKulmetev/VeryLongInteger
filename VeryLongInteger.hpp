#ifndef VERY_LONG_INTEGER
#define VERY_LONG_INTEGER

#include <vector>
#include <iostream>
#include <cstdlib>

class VeryLongInteger {
private:
	std::vector<int> digits;
	bool negative = false;

	void addAbs(const VeryLongInteger& other) {
		auto itThis = digits.rbegin();
		auto itOther = other.digits.rbegin();
		int carry = 0;

		std::vector<int> result;

		while (itThis != digits.rend() || itOther != other.digits.rend() || carry) {
			int sum = carry;
			if (itThis != digits.rend())		{ sum += *itThis++; }
			if (itOther != other.digits.rend())	{ sum += *itOther++; }
			carry = sum / 10;
			result.insert(result.begin(), sum % 10);
		}

		digits = std::move(result);
	}

public:
	VeryLongInteger() = default;
	
	VeryLongInteger(long long num) {
		int digit;
		if (num < 0) negative = true;
		num = std::abs(num);
		while (num > 0) {
			digit = num % 10;
			digits.insert(digits.begin(), digit);
			num /= 10;
		}		
	}

	VeryLongInteger(const VeryLongInteger& other) : digits{ other.digits }, negative{ other.negative } {}

	VeryLongInteger& operator = (const VeryLongInteger& other) {
		if (this != &other) {
			digits = other.digits;
			negative = other.negative;
		}
		return *this;
	}

	VeryLongInteger& operator += (const VeryLongInteger& other) {
		// if both numbers are positive or negative
		if (this->negative == other.negative) {
			addAbs(other);
		}

		return *this;
	}

	VeryLongInteger operator + (const VeryLongInteger& other) {
		VeryLongInteger sum = *this;
		sum += other;
		return sum;
	}

	

	friend std::ostream& operator << (std::ostream& out, const VeryLongInteger& object);

};

std::ostream& operator << (std::ostream& out, const VeryLongInteger& object) {
	if (object.negative) {
		out << "-";
	}
	for (int digit : object.digits) {
		out << digit;
	}
	return out;
}

#endif