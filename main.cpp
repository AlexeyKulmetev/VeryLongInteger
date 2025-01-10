#include "VeryLongInteger.hpp"

int main() {
	VeryLongInteger longInt(1111);
	VeryLongInteger longInt_2(1111);
	std::cout << longInt << "\n" << longInt_2 << "\n";
	//longInt = longInt_2;

	std::cout << longInt + longInt_2;

	return 0;
}