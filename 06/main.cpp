#include <cassert>
#include "format.hpp"

bool test1 () {
    std::string msg("базовый тест");
    try {
        if (format("p0: {0}; p1: {1}; p2: {2}", '0', 1, "2") == "p0: 0; p1: 1; p2: 2") {
            std::cout << "Пройден: " << msg << "\n";
            return true;
        }
        else {
            std::cout << "Не пройден: " << msg << "\n";
            return false;
        } 
    }
    catch (std::runtime_error& e) {
        std::cout << "Не пройден: " << msg << "\n";
        return false;
    }
}

bool test2 () {
    std::string msg("одинокая }");
    try {
        std::string s = format("abc 0}", '1');
        std::cout << "Не пройден: " << msg << "\n";
        return false;
    }
    catch (std::runtime_error& e) {
        std::cout << "Пройден: " << msg << "\n";
        return true;
    }
}

bool test3 () {
    std::string msg("Несколько одиноких }");
    try {
        std::string s = format("abc}}} 0}", '1');
        std::cout << "Не пройден: " << msg << "\n";
        return false;
    }
    catch (std::runtime_error& e) {
        std::cout << "Пройден: " << msg << "\n";
        return true;
    }
}

bool test4 () {
    std::string msg("Не закрытая }");
    try {
        std::string s = format("abc {0}}", '1');
        std::cout << "Не пройден: " << msg << "\n";
        return false;
    }
    catch (std::runtime_error& e) {
        std::cout << "Пройден: " << msg << "\n";
        return true;
    }
}

bool test5 () {
    std::string msg("Не число внутри {}");
    try {
        std::string s = format("{abc }", '1');
        std::cout << "Не пройден: " << msg << "\n";
        return false;
    }
    catch (std::runtime_error& e) {
        std::cout << "Пройден: " << msg << "\n";
        return true;
    }
}

bool test6 () {
    std::string msg("Пустые {}");
    try {
        std::string s = format("{} abc", '1');
        std::cout << "Не пройден: " << msg << "\n";
        return false;
    }
    catch (std::runtime_error& e) {
        std::cout << "Пройден: " << msg << "\n";
        return true;
    }
}

bool test7 () {
    std::string msg("Одинокая {");
    try {
        std::string s = format("{ abc", '1');
        std::cout << "Не пройден: " << msg << "\n";
        return false;
    }
    catch (std::runtime_error& e) {
        std::cout << "Пройден: " << msg << "\n";
        return true;
    }
}

bool test8 () {
    std::string msg("Незакрытая {");
    try {
        std::string s = format("{0} {abc", '1');
        std::cout << "Не пройден: " << msg << "\n";
        return false;
    }
    catch (std::runtime_error& e) {
        std::cout << "Пройден: " << msg << "\n";
        return true;
    }
}

bool test9 () {
    std::string msg("Некорректное число параметров");
    try {
        std::string s = format("{0} {1} {2}", '1');
        std::cout << "Не пройден: " << msg << "\n";
        return false;
    }
    catch (std::runtime_error& e) {
        std::cout << "Пройден: " << msg << "\n";
        return true;
    }
}

bool test10 () {
    std::string msg("Лишние параметры");
    try {
        if (format("p0: {0} {0} {0}", '0', 1, "2") == "p0: 0 0 0") {
            std::cout << "Пройден: " << msg << "\n";
            return true;
        }
        else {
            std::cout << "Не пройден: " << msg << "\n";
            return false;
        } 
    }
    catch (std::runtime_error& e) {
        std::cout << "Не пройден: " << msg << "\n";
        return false;
    }
}
int main () {

    size_t passed = 0;
    
    if (test1()) passed++;
    if (test2()) passed++;
    if (test3()) passed++;
    if (test4()) passed++;
    if (test5()) passed++;
    if (test6()) passed++;
    if (test7()) passed++;
    if (test8()) passed++;
    if (test9()) passed++;
    if (test10()) passed++;
    
    std::cout << "Пройдено тестов: " << passed << "/10\n";
    
    return 0;
} 
