#include "BigInt.hpp"

bool test1 () {
	std::string name("Конструктор из строки: ");	
	try {
		BigInt a("123456789123456789");
		std::cout << name << ": пройдено\n";
		return true;
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test2 () {
	std::string name("Приведение к int и сравнение с int 1");	
	try {
		BigInt a = 123456;
		if (a == 123456) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test3 () {
	std::string name("Приведение к int и сравнение с int 2");	
	try {
		BigInt a(123456);
		if (a == 123456) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test4 () {
	std::string name("Cоздание нулевого объекта по умолчанию");	
	try {
		BigInt a;
		if (a == 0 and a == BigInt("0")) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test5 () {
	std::string name("Cоздание отриц. числа из строки 1");	
	try {
		BigInt a("-12345");
		if (a == -12345) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}


bool test6 () {
	std::string name("Cоздание отриц. числа из строки 2");	
	try {
		BigInt a("-123456789123456789");
		BigInt b("123456789123456789");
		if (!a.get_sign() and a.abs_eq(b)) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test7 () {
	std::string name("Cоздание числа из строки, начинающийся с нулей");	
	try {
		BigInt a("-0000000000000123456789123456789");
		BigInt b("0000000000000123456789123456789");
		BigInt a2("-123456789123456789");
		BigInt b2("123456789123456789");
		if (a == a2 and b == b2) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}


bool test8 () {
	std::string name("Больше, чем тест1");	
	try {
		BigInt a("123456789123456789");
		BigInt b("123456789023456789");
		if (a > b) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test9 () {
	std::string name("Больше, чем тест2");	
	try {
		BigInt a("123456789");
		BigInt b("-123456789223456789");
		if (a > b) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test10 () {
	std::string name("Больше, чем тест3");	
	try {
		BigInt a("123456789");
		BigInt b("123");
		if (a > b) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}


bool test11 () {
	std::string name("Меньше, чем тест1");	
	try {
		BigInt a("123456789123456789");
		BigInt b("123456789023456789");
		if (b < a) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test12 () {
	std::string name("Меньше, чем тест2");	
	try {
		BigInt a("123456789");
		BigInt b("-123456789223456789");
		if (b < a) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test13 () {
	std::string name("Меньше, чем тест3");	
	try {
		BigInt a("123456789");
		BigInt b("123");
		if (b < a) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test14 () {
	std::string name("Больше или равно тест1");	
	try {
		BigInt a("123456789123456789");
		BigInt b("123456789023456789");
		if (a >= b) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test15 () {
	std::string name("Больше или равно тест2");	
	try {
		BigInt a("123456789");
		BigInt b("-123456789223456789");
		if (a >= b) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test16 () {
	std::string name("Больше или равно тест3");	
	try {
		BigInt a("123456789");
		BigInt b("123");
		if (a >= b) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test17 () {
	std::string name("Больше или равно тест4");	
	try {
		BigInt a("123456789123456789");
		BigInt b("123456789123456789");
		if (a >= b) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test18 () {
	std::string name("Больше или равно тест5");	
	try {
		BigInt a("-123456789123456789");
		BigInt b("-123456789123456789");
		if (a >= b) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test19 () {
	std::string name("Больше или равно тест6");	
	try {
		BigInt a("0");
		BigInt b("0");
		if (a >= b) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}


bool test20 () {
	std::string name("Меньше или равно тест1");	
	try {
		BigInt a("123456789123456789");
		BigInt b("123456789023456789");
		if (b <= a) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test21 () {
	std::string name("Меньше или равно тест2");	
	try {
		BigInt a("123456789");
		BigInt b("-123456789223456789");
		if (b <= a) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test22 () {
	std::string name("Меньше или равно тест3");	
	try {
		BigInt a("123456789");
		BigInt b("123");
		if (b <= a) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test23 () {
	std::string name("Меньше или равно тест4");	
	try {
		BigInt a("123456789123456789");
		BigInt b("123456789123456789");
		if (b <= a) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test24 () {
	std::string name("Меньше или равно тест5");	
	try {
		BigInt a("-123456789123456789");
		BigInt b("-123456789123456789");
		if (b <= a) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test25 () {
	std::string name("Меньше или равно тест6");	
	try {
		BigInt a("0");
		BigInt b("0");
		if (b <= a) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test26 () {
	std::string name("Унарный минус 1");	
	try {
		BigInt a("123456789");
		BigInt b = -a;
		if (a == -b and -a == b) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test27 () {
	std::string name("Унарный минус 2");	
	try {
		BigInt a("123456789");
		BigInt b = -a;
		if (a.abs_eq(b) and !b.get_sign()) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test28 () {
	std::string name("Сложение 1");	
	try {
		BigInt a("123456789");
		BigInt b("923456789");
		BigInt c("1046913578");
		if (a + b == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test29 () {
	std::string name("Сложение 2");	
	try {
		BigInt a("123456789");
		BigInt b("-123456789");
		BigInt c("0");
		if (a + b == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test30 () {
	std::string name("Сложение 3");	
	try {
		BigInt a("-123456789");
		BigInt b("123456789");
		BigInt c("0");
		if (a + b == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test31 () {
	std::string name("Сложение 4");	
	try {
		BigInt a("-123456789");
		BigInt b("923456789");
		BigInt c("800000000");
		if (a + b == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}


bool test32 () {
	std::string name("Сложение 5");	
	try {
		BigInt a("923456789");
		BigInt b("-123456789");
		BigInt c("800000000");
		if (a + b == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}


bool test33 () {
	std::string name("Сложение 6");	
	try {
		BigInt a("-923456789");
		BigInt b("123456789");
		BigInt c("-800000000");
		if (a + b == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test34 () {
	std::string name("Сложение 7");	
	try {
		BigInt a("123456789");
		BigInt b("-923456789");
		BigInt c("-800000000");
		if (a + b == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test35 () {
	std::string name("Вычитание 1");	
	try {
		BigInt a("123456789");
		BigInt b("923456789");
		BigInt c("-800000000");
		if (a - b == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test36 () {
	std::string name("Вычитание 2");	
	try {
		BigInt a("123456789");
		BigInt b("123456789");
		BigInt c("0");
		if (a - b == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test37 () {
	std::string name("Вычитание 3");	
	try {
		BigInt a("-123456789");
		BigInt b("123456789");
		BigInt c("-246913578");
		if (a - b == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test38 () {
	std::string name("Вычитание 4");	
	try {
		BigInt a("-123456789");
		BigInt b("-123456789");
		BigInt c("0");
		if (a - b == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}


bool test39 () {
	std::string name("Вычитание 5");	
	try {
		BigInt a("923456789");
		BigInt b("-123456789");
		BigInt c("1046913578");
		if (a - b == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}


bool test40 () {
	std::string name("Вычитание 6");	
	try {
		BigInt a("-923456789");
		BigInt b("-123456789");
		BigInt c("-800000000");
		if (a - b == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test41 () {
	std::string name("Сложение inplace 1");	
	try {
		BigInt a("123456789");
		BigInt b("923456789");
		BigInt c("1046913578");
		a += b;
		if (a  == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test42 () {
	std::string name("Сложение inplace 2");	
	try {
		BigInt a("123456789");
		BigInt b("-123456789");
		BigInt c("0");
		a += b;
		if (a == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test43 () {
	std::string name("Сложение inplace 3");	
	try {
		BigInt a("-123456789");
		BigInt b("123456789");
		BigInt c("0");
		a += b;
		if (a == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test44 () {
	std::string name("Сложение inplace 4");	
	try {
		BigInt a("-123456789");
		BigInt b("923456789");
		BigInt c("800000000");
		a += b;
		if (a == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}


bool test45 () {
	std::string name("Сложение inplace 5");	
	try {
		BigInt a("923456789");
		BigInt b("-123456789");
		BigInt c("800000000");
		a += b;
		if (a == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}


bool test46 () {
	std::string name("Сложение inplace 6");	
	try {
		BigInt a("-923456789");
		BigInt b("123456789");
		BigInt c("-800000000");
		a += b;
		if (a == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test47 () {
	std::string name("Сложение inplace 7");	
	try {
		BigInt a("123456789");
		BigInt b("-923456789");
		BigInt c("-800000000");
		a += b;
		if (a == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test48 () {
	std::string name("Вычитание inplace 1");	
	try {
		BigInt a("123456789");
		BigInt b("923456789");
		BigInt c("-800000000");
		a -= b;
		if (a == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test49 () {
	std::string name("Вычитание inplace 2");	
	try {
		BigInt a("123456789");
		BigInt b("123456789");
		BigInt c("0");
		a -= b;
		if (a == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test50 () {
	std::string name("Вычитание inplace 3");	
	try {
		BigInt a("-123456789");
		BigInt b("123456789");
		BigInt c("-246913578");
		a -= b;
		if (a == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}

bool test51 () {
	std::string name("Вычитание inplace 4");	
	try {
		BigInt a("-123456789");
		BigInt b("-123456789");
		BigInt c("0");
		a -= b;
		if (a == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}


bool test52 () {
	std::string name("Вычитание inplace 5");	
	try {
		BigInt a("923456789");
		BigInt b("-123456789");
		BigInt c("1046913578");
		a -= b;
		if (a == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}


bool test53 () {
	std::string name("Вычитание inplace 6");	
	try {
		BigInt a("-923456789");
		BigInt b("-123456789");
		BigInt c("-800000000");
		a -= b;
		if (a == c) {
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}


bool test54 () {
	std::string name("Метод to_str");	
	try {
		BigInt a("923456789");
		BigInt b("-123456789");
		BigInt c("-000000000123456789");
		BigInt d("000000000923456789");

		std::string as = a.to_str();
		std::string bs = b.to_str();
		std::string cs = c.to_str();
		std::string ds = d.to_str();

		if (as == "923456789" and bs == "-123456789"
            and cs == "-123456789" and ds == "923456789")
		{
			std::cout << name << ": пройдено\n";
			return true;
		}
		else {
			std::cout << name << ": не пройдено\n";		
		    return false;
		}
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}


bool test55 () {
	std::string name("operator<<");	
	try {
		BigInt a("-923456789");
		BigInt b("-123456789");
		BigInt c("-800000000");
		std::cout << "Печатаем BigInt " << a << " " << b << " " << c << "\n"; 
		
		std::cout << name << ": пройдено\n";
		return true;
	}
	catch (...) {
		std::cout << name << ": не пройдено\n";		
		return false;
	}
}


int main () {

	size_t passed = 0;


	if(test1()) passed++;
	if(test2()) passed++;
	if(test3()) passed++;
	if(test4()) passed++;
	if(test5()) passed++;
	if(test6()) passed++;
	if(test7()) passed++;
	if(test8()) passed++;
	if(test9()) passed++;
	if(test10()) passed++;
	if(test11()) passed++;
	if(test12()) passed++;
	if(test13()) passed++;
	if(test14()) passed++;
	if(test15()) passed++;
	if(test16()) passed++;
	if(test17()) passed++;
	if(test18()) passed++;
	if(test19()) passed++;
	if(test20()) passed++;
	if(test21()) passed++;
	if(test22()) passed++;
	if(test23()) passed++;
	if(test24()) passed++;
	if(test25()) passed++;
	if(test26()) passed++;
	if(test27()) passed++;
	if(test28()) passed++;
	if(test29()) passed++;
	if(test30()) passed++;
	if(test31()) passed++;
	if(test32()) passed++;
	if(test33()) passed++;
	if(test34()) passed++;
	if(test35()) passed++;
	if(test36()) passed++;
	if(test37()) passed++;
	if(test38()) passed++;
	if(test39()) passed++;
	if(test40()) passed++;
	if(test41()) passed++;
	if(test42()) passed++;
	if(test43()) passed++;
	if(test44()) passed++;
	if(test45()) passed++;
	if(test46()) passed++;
	if(test47()) passed++;
	if(test48()) passed++;
	if(test49()) passed++;
	if(test50()) passed++;
	if(test51()) passed++;
	if(test52()) passed++;
	if(test53()) passed++;
	if(test54()) passed++;
	if(test55()) passed++;

	std::cout << "Тестов пройдено: " << passed << "/55\n";

	return 0;
}
