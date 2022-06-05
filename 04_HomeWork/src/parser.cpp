#include "parser.hpp"
#include "number.hpp"
#include "variable.hpp"
#include "add.hpp"
#include "sub.hpp"
#include "mul.hpp"
#include "div.hpp"

#include <iostream>

using Token = Lexer::Token;

// Начало парсинга.
ASTNode *Parser::parse() {
    return expr();
}

// Получить следующий токен от Лексера.
void Parser::next_token() { 
    tok_ = lexer_.next_token();
}

// Обработка сложения или вычитания.
ASTNode *Parser::expr() { 
    // parse addition and subsctruction
    ASTNode *root = term();
    if (root == nullptr) {
        return nullptr;
    }

    ASTNode* next_node = nullptr;

    for (;;) {
        switch (tok_) {
        case Token::Operator: {
            std::string op = lexer_.get_operator();
            
            switch (op.front()) {
            case '+':
                next_node = term();
                if (next_node == nullptr) {
                    return nullptr;
                }
                root = new Add(root, next_node); // Выставляем сложение и берём следующее число.
                break;
            case '-':
                next_node = term();
                if (next_node == nullptr) {
                    return nullptr;
                }
                root = new Sub(root, next_node); // Выставляем вычитание и берём следующее число.
                break;
            default: 

                return root;
            }
            break;
        }
        case Token::Rbrace: {
            //std::cout << "R brace" << std::endl;
            next_token();
            return root;
            break;
        }
        default:
            if (root != nullptr) {
                if (tok_ != Token::End) {
                    std::cout << "Error! Operator of right brace expected!" << std::endl;
                    return nullptr;
                }
            }
            return root;
        }
    }
}

// Обработка умножения или деления.
ASTNode *Parser::term() {
    // parse multiplication and division
    ASTNode *root = prim(); // Берём число.
    if (root == nullptr) {
        return nullptr;
    }

    ASTNode *next_node = nullptr;

    for (;;) {
        switch (tok_) {
        case Token::Operator: {
            std::string op = lexer_.get_operator();

            switch (op.front()) {
            case '*':
                next_node = prim();
                if (next_node == nullptr) {
                    return nullptr;
                }
                root = new Mul(root, next_node); // Выставляем умножение и берём следующее число.
                break;
            case '/':
                next_node = prim();
                if (next_node == nullptr) {
                    return nullptr;
                }
                root = new Div(root, next_node); // Выставляем деление и берём следующее число.
                break;
            default:
                return root; // Если оператор, но не * или /, просто возвращаем число.
            }
                       
            break;
        }
        case Token::Rbrace: {
            //std::cout << "R brace" << std::endl;
            next_token();
            return root;
            break;
        }
        default:
            if (root != nullptr) {
                if (tok_ != Token::End) {
                    std::cout << "Error! Operator of right brace expected!" << std::endl;
                    return nullptr;
                }
                
            }

            return root;
        }
    }
}

ASTNode *Parser::prim() {
    // parse numbers and names
    ASTNode *node = nullptr;
 
    next_token();

    switch (tok_) {
    case Token::Number:
        node = new Number(lexer_.get_number());
        break;
    case Token::Name:
        node = new Variable(lexer_.get_name());
        break;
    case Token::Lbrace: {
        //std::cout << "L brace" << std::endl;
        return expr();
        break;
    }
    default:
        std::cout << "Error! Number, variable or left brace expected!" << std::endl;
        return nullptr;
        break;
    }

    next_token();

    return node;
}