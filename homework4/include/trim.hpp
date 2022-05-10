#pragma once

#include <string>

#include "astnode.hpp"

class Mul : public ASTNode {
  public:
    Mul(ASTNode* node1, ASTNode* node2)
        : ASTNode("*", node1, node2) {};
};

class Div : public ASTNode {
  public:
    Div(ASTNode* node1, ASTNode* node2)
        : ASTNode("/", node1, node2) {};
};
