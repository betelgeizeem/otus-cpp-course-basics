#pragma once

#include <string>

#include "astnode.hpp"

class Add : public ASTNode {
  public:
    Add(ASTNode* node1, ASTNode* node2)
        : ASTNode("+", node1, node2) {};
};

class Sub : public ASTNode {
  public:
    Sub(ASTNode* node1, ASTNode* node2)
        : ASTNode("-", node1, node2) {};
};
