#ifndef VERY_LONG_INTEGER
#define VERY_LONG_INTEGER

#include <vector>
#include <iostream>

class VeryLongInteger {
private:
	std::vector<int> digits;
	bool negative = false;

public:
	VeryLongInteger() = default;
	VeryLongInteger(int num) {
		int digit;
		while (num > 0) {
			digit = num % 10;
			digits.insert(digits.begin(), digit);
			num /= 10;
		}		
	}



	friend std::ostream& operator << (std::ostream& out, const VeryLongInteger& object);

};

std::ostream& operator << (std::ostream& out, const VeryLongInteger& object) {
	out << object.digits;
	return out;
}

#endif