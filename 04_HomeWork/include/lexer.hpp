// OTUS C++ Basic course homework skeleton.
// Lexer interface

#pragma once

#include <istream>
#include <string>

#include <iostream>

// На вход лексическому анализатору (лексеру) подаются символы, на выходе он формирует токены, которые представляют собой элементарные кирпичики

// Lexer - класс, описывающий лексический анализатор.
// Анализ содержимого входной строки и превращение этих символов в токены для парсера.
class Lexer {
  public:

    // Разновидности токенов.
    enum class Token {
        Number,     // Возвращаем после окончания чтения числа из потока данных.
        Operator,   // Возвращаем после чтения одного из возможных математических операторов.
        End,        // Возвращаем если достигнут конец файла или конец строки.
        Lbrace,     // Левая скобка
        Rbrace,     // Правая скобка
        Name,       // Переменная
        Unknown
    };

    explicit Lexer(std::istream &in);

    Lexer(const Lexer &other) = delete;

    Lexer &operator=(const Lexer &other) = delete;

    // Данный метод пытается найти следующий токен в потоке входных данных и возвращает тип токена.
    Token next_token();

    int get_number() const { return number_; }

    std::string get_operator() const { return operator_; }

    std::string get_name() const { return name_; }

  protected:
    bool isbrace(char ch) const;

    bool isoperator(char ch) const;

  private:

      // Виды внутренних состояний лексера.
    enum class State {
        Empty,      // Ничего ещё нет.
        ReadNumber, // Читаем число.
        ReadName,   // Читаем имя переменной.
        End,
    };

    char next_char();
    bool end() const;

    State state_; // Внутреннее состояние лексера.
    std::string name_; // Прочитанная переменная.
    int number_; // Число, полученное из потока данных.
    std::string operator_; // Прочитанный символ оператора.
    char ch_;   // Прочитанный символ из входного потока.
    std::istream &in_; // Входной поток данных.
};

// Конструктор.
inline Lexer::Lexer(std::istream &in)
    : state_(State::Empty)
    , number_(0)
    , in_(in) 
{
    next_char(); // Сразу читаем первый символ из входного потока.
}

// Чтение следующего символа из входного потока.
inline char Lexer::next_char()
{
    in_.get(ch_);
    return ch_;
}

// Достигнут ли конец входного потока данных.
inline bool Lexer::end() const
{ 
    return in_.eof() || ch_ == '\n';
}

// Является ли символ скобкой.
inline bool Lexer::isbrace(char ch) const
{
    return ch == '(' || ch == ')';
}

// Является ли символ математеческим оператором.
inline bool Lexer::isoperator(char ch) const
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}
