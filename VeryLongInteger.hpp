#ifndef VERY_LONG_INTEGER
#define VERY_LONG_INTEGER

// THE CODE NEEDS TO BE REWORKED TO CHANGE THE WAY DATA IS STORED IN THE VECTOR

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

	int absCompare(const VeryLongInteger& other) const {
		if (digits.size() != other.digits.size()) {
			return digits.size() < other.digits.size() ? -1 : 1;
		}

		for (size_t i = digits.size(); i > 0; --i) {
			if (digits[i - 1] != other.digits[i - 1]) {
				return digits[i - 1] < other.digits[i - 1] ? -1 : 1;
			}
		}
		return 0;
	}

	void subtractAbs(const VeryLongInteger& other) {
		std::vector<int>::reverse_iterator itThis = digits.rbegin();
		std::vector<int>::const_reverse_iterator itOther = other.digits.rbegin();
		int carry = 0;

		std::vector<int> result;

		while (itThis != digits.rend() || itOther != other.digits.rend() || carry) {
			int sub = (itThis != digits.rend() ? *itThis : 0) - carry;
			if (itOther != other.digits.rend()) {
				sub -= *itOther++;
			}

			if (sub < 0) {
				sub += 10;
				carry = 1;
			}
			else {
				carry = 0;
			}

			if (itThis != digits.rend()) {
				++itThis;
			}
			result.insert(result.begin(), sub);
		}

		digits = std::move(result);
	}

public:
	VeryLongInteger() = default;
	
	VeryLongInteger(long long num) {
		long long digit;
		if (num < 0) negative = true;
		num = std::abs(num);
		while (num > 0) {
			digit = num % 10;
			digits.insert(digits.begin(), digit);
			num /= 10;
		}		
	}

	VeryLongInteger(const VeryLongInteger& other) : digits{ other.digits }, negative{ other.negative } {}

	VeryLongInteger(const std::string& str) {
		if (str.empty()) {
			// vector digits should be empty too
			// how to handle this case ?
		}

		size_t start = 0;
		negative = false;


	}

	// Fix me !!
	~VeryLongInteger() {
		
	}

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
		else {
			if (absCompare(other) >= 0) {
				subtractAbs(other);
			}
			else {
				VeryLongInteger temp = other;
				temp.subtractAbs(*this);
				this->digits = temp.digits;
				this->negative = !other.negative;
			}
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