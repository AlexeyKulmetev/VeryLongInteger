#include "VeryLongInteger.hpp"

int main() {
	VeryLongInteger longInt(-567);
	VeryLongInteger longInt_2(200);
	std::cout << longInt << "\n" << longInt_2 << "\n";
	longInt = longInt_2;
	std::cout << longInt << "\n" << longInt_2 << "\n";
//	std::cout << "test";
	return 0;
}