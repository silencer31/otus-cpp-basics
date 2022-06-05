#include "parser.hpp"
#include "number.hpp"
#include "variable.hpp"
#include "add.hpp"
#include "sub.hpp"
#include "mul.hpp"
#include "div.hpp"

#include <iostream>

using Token = Lexer::Token;

// ������ ��������.
ASTNode *Parser::parse() {
    return expr();
}

// �������� ��������� ����� �� �������.
void Parser::next_token() { 
    tok_ = lexer_.next_token();
}

// ��������� �������� ��� ���������.
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
                root = new Add(root, next_node); // ���������� �������� � ���� ��������� �����.
                break;
            case '-':
                next_node = term();
                if (next_node == nullptr) {
                    return nullptr;
                }
                root = new Sub(root, next_node); // ���������� ��������� � ���� ��������� �����.
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

// ��������� ��������� ��� �������.
ASTNode *Parser::term() {
    // parse multiplication and division
    ASTNode *root = prim(); // ���� �����.
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
                root = new Mul(root, next_node); // ���������� ��������� � ���� ��������� �����.
                break;
            case '/':
                next_node = prim();
                if (next_node == nullptr) {
                    return nullptr;
                }
                root = new Div(root, next_node); // ���������� ������� � ���� ��������� �����.
                break;
            default:
                return root; // ���� ��������, �� �� * ��� /, ������ ���������� �����.
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