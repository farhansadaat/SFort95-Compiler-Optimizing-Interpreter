#include "ast.h"
#include <iostream>

Value IntNode::eval(std::map<std::string, Value>&) {
    return {value};
}

Value VarNode::eval(std::map<std::string, Value>& env) {
    return env[name];
}

BinOpNode::BinOpNode(char o, AST l, AST r) : op(o), left(l), right(r) {}

Value BinOpNode::eval(std::map<std::string, Value>& env) {
    Value a = left->eval(env);
    Value b = right->eval(env);
    if (op == '+') return {a.i + b.i};
    if (op == '-') return {a.i - b.i};
    if (op == '*') return {a.i * b.i};
    return {a.i / b.i};
}

AssignNode::AssignNode(const std::string& n, AST e) : name(n), expr(e) {}

Value AssignNode::eval(std::map<std::string, Value>& env) {
    env[name] = expr->eval(env);
    return {};
}

PrintNode::PrintNode(AST e) : expr(e) {}

Value PrintNode::eval(std::map<std::string, Value>& env) {
    Value v = expr->eval(env);
    std::cout << v.i << std::endl;
    return {};
}
