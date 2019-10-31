#include <iostream>
#include "matrix.hpp"

int main() {
	
	std::cout << "Running a small example of using Matrix class\n";

	Matrix m(2,3);

	m[0][0] = 1;
	m[0][1] = 2;
	m[0][2] = 3;
	m[1][0] = 4;
	m[1][1] = 5;
	m[1][2] = 6;
	
	std::cout << "Printing matrix values. m = \n";
	m.print_values();

	std::cout << "Getting row and column numbers\n";
	std::cout << "Num of rows: " << m.getRows() << "; Num of columns: " << m.getColumns() << "\n";

	
	std::cout << "Multiplying by a number: m *= 2\n";
	m *= 2;
	m.print_values();

	std::cout << "Getting an element by index: m[1][2]\n";
	std::cout << "m[1][2] = " << m[1][2] << "\n";
	
	return 0;
}
