// OTUS C++ basic course homework.
// ASTNode

#pragma once

#include <cctype>
#include <iostream>
#include <string>

// Abstract Syntax Tree - јбстрактное синтетическое дерево

// ASTNode - базовый класс, описывающий узел дерева.
class ASTNode {
  public:
    //  онструктор листа - узла дерева без дочерних узлов.
    explicit ASTNode(const std::string &repr);

    //  онструктор узла дерева с 2 дочерними узлами.
    ASTNode(const std::string &repr, ASTNode *lhs, ASTNode *rhs);

    ASTNode(const ASTNode &other) = delete;

    ASTNode &operator=(const ASTNode &other) = delete;

    ~ASTNode();

    std::string repr() const { 
        return repr_;
    }

    void print(std::ostream &out) const; // ѕечать всего дерева.

  private:
    void inner_print(std::ostream &out, size_t indent) const;

    std::string repr_; // —троковое представление числа или переменной.

    ASTNode *lhs_; // Ћевый дочерний узел.
    ASTNode *rhs_; // ѕравый дочерний узел.
};
