#include <iostream>
#include <cstddef>
#include "matrix.hpp"


bool creation_test() {
	std::cout << "Creation test\n";
	
	Matrix m(10,20);

	if (m.getRows() != 10 || m.getColumns() != 20) {
		std::cout << "Creation test is not passed!\n";		
		return false;	
	}

	std::cout << "Creation test passed!\n";
	
	return true;
}


bool assignment_test() {

	std::cout << "Assignment test\n";

	Matrix m(2,3);

	m[0][0] = 1;
	m[0][1] = 2;
	m[0][2] = 3;
	m[1][0] = 4;
	m[1][1] = 5;
	m[1][2] = 6;

	if (m[0][0] != 1 || m[0][1] != 2 || m[0][2] != 3 ||
        m[1][0] != 4 || m[1][1] != 5 ||	m[1][2] != 6) {
		std::cout << "Assignment test is not passed!\n";
		return false;
	}
	
	std::cout << "Assignment test passed!\n";
	return true;

}

bool index_error_test_1() {

	std::cout << "Index error test 1 \n";
	
	Matrix m(2,3);

	try {
    	int x = m[3][0];
	}
	catch (const std::out_of_range& e) {
		std::cout << "Index error test 1 passed!\n";
		return true;
	}
	std::cout << "Index error test 1 is not passed!\n";
	return false;
}

bool index_error_test_2() {

	std::cout << "Index error test 2 \n";
	
	Matrix m(2,3);

	try {
    	int x = m[0][5];
	}
	catch (const std::out_of_range& e) {
		std::cout << "Index error test 2 passed!\n";
		return true;
	}
	std::cout << "Index error test 2 is not passed!\n";
	return false;
}


bool eq_test_1() {
	
	std::cout << "Eq 1 test\n";
	
	Matrix m(2,3);
	m[0][0] = 1;
	m[0][1] = 2;
	m[0][2] = 3;
	m[1][0] = 4;
	m[1][1] = 5;
	m[1][2] = 6;

	Matrix n(2,3);
	n[0][0] = 1;
	n[0][1] = 2;
	n[0][2] = 3;
	n[1][0] = 4;
	n[1][1] = 5;
	n[1][2] = 6;

	if (m == n) {
		std::cout << "Eq 1 test passed!\n";
		return true;
	}
	std::cout << "Eq 1 test is not passed!\n";
	return false;
	
}


bool eq_test_2() {
	
	std::cout << "Eq 2 test\n";
	
	Matrix m(2,3);
	m[0][0] = 1;
	m[0][1] = 2;
	m[0][2] = 3;
	m[1][0] = 4;
	m[1][1] = 5;
	m[1][2] = 6;

	Matrix n(2,3);
	n[0][0] = 1;
	n[0][1] = 2;
	n[0][2] = 3;
	n[1][0] = 7;
	n[1][1] = 5;
	n[1][2] = 6;

	if (m == n) {
		std::cout << "Eq 2 test is not passed!\n";
		return false;
	}
	
	std::cout << "Eq 2 test passed!\n";
	return true;
}


bool mult_test() {
	std::cout << "Multiplication by number test!\n";
	Matrix m(2,3);

	m[0][0] = 1;
	m[0][1] = 2;
	m[0][2] = 3;
	m[1][0] = 4;
	m[1][1] = 5;
	m[1][2] = 6;

	Matrix n(2,3);

	n[0][0] = 2;
	n[0][1] = 4;
	n[0][2] = 6;
	n[1][0] = 8;
	n[1][1] = 10;
	n[1][2] = 12;

	m *= 2;
	
	if (m == n) {
		std::cout << "Multiplication by number test passed!\n";
		return true;
	}

	std::cout << "Multiplication by number test is not passed!\n";
	return false;
}


int main() {

	int total = 7;
	int c = 0;

	if (creation_test()) c += 1;
	if (assignment_test()) c += 1;
	if (index_error_test_1()) c += 1;
	if (index_error_test_2()) c += 1;
	if (eq_test_1()) c += 1;
	if (eq_test_2()) c += 1;
	if (mult_test()) c += 1;

	std::cout << "Tests passed: " << c << "/" << total << "\n";

	return 0;
}
