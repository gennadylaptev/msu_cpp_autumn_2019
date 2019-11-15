#include "Serializer.hpp"
#include "Deserializer.hpp"
#include "Error.hpp"
#include <cstdint>

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

	// В serialize передаем ссылку на Serializer
	// применяем его оператор ()
	// который вызывает метод process
	// который принимает поля Data в качестве аргументов
    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c); 
    }

	// здесь мы записываем в соотв. поле
	// соотв. данные из потока
    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};
