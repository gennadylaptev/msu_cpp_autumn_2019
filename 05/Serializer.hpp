#include "Error.hpp"
#include <iostream>
#include <cstdint>


class Serializer
{
	   
	static constexpr char Separator = ' ';
	std::ostream &out_;

	public:
		explicit Serializer(std::ostream& out)
		    : out_(out)	{}

		template <class T>
		Error save(T& object)
		{
		    return object.serialize(*this);
		}

		template <class... ArgsT>
		Error operator () (ArgsT&&... args)
		{
		    return process(std::forward<ArgsT>(args)...);
		}
		
	private:
		// process использует variadic templates
		// здесь мы пытаемся сериализовать переданные данные
		// = записать в поток в виде строк
		// т.к. в общем случае мы не знаем, сколько будет передано элементов
		// будем записывать их в поток рекурсивно
		// т.е. брать первый элемент, записывать его и
		// вызывать process на оставшихся
		// критерий остановки - остался один элемент
		// тогда уже мы возращаем объект класса Error
		// также, мы возращаем Error::CorruptedArchive, 
        // когда сталкиваемся с объектом неправильного типа
		template <class T, class... ArgsT>
		Error process (T&& fst, ArgsT&&... args) {
			if (write_symbol(fst) == Error::NoError) {
				return process (std::forward<ArgsT>(args)...);
			}
			else
				return Error::CorruptedArchive;
		}


		template <class T>
		Error process (T&& lst) {
			return write_symbol(lst);
		}

		// Пишем в поток
		Error write_symbol (bool& x) {
			out_ << (x ? "true" : "false") << Separator;
			return Error::NoError;
		}

		Error write_symbol (uint64_t& x) {
			out_ << x << Separator;
			return Error::NoError;
		}

};
