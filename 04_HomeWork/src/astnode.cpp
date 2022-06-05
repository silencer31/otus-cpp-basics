#include "astnode.hpp"

ASTNode::ASTNode(const std::string &repr)
    : repr_(repr)
    , lhs_{nullptr}
    , rhs_{nullptr} {}

ASTNode::ASTNode(const std::string &repr, ASTNode *lhs, ASTNode *rhs)
    : repr_(repr)
    , lhs_{lhs}
    , rhs_{rhs} {}

ASTNode::~ASTNode() {
    delete lhs_;
    delete rhs_;
}

// Начало печати всего дерева.
void ASTNode::print(std::ostream &out) const { 
    inner_print(out, 0);
}

// Если есть 2 связанных узла, то печатаем и их. Иначе только число или перенную.
void ASTNode::inner_print(std::ostream &out, size_t indent) const {
    if (lhs_) {
        lhs_->inner_print(out, indent + 1);
    }

    for (size_t i = 0; i < indent; ++i) {
        out << "    ";
    }

    out << repr_ << '\n';

    if (rhs_) {
        rhs_->inner_print(out, indent + 1);
    }
}
