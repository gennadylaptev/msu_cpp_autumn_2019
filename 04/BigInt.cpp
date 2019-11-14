#include "BigInt.hpp"


// Конструктор по умолчанию для нулевого объекта
BigInt::BigInt () : size_(1), sign_(true), data_(new uint8_t[1]) {
	data_[0] = 0;
}


// Конструктор из указателя на массив uint8_t и размера
BigInt::BigInt (uint8_t * data, size_t size, bool sign)
	: data_(data), size_(size), sign_(sign) {}


// Конструктор из строки
BigInt::BigInt (const std::string& str) {
	bool marker = false;			

	if (str[0] == '-') {
		sign_ = false;
		marker = true;
	}
	else if (str[0] == '+') {
		marker = true;
	}
	
	uint8_t d = marker ? 1 : 0;

	// если число начинается с нулей, то найдем индекс первой цифры, отличной от 0
	size_t start = d;
	for (size_t j = start; j < str.length(); j++) {
		
		if (str[j] != '0')
			break;
		start += 1;	
	}

	// Если у нас остались одни нули, то нужно создать массив длины 0 и поместить туда 0
	// Условимся, что ноль всегда имеет положительный знак
	
	if (str.length() - start == 0) {
		size_ = 1;
		data_ = new uint8_t[size_];
		data_[0] = 0;
		sign_ = true;
	}
	else {
		size_ = str.length() - start;
		data_ = new uint8_t[size_];
		
		const char * cstr = str.c_str();
		for (size_t k = (str.length() - 1); k != (start-1); k--) {
			// Т.к. мы приводим char к uint8_t, нужно отнять отступ,
			// чтобы из ascii кода получить нужную цифру.
			// Для удобства запишем наши цифры слева направо 
			data_[str.length()-1-k] = (uint8_t)cstr[k] - offset;
		}
	}
	
}


// Конструктор копирования
BigInt::BigInt (BigInt const& other)
	//скопируем размер и знак, аллоцируем нужное кол-во памяти
	: size_(other.size_), sign_(other.sign_),
	data_(new uint8_t[other.size_]) 
{
	for (size_t i = 0; i < size_; ++i)
		data_[i] = other.data_[i];
}


// Деструктор 
BigInt::~BigInt () {
	delete [] data_;
}


// Приведение int к BigInt
BigInt::BigInt(int x) : size_(1), sign_(x >= 0) {
	int max_div = BASE;
	x = std::abs(x);

	while (x / max_div) {
		size_++;
		max_div *= BASE;
	}
	
	data_ = new uint8_t[size_];
	for (size_t i = 0; i < size_; i++) {
		data_[i] = x % BASE;
		x = x / BASE;
	}
}


// Оператор присваивания	
BigInt& BigInt::operator= (BigInt const& other) {
	if (this != &other) {
		// удалим старые данные, заново аллоцириуем память
		// заполняем её новыми данными
		delete [] data_;
		data_ = new uint8_t[other.size_];
		size_ = other.size_;
		sign_ = other.sign_;

		for (size_t i = 0; i < size_; ++i)
			data_[i] = other.data_[i];				
	}
	return *this;
}


// Операторы сравнения
bool BigInt::operator> (BigInt const& other) const {
	if (sign_ && !(other.sign_))
		return true;
	else if (!(sign_) && other.sign_)
		return false;

	if (this->size_ > other.size_ && sign_ && other.sign_)
		return true;
	else if (size_ < other.size_ && sign_ && other.sign_)
		return false;
	else if (size_ > other.size_ && !(sign_) && !(other.sign_))
		return false;
	else if (size_ < other.size_ && !(sign_) && !(other.sign_))
		return true;
	
	// N сравнений требуется только в худшем случае
	if (sign_ && other.sign_) {
		for (size_t i = size_-1; i < size_; --i) {
			if (data_[i] > other.data_[i]) { return true;}
			else if (data_[i] < other.data_[i]) { return false; }
		}
	}
	return false;
}


bool BigInt::operator== (BigInt const& other) const {
	if (sign_ != other.sign_)
		return false;
	
	if (size_ != other.size_)
		return false;
	
	// N сравнений требуется только в худшем случае
	for (size_t i = 0; i < size_; i++) 
		if (data_[i] != other.data_[i]) { return false;}
	
	return true;
}


bool BigInt::operator< (BigInt const& other) const {
	if (!(*this > other) && (!(*this == other)))
		return true;
	else
		return false;
}


bool BigInt::operator>= (BigInt const& other) const {
	if (*this < other)
		return false;
	else
		return true;
}


bool BigInt::operator<= (BigInt const& other) const {
	if (*this > other)
		return false;
	else
		return true;
}


// Унарный минус
BigInt BigInt::operator- () const {
	BigInt tmp(*this);
	tmp.sign_ = !tmp.sign_;
	return tmp;
}


bool BigInt::abs_gt (BigInt const& other) const {			
	if (this->size_ > other.size_)
		return true;
	else if (size_ < other.size_)
		return false;

	// N сравнений требуется только в худшем случае
	for (size_t i = size_-1; i < size_; --i) {
		if (data_[i] > other.data_[i]) { return true;}
		else if (data_[i] < other.data_[i]) { return false; }
	}
	return false;
}


