#ifndef VERY_LONG_INTEGER
#define VERY_LONG_INTEGER

#include <vector>
#include <iostream>
#include <cstdlib>

class VeryLongInteger {
private:
	std::vector<int> digits;
	bool negative = false;

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
		// if both numbers are positive
		if (this->negative == other.negative) {
			auto itThis = digits.rbegin();
			auto itOther = other.digits.rbegin();

			std::vector<int> tmpDigits(std::max(digits.size(), other.digits.size()));
			int carry = 0;

			while (itThis != digits.rend() || itOther != other.digits.rend() || carry != 0) {
				int sum = carry;
				if (itThis != digits.rend()) {
					sum += *itThis;
					++itThis;
				}
				if (itOther != other.digits.rend()) {
					sum += *itOther;
					++itOther;
				}

				tmpDigits.insert(tmpDigits.begin(), sum % 10);
				carry = sum / 10;
			}

			digits = tmpDigits;
		}

		else {
			//itPos = // assign rbegin() of positive vector
			//itNegative = // assign rbegin() of negative vector

		}

	}

	VeryLongInteger operator + (const VeryLongInteger& other) {

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