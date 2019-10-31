#include <iostream>
#include <cstddef>
#include "matrix.hpp"
	
		
Matrix::MatrixRow::MatrixRow(const size_t size, int* data) : size_(size), data_(data) {}


int& Matrix::MatrixRow::operator[] (size_t j) {
	if (0 <= j &&  j < size_) {
		return data_[j];
	}
	else {
		throw std::out_of_range("Column Index Error");
	}
}


const int& Matrix::MatrixRow::operator[] (size_t j) const {
	if (0 <= j &&  j < size_) {
		return data_[j];
	}
	else {
		throw std::out_of_range("Column Index Error");
	}
}



Matrix::Matrix (const size_t rows, const size_t cols) : rows_(rows), cols_(cols) {
	data_ = new int*[rows_];
	for (size_t i = 0; i < rows_; ++i)
		data_[i] = new int[cols];
}


Matrix::~Matrix () {
	for (size_t i = 0; i < rows_; ++i)
		delete [] data_[i];
	delete [] data_;
}


Matrix::MatrixRow Matrix::operator[] (size_t i) {
	if (i >= 0 && i < rows_)
		return MatrixRow(cols_, data_[i]);
	else
		throw std::out_of_range("Row Index Error");
}


const Matrix::MatrixRow Matrix::operator[] (size_t i) const {
	if (i >= 0 && i < rows_)
		return MatrixRow(cols_, data_[i]);
	else
		throw std::out_of_range("Row Index Error");
}


Matrix& Matrix::operator*= (const int c) {
	for (size_t i = 0; i < rows_; ++i) {
		for (size_t j = 0; j < cols_; ++j) {
			data_[i][j] *= c;
		}
	}

	return *this;
}


bool Matrix::operator== (const Matrix& m) const {
	if (m.rows_ != rows_ || m.cols_ != cols_)
		return false;

	for (size_t i = 0; i < rows_; ++i) {
		for (size_t j = 0; j < cols_; ++j) {
			if (m.data_[i][j] != data_[i][j])
				return false;
		}
	}
	return true;	
}


bool Matrix::operator!= (const Matrix& m) const {
	return !(*this == m);		
}


size_t Matrix::getRows () const {
	return rows_;
}


size_t Matrix::getColumns () const {
	return cols_;
}


void Matrix::print_values() const {
	for (size_t i = 0; i < rows_; ++i) {
		for (size_t j = 0; j < cols_; ++j) {
			std::cout << data_[i][j] << " ";
		}
		std::cout << "\n";
	}
}
