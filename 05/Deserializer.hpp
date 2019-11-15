#include "Error.hpp"
#include <iostream>
#include <string>
#include <cstdint>


class Deserializer
{
	   
	static constexpr char Separator = ' ';
	std::istream & in_;

	public:
		explicit Deserializer(std::istream& in)
		    : in_(in) {}

		template <class T>
		Error load (T& object)
		{
		    return object.deserialize(*this);
		}
		
		// здесь мы принимаем поля структуры
		template <class... ArgsT>
		Error operator () (ArgsT&&... args)
		{	
			// перемещаем поля в метод process
		    return process(std::forward<ArgsT>(args)...);
		}
		
	
	private:
		template <class T, class... ArgsT>
		Error process (T&& fst, ArgsT&&... args) {
			if (read_val(fst) == Error::CorruptedArchive) {
				return Error::CorruptedArchive; 
			}
			else
				return process(std::forward<ArgsT>(args)...);
		}

		template <class T>
		Error process (T&& lst) {
			return read_val(lst);
		}


		// Читаем из потока
		Error read_val (bool & val) {
			std::string text;
			in_ >> text;

			if (text == "true")
				val = true;
			else if (text == "false")
				val = false;
			else
				return Error::CorruptedArchive;

			return Error::NoError;
		}


		Error read_val (uint64_t & val) {
			std::string text;
			in_ >> text;

			// по условию у нас беззнаковый тип
			if (text[0] == '-') { return Error::CorruptedArchive; }

			try {
				val = std::stoull(text);
			}
			catch (std::exception& e) {
				std::cout << e.what() << std::endl;
				return Error::CorruptedArchive;
			}
			return Error::NoError;
		}
};
