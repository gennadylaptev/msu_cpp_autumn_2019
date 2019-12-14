#include <iostream>
#include <sstream>
#include "MyVector.hpp"

std::string yes (" passed!\n");
std::string no (" not passed!\n");


struct Custom_int {
    int value;
    // set default value to smth != 0
    Custom_int (int x = 9) : value(x) {}
};

struct Custom_int_print {

    std::stringstream stream;
    int value;
    
    Custom_int_print (int x = 9) : value (x) {}
    
    Custom_int_print (const Custom_int_print& other) {
        stream << "copying";
        value = other.value;
    }
    
    Custom_int_print (Custom_int_print&& other) {
        stream << "moving";
        value = other.value;
        other.value = 0;
    }
    
    ~Custom_int_print () {
        stream.str("");
        stream.clear();
    }
    
};


std::ostream& operator<< (std::ostream& out, const Custom_int& x) {
    out << x.value;
    return out;
}

void test_iterator () {
    std::string name ("Iterator");
    
    std::stringstream s;
    MyVector<int> v(3);
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    
    for (auto i = v.begin(); i != v.end(); ++i )
        s << *i;
    
    if (s.str() == "012")
        std::cout << name << yes;
    else
        std::cout << name << no;
}

void test_reversed () {
    std::string name ("Reversed");
    
    std::stringstream s;
    MyVector<int> v(3);
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    
    for (auto i = v.rbegin(); i != v.rend(); ++i )
        s << *i;
    
    if (s.str() == "210")
        std::cout << name << yes;
    else
        std::cout << name << no;
}

void test_copy() {
    std::string name ("Copy constructor");

    std::stringstream s;
    MyVector<int> b(3);
          
    b.push_back(0);
    b.push_back(1);
    b.push_back(2);
    
    MyVector<int> a(b);
    
    for (auto i = a.begin(); i != a.end(); ++i )
        s << *i;
    
    for (auto j = b.begin(); j != b.end(); ++j )
        s << *j;
    
    if (s.str() == "012012")
        std::cout << name << yes;
    else
        std::cout << name << no;

}

void test_assign() {
    std::string name ("Assignment operator");
    std::stringstream s;
    MyVector<int> b(3);
          
    b.push_back(0);
    b.push_back(1);
    b.push_back(2);
    
    MyVector<int> a = b;
    
    for (auto i = a.begin(); i != a.end(); ++i )
        s << *i;
    
    for (auto j = b.begin(); j != b.end(); ++j )
        s << *j;
    
    if (s.str() == "012012")
        std::cout << name << yes;
    else
        std::cout << name << no;
}

void test_reserve_1 () {
    std::string name ("Reserve_1");

    MyVector<int> b(3);
    b.push_back(0);
    b.push_back(1);
    b.push_back(2);

    b.reserve(10);
    
    if (b.capacity() == 10)
        std::cout << name << yes;
    else
        std::cout << name << no;    
}

void test_reserve_2 () {
    std::string name ("Reserve_2");

    MyVector<int> b(3);
    b.push_back(0);
    b.push_back(1);
    b.push_back(2);

    b.reserve(1);
    
    if (b.capacity() == 3)
        std::cout << name << yes;
    else
        std::cout << name << no;    
}

void test_pop_back () {
    std::string name ("Pop_back");
    std::stringstream s;
    
    MyVector<int> b(3);
    b.push_back(0);
    b.push_back(1);
    b.push_back(2);

    b.pop_back();
    
    for (auto i = b.begin(); i != b.end(); ++i )
        s << *i;
    
    if (s.str() == "01")
        std::cout << name << yes;
    else
        std::cout << name << no;    
}

void test_resize_1 () {
    std::string name ("Resize_1");
    std::stringstream s;
    
    MyVector<int> b(3);
    b.push_back(0);
    b.push_back(1);
    b.push_back(2);

    b.resize(2);
    
    for (auto i = b.begin(); i != b.end(); ++i )
        s << *i;
    
    if (s.str() == "01")
        std::cout << name << yes;
    else
        std::cout << name << no;    
}

