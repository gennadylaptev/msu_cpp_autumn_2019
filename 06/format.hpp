#include <iostream>
#include <string>
#include <sstream>
#include <vector>


template <class T>
std::string to_string(T&& x) {
    std::stringstream stream;
    stream << x;
    return stream.str();
}

template <class... argsT>
std::string format(const std::string & str, argsT && ... args) {
    size_t i = 0;
    std::stringstream S;
    std::string buffer;

    // считаем все параметры в вектор через initializer_list
    std::vector<std::string> params = { to_string(std::forward<argsT>(args))... };
    
    while (i < str.length()) {
        if (str[i] == '{') {
            size_t k = 1;
            
            while (str[i+k] != '}') {
                if (!std::isdigit(str[i+k]))
                    throw std::runtime_error("Неправильный формат!");
                buffer += str[i+k];
                k++;
            }
            
            try {
                size_t param_ind = std::stoi(buffer);
                if (param_ind >= params.size())
                    throw std::runtime_error("Неправильный формат!");
                S << params[param_ind];
            }
            catch (std::invalid_argument& e) {
                throw std::runtime_error("Неправильный формат!");
            }
            
            buffer.clear();
            i = i + k + 1;
        }

        else {
            if (str[i] == '}')
                throw std::runtime_error("Неправильный формат!");
            S << str[i];
            i++;
        }
    }
    
    return S.str();
}
