#include "BigInt.hpp"

int main() {
	std::cout << "Несколько примеров использония класса BigInt: \n";
	
	BigInt a("-0000123456789");
	std::cout << "Создание из строки: BigInt a(\"-0000123456789\"); a = " << a << "\n";

	BigInt b = 123;	
	std::cout << "Также BigInt можно создавать из обычного int: BigInt b = 123; b = " << b << "\n";

	std::cout << "BigInt можно складывать: a + b = " << a+b << "\n";
	std::cout << "И вычитать: a - b = " << a-b << "\n";

	std::cout << "А также делать это inplace.\n";
	std::cout << "BigInt можно сравнивать между собой и int, в общем все то, что можно делать с int\n";
	std::cout << "Все, кроме деления и умножения.\n";

	return 0;
}
