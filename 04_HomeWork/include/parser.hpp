#pragma once

#include <istream>

#include "astnode.hpp"
#include "lexer.hpp"

class Parser {
  public:
    explicit Parser(Lexer &lexer)
        : lexer_(lexer), tok_(Lexer::Token::Unknown)
    {  }

    Parser(const Parser &other) = delete;

    Parser &operator=(const Parser &other) = delete;

    ~Parser() = default;

    ASTNode *parse();

  private:
    void next_token();

    // Следующие три метода реализуют разбор арифметических выражений.
    ASTNode *expr(); // Сложение или вычетание.

    ASTNode *term(); // Умножение или деление.

    ASTNode *prim(); // Число или переменная.

    Lexer &lexer_; // Связь с Лексером.
    Lexer::Token tok_; // Текущий токен.
};
