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
		std::vector<int>::iterator itThis = digits.begin();
		std::vector<int>::const_iterator itOther = other.digits.begin();
		int carry = 0;

		std::vector<int> result;

		while (itThis != digits.end() || itOther != digits.end() || carry) {
			int sum = carry;
			if (itThis != digits.end())			{ sum += *itThis++; }
			if (itOther != other.digits.end())	{ sum += *itThis++; }
			carry = sum / 10;
			result.push_back(sum % 10);
		}

		digits = std::move(result);
	}

public:
	VeryLongInteger() = default;
	
	VeryLongInteger(int num) {
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