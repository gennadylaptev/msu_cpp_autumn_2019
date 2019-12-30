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
        // to correctly handle "-" case
        num = -get_num(s);
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

void process_args_for_compute(int argc, char * argv[], std::stringstream& s) {
   // check the number of arguments, return a stringstream if everything is okay
   if (argc != 2) {
        throw std::runtime_error("Invalid number of arguments!");
    }
   s = std::stringstream(argv[1]);
   return;
}

int compute(std::stringstream& s) {
    // evaluate an expression in a stringstream
    op_val curr_op;
    int res = sum(s, curr_op);
    return res;
}

int main (int argc, char * argv[]) {

    try {
        std::stringstream s;
        process_args_for_compute (argc, argv, s);

        int res = compute(s);
        std::cout << res << "\n";
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << " Failed to obtain the result." << "\n";
    }

    return 0;
}