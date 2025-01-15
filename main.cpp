#include "VeryLongInteger.hpp"

int main() {
	VeryLongInteger longInt(1235648975615);
	VeryLongInteger longInt_2(123454812315486);
	std::cout << longInt << "\n" << longInt_2 << "\n";
	//longInt = longInt_2;

	std::cout << longInt + longInt_2;

	return 0;
}