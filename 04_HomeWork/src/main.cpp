// OTUS C++ Basic course homework skeleton.
// Lexer using example

#include <iostream>

#include "astnode.hpp"
#include "lexer.hpp"
#include "parser.hpp"

int main() {

    std::cout << "-- Start --" << std::endl;
    // TODO
    // Implement the next classes:
    // Add - ���� ���� "+"
    // Sub - ���� ����� "-"
    // Mul - ���� ��������� "*"
    // Div - ���� ������� "/"
    // Variable - ��������� ����������.

    // Without implementation of these classes this application works only with numbers
    

    // ������ ������� �������.
    Lexer lexer(std::cin);
    Parser parser(lexer);

    ASTNode *ast = parser.parse(); // ������ ��������.
    if (ast) {
         ast->print(std::cout); // ������ ������ ����� ������.
    }
    else {
        std::cout << "Unable to form the tree because of errors!" << std::endl;
        return 1;
    }

    std::cout << "-- Finish --" << std::endl;

    return 0;
}