bool BigInt::abs_eq (BigInt const& other) const {
	if (size_ != other.size_)
		return false;
	for (size_t i = 0; i < size_; ++i) {
		if (data_[i] != other.data_[i])
			return false;
	}

	return true;
}


BigInt BigInt::operator- (BigInt const& other) {
	return _subtract(*this, other);
}


const BigInt& BigInt::operator-=(const BigInt& other) {
	*this = _subtract(*this, other);
	return *this;
}


BigInt BigInt::_subtract (BigInt const& a, BigInt const& b) {

	if (a.sign_ == b.sign_) {
		if (a == b) {return BigInt();}				
		else if (a.abs_gt(b)) {
			BigInt res = _abs_subtract(a, b);
			res.set_sign(a.sign_);
			return res;
		}
		else {
			BigInt res = _abs_subtract(b, a);
			res.set_sign(!a.sign_);
			return res;
		}
	}
	else {
		BigInt res = _abs_sum(a, b);
		if (a.sign_ && !b.sign_)
			res.set_sign(true);
		else
			res.set_sign(false);

		return res;
	}			
}


BigInt BigInt::_add (BigInt const& a, BigInt const& b) {
	
	if (a.sign_ == b.sign_) {
		BigInt res = _abs_sum(a, b);
		res.set_sign(a.sign_);
		return res;
	}
	else {
		if (a.abs_eq(b))
			return BigInt();
		else {
			if (a.abs_gt(b)) {
				BigInt res = _abs_subtract(a, b);
				res.set_sign(a.sign_);
				return res;
			}
			else {
				BigInt res = _abs_subtract(b, a);
				res.set_sign(b.sign_);
				return res;
			}
		}
	}
}


const BigInt& BigInt::operator+=(const BigInt& other) {
	*this = _add(*this, other);
	return *this;
}


BigInt BigInt::operator+ (BigInt const& other) {
	return _add(*this, other);
}


// вычитаем из большего по модулю меньшее, одинакового знака
BigInt BigInt::_abs_subtract (BigInt const& a, BigInt const& b) {

	size_t max_size = std::max(a.size_, b.size_);
	size_t min_size = std::min(a.size_, b.size_);

	size_t tmp_size = max_size;
	uint8_t z;
	uint8_t r = 0;
	size_t zero_count = 0;

	uint8_t * tmp_data = new uint8_t[max_size];

	for (size_t i = 0; i < max_size; ++i) {

		if (i < min_size) {
			if (a.data_[i] < b.data_[i] + r) {
				z = BASE + a.data_[i] - b.data_[i] - r;
				r = 1;					
			}
			else {z = a.data_[i] - b.data_[i] - r; r = 0;}
			tmp_data[i] = z;
		}

		else {
			if (a.data_[i] < r) {z = BASE + a.data_[i] - r; r = 1;}
			else {z = a.data_[i] - r; r = 0;}
			tmp_data[i] = z;
		}
		
		if (z == 0)
			zero_count++;
		else
			zero_count = 0;
	}

	// после вычитания может оказаться, что большая часть памяти занята нулями
	if (zero_count > 0) {
		if (zero_count == max_size) {
			delete [] tmp_data;					
			return BigInt();
		}
		else {
			tmp_size -= zero_count;
			uint8_t * tmp_data_2 = new uint8_t[tmp_size];
			for (size_t j = 0; j < tmp_size; j++)
				tmp_data_2[j] = tmp_data[j];

			delete [] tmp_data;
			return BigInt(tmp_data_2, tmp_size, true);
		}
	}

	else
		return BigInt(tmp_data, tmp_size, true);
}


// Складываем по модулю
BigInt BigInt::_abs_sum (BigInt const& a, BigInt const& b) {
	
	// Мы аллоцируем память макс размер + 1
	size_t max_size = std::max(a.size_, b.size_);
	size_t min_size = std::min(a.size_, b.size_);

	size_t tmp_size = max_size;
	uint8_t z;
	uint8_t r = 0;
		
	uint8_t * tmp_data = new uint8_t[max_size + 1];

	for (size_t i = 0; i < max_size+1; ++i) {
		if (i < min_size) {
			z = a.data_[i] + b.data_[i] + r;
			if (z > 9) { z = z % 10; r = 1;}
			else { r = 0;}
			tmp_data[i] = z;
		}
		else if (i < max_size) {
			if (a.size_ >= b.size_)
				tmp_data[i] = a.data_[i] + r;
			else if (a.size_ < b.size_)
				tmp_data[i] = b.data_[i] + r;
			
			r = 0;
		}
		else {
			tmp_data[i] = r;
			if (r > 0) ++tmp_size;
		}
	}	

	return BigInt(tmp_data, tmp_size, true);					
}


std::string BigInt::to_str() const {
	std::string s;
	s += (sign_ ? "" : "-");
	for (size_t i = (size_-1); i < size_; --i)
		s.push_back(data_[i] + '0');
	return s;
}


void BigInt::set_sign (bool sign) { sign_ = sign; }
bool BigInt::get_sign () const { return sign_; }

size_t BigInt::get_size () const { return size_; }


std::ostream& operator<< (std::ostream& out, const BigInt& x) {
	out << x.to_str();	
	return out;
}
