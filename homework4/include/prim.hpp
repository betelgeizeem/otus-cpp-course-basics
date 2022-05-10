#pragma once

#include <string>

#include "astnode.hpp"

class Number : public ASTNode {
  public:
    Number(int val)
        : ASTNode(std::to_string(val))
        , val_(val) {}

    int value() const { return val_; }

  private:
    int val_;
};

class Variable : public ASTNode {
  public:
    Variable(std::string str)
        : ASTNode(str)
        , str_(str) {}

    std::string value() const { return str_; }

  private:
    std::string str_;
};
