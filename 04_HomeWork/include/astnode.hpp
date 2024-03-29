// OTUS C++ basic course homework.
// ASTNode

#pragma once

#include <cctype>
#include <iostream>
#include <string>

// Abstract Syntax Tree - ����������� ������������� ������

// ASTNode - ������� �����, ����������� ���� ������.
class ASTNode {
  public:
    // ����������� ����� - ���� ������ ��� �������� �����.
    explicit ASTNode(const std::string &repr);

    // ����������� ���� ������ � 2 ��������� ������.
    ASTNode(const std::string &repr, ASTNode *lhs, ASTNode *rhs);

    ASTNode(const ASTNode &other) = delete;

    ASTNode &operator=(const ASTNode &other) = delete;

    ~ASTNode();

    std::string repr() const { 
        return repr_;
    }

    void print(std::ostream &out) const; // ������ ����� ������.

  private:
    void inner_print(std::ostream &out, size_t indent) const;

    std::string repr_; // ��������� ������������� ����� ��� ����������.

    ASTNode *lhs_; // ����� �������� ����.
    ASTNode *rhs_; // ������ �������� ����.
};
