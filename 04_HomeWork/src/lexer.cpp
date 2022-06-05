// OTUS C++ Basic course homework skeleton.
// Lexer implementation

#include "lexer.hpp"

#include <cctype>

#include <iostream>


// Данный метод пытается найти следующий токен в потоке входных данных и возвращает тип токена.
Lexer::Token Lexer::next_token()
{
    for (;;) {
        switch (state_) {
        case State::End:
            return Token::End;

        case State::ReadNumber:
            if (end()) {
                state_ = State::End;
                return Token::Number;
            }

            if (std::isdigit(ch_)) {
                number_ = 10 * number_ + (ch_ - '0');
                state_ = State::ReadNumber;
                next_char();
                break;
            }

            state_ = State::Empty;
            return Token::Number;

        case State::ReadName:
            if (end()) {
                state_ = State::End;
                return Token::Name;
            }

            // Имя переменной может быть из букв и цифр.
            if (std::isalpha(ch_) || std::isdigit(ch_)) {
                name_ += ch_;
                next_char();
                break;
            }

            state_ = State::Empty;
            return Token::Name;

        case State::Empty: // Анализ следующего символа из входного потока.
            if (end()) {
                state_ = State::End;
                return Token::End;
            }
            
            if (std::isspace(ch_)) { // Остаёмся в состоянии State::Empty и переходим на следующую итерацию цикла в поиске символа - не пробела.
                next_char(); 
                break;
            }

            if (isoperator(ch_)) {
                operator_ = ch_;
                next_char();
                return Token::Operator;
            }

            if (ch_ == '(') {
                next_char();
                return Token::Lbrace;
            }

            if (ch_ == ')') {
                next_char();
                return Token::Rbrace;
            }

            if (std::isdigit(ch_)) { // Прочитали символ числа.
                number_ = ch_ - '0';
                state_ = State::ReadNumber;
                next_char();
                break;
            }

            if (std::isalpha(ch_)) { // Прочитали символ переменной.
                name_ = ch_;
                state_ = State::ReadName;
                next_char();
                break;
            }
        }
    }
}