void test_resize_2 () {
    std::string name ("Resize_2");
    std::stringstream s;
    
    MyVector<Custom_int> b(5);
    b.push_back(Custom_int(7));
    b.push_back(Custom_int(6));
    b.push_back(Custom_int(5));
    b.push_back(Custom_int(4));
    b.push_back(Custom_int(3));

    b.resize(6);
    
    for (auto i = b.begin(); i != b.end(); ++i )
        s << *i;
    
    if (s.str() == "765439")
        std::cout << name << yes;
    else
        std::cout << name << no;    
}

void test_resize_3 () {
    std::string name ("Resize_3");
    std::stringstream s;
    
    MyVector<Custom_int> b(5);
    b.push_back(Custom_int(7));
    b.push_back(Custom_int(6));
    b.push_back(Custom_int(5));
    b.push_back(Custom_int(4));
    b.push_back(Custom_int(3));

    b.resize(20);
    
    for (auto i = b.begin(); i != b.end(); ++i )
        s << *i;
        
    if (s.str() == "76543999999999999999")
        std::cout << name << yes;
    else
        std::cout << name << no;    
}

void test_resize_4 () {
    std::string name ("Resize_4");
    std::stringstream s;
    
    MyVector<Custom_int> b(5);
    b.push_back(Custom_int(7));
    b.push_back(Custom_int(6));
    b.push_back(Custom_int(5));
    b.push_back(Custom_int(4));
    b.push_back(Custom_int(3));
    
    Custom_int x = Custom_int(2);

    b.resize(6, x);
    
    for (auto i = b.begin(); i != b.end(); ++i )
        s << *i;
    
    if (s.str() == "765432")
        std::cout << name << yes;
    else
        std::cout << name << no;    
}

void test_resize_5 () {
    std::string name ("Resize_5");
    std::stringstream s;
    
    MyVector<Custom_int> b(5);
    b.push_back(Custom_int(7));
    b.push_back(Custom_int(6));
    b.push_back(Custom_int(5));
    b.push_back(Custom_int(4));
    b.push_back(Custom_int(3));
    
    Custom_int x = Custom_int(2);

    b.resize(20, x);
    
    for (auto i = b.begin(); i != b.end(); ++i )
        s << *i;
    
    if (s.str() == "76543222222222222222")
        std::cout << name << yes;
    else
        std::cout << name << no;    
}

void test_pushback_lvalue () {
    std::string name ("Push_back lvalue");
    MyVector<Custom_int_print> b(1);
    Custom_int_print x = Custom_int_print(7);
    b.push_back(x);
    if (b[0].stream.str() == "copying")
        std::cout << name << yes;
    else
        std::cout << name << no;
}

void test_pushback_rvalue () {
    std::string name ("Push_back rvalue");
    MyVector<Custom_int_print> b(1);
    b.push_back(Custom_int_print(7));
    
    if (b[0].stream.str() == "moving")
        std::cout << name << yes;
    else
        std::cout << name << no;
}

void test_iterator_1 () {
    std::string name ("Iterator_1");
    MyVector<int> b(3);
    b.push_back(0);
    b.push_back(1);
    b.push_back(2);
    b.push_back(3);
    b.push_back(4);

    auto it = b.begin();
    auto it2 = 2 + it;

    if (*it2 == 2)
        std::cout << name << yes;
    else
        std::cout << name << no;
}

void test_iterator_2 () {
    std::string name ("Iterator_2");
    MyVector<int> b(3);
    b.push_back(0);
    b.push_back(1);
    b.push_back(2);
    b.push_back(3);
    b.push_back(4);

    auto it = b.begin();
    auto it2 = it + 2;

    if (*it2 == 2)
        std::cout << name << yes;
    else
        std::cout << name << no;
}

void test_init_list () {
    std::string name ("Init list");
    std::stringstream s;
    MyVector<int> b = {1,2,3,4,5,6};
    
    for (const auto& x : b)
        s << x;    
    
    if (s.str() == "123456")
        std::cout << name << yes;
    else
        std::cout << name << no;
}

int main() {
    
    
    test_iterator ();
    test_reversed ();
    test_copy ();
    test_assign ();
    test_reserve_1 ();
    test_reserve_2 ();
    
    test_pop_back ();
    test_resize_1 ();
    test_resize_2 ();
    test_resize_3 ();
    test_resize_4 ();
    test_resize_5 ();
    
    test_pushback_lvalue ();
    test_pushback_rvalue ();
    
    test_iterator_1 ();
    
    test_init_list();
   
    
    return 0;
}
