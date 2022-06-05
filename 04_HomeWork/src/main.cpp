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
    // Add - Знак плюс "+"
    // Sub - Знак минус "-"
    // Mul - Знак умножения "*"
    // Div - Знак деления "/"
    // Variable - Буквенная переменная.

    // Without implementation of these classes this application works only with numbers
    

    // Создаём объекты классов.
    Lexer lexer(std::cin);
    Parser parser(lexer);

    ASTNode *ast = parser.parse(); // Начало парсинга.
    if (ast) {
         ast->print(std::cout); // Начало печати всего дерева.
    }
    else {
        std::cout << "Unable to form the tree because of errors!" << std::endl;
        return 1;
    }

    std::cout << "-- Finish --" << std::endl;

    return 0;
}
