#include <iostream>
#include <sstream>

enum op_val {
    PLUS = '+',
    MINUS = '-',
    MULT = '*',
    DIV = '/',
    END
};

// get an int (until the next delimiter)
int get_num (std::stringstream& s) {
    char symb;
    int num;

    if (!s.get(symb))
        throw std::runtime_error("Wrong format!");;
    // skip all whitespaces
    while (isspace(symb)) {
        s.get(symb);
    }

    if (isdigit(symb)) {
        s.putback(symb);
        s >> num; // get the num until the next whitespace
    }
    else if (symb == '-') {
        s >> num;
        num = -num;
        //num = -get_num (s);
    }
    else
        throw std::runtime_error("Wrong format!");

    return num;
}

void get_op (std::stringstream& s, op_val& curr_op) {
    // since we call get_op after parsing a number
    // it's totally okay to get no operators --
    // we reached the end of the stream
    char symb;
    if (!s.get(symb)) {
        curr_op = END;
        return;
    }

    while (isspace(symb)) {

        if (!s.get(symb)) {
            curr_op = END;
            std::cout << std::string(1, symb) << "\n";
            return;
        }
    }
    switch (symb) {
        case '+':
        case '-':
        case '*':
        case '/':
            curr_op = op_val(symb);
            break;
        default:
            throw std::runtime_error("Wrong format!");
    }
}

int mult (std::stringstream& s, op_val& curr_op) {
    int left = get_num(s);
    get_op(s, curr_op);

    while (true) {
        switch (curr_op) {
            case MULT:
                left *= get_num(s);
                get_op(s, curr_op);
                break;
            case DIV:
                left /= get_num(s);
                // will automatically throw Floating point exception
                get_op(s, curr_op);
                break;
            default:
                return left;
        }
    }
}

int sum (std::stringstream& s, op_val& curr_op) {
    int left = mult(s, curr_op);

    while (true) {

        switch (curr_op) {
            case PLUS:
                left += mult(s, curr_op);
                break;
            case MINUS:
                left -= mult(s, curr_op);
                break;
            case END:
                return left;
        }
    }

}

int main (int argc, char * argv[]) {

    if (argc != 2) {
        throw std::runtime_error("Invalid number of arguments!");
        return 1;
    }
    std::stringstream s(argv[1]);
    op_val curr_op; // store current operation

    int res = sum(s, curr_op);

    std::cout << res << "\n";

    return 0;
}