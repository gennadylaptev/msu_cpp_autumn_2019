#include <iostream>
#include <cstddef>

class Matrix {

	class MatrixRow {
		
		size_t size_;
		int* data_;
		
		public:			
			MatrixRow(const size_t size, int* data);
			int& operator[] (size_t j); 
			const int& operator[] (size_t j) const;
	};

	size_t rows_;
	size_t cols_;
	int ** data_;

	public:

		Matrix (const size_t rows, const size_t cols);

		~Matrix ();

		Matrix::MatrixRow operator[] (size_t i);
		
		const Matrix::MatrixRow operator[] (size_t i) const;

		Matrix& operator*= (const int c);

		bool operator== (const Matrix& m) const;

		bool operator!= (const Matrix& m) const;

		size_t getRows() const;
		size_t getColumns() const;
		void print_values() const;
};
