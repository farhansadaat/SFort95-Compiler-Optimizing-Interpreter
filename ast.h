#ifndef AST_H
#define AST_H

#include <memory>
#include <map>
#include <string>

struct Value {
    int i = 0;
};

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual Value eval(std::map<std::string, Value>& env) = 0;
};

using AST = std::shared_ptr<ASTNode>;

class IntNode : public ASTNode {
    int value;
public:
    IntNode(int v) : value(v) {}
    Value eval(std::map<std::string, Value>&) override;
};

class VarNode : public ASTNode {
    std::string name;
public:
    VarNode(const std::string& n) : name(n) {}
    Value eval(std::map<std::string, Value>& env) override;
};

class BinOpNode : public ASTNode {
    char op;
    AST left, right;
public:
    BinOpNode(char o, AST l, AST r);
    Value eval(std::map<std::string, Value>& env) override;
};

class AssignNode : public ASTNode {
    std::string name;
    AST expr;
public:
    AssignNode(const std::string& n, AST e);
    Value eval(std::map<std::string, Value>& env) override;
};

class PrintNode : public ASTNode {
    AST expr;
public:
    PrintNode(AST e);
    Value eval(std::map<std::string, Value>& env) override;
};

#endif
