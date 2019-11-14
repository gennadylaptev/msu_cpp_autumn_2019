#include <cassert>
#include <iostream>
#include <string>
#include <cstdint>
#include <cstddef>
#include <algorithm>
#include <cmath>


class BigInt {

	static const uint8_t BASE = 10;
	const uint8_t offset = 48;
	bool sign_ = true; // true - положительное, false - отрицательное
	uint8_t * data_;
	size_t size_;


	public:		
		// Конструктор по умолчанию (создает нулевой BigInt)
		BigInt ();
		
		// Конструктор из указателя на массив uint8_t и размера
		BigInt (uint8_t * data, size_t size, bool sign);

		// Конструктор из строки
		BigInt (const std::string& str) ;

		// Конструктор копирования
		BigInt (BigInt const& other);

		// Деструктор 
		~BigInt () ;
		
		// Приведение int к BigInt
	 	BigInt(int x);

		// Оператор присваивания	
		BigInt& operator= (BigInt const& other) ;


		// Операторы сравнения
		bool operator> (BigInt const& other) const ;

		bool operator== (BigInt const& other) const ;

		bool operator< (BigInt const& other) const ;

		bool operator>= (BigInt const& other) const ;

		bool operator<= (BigInt const& other) const ;


		// Унарный минус
		BigInt operator- () const;


		// Доп. операторы сравнения (по модулю)
		bool abs_gt (BigInt const& other) const ;

		bool abs_eq (BigInt const& other) const ;


		// Сложение и вычитание
		BigInt operator+ (BigInt const& other);
		BigInt operator- (BigInt const& other);

		// Сложение и вычитание inplace
		const BigInt& operator+=(const BigInt& other);
		const BigInt& operator-=(const BigInt& other);

		
		// Доп. методы для реализации сложения и вычитания
		static BigInt _subtract (BigInt const& a, BigInt const& b);

		static BigInt _add (BigInt const& a, BigInt const& b);

			// вычитаем из большего по модулю меньшее, одинакового знака
		static BigInt _abs_subtract (BigInt const& a, BigInt const& b);

			// Складываем по модулю
		static BigInt _abs_sum (BigInt const& a, BigInt const& b);


		std::string to_str() const;
		void set_sign (bool sign);
		bool get_sign () const;
		size_t get_size () const;

		friend std::ostream& operator<< (std::ostream& out, const BigInt& x);

};
