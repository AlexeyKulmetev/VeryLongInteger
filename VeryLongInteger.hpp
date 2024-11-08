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

	VeryLongInteger(VeryLongInteger& other) : digits{ other.digits }, negative{ other.negative } {}

	VeryLongInteger& operator = (const VeryLongInteger& other) {
		digits = other.digits;
		negative = other.negative;
		return *this;
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