#include "parser.h"

static Token curr;
static std::istream* input;
static int line;

static void advance() {
    curr = getNextToken(*input, line);
}

static AST parseFactor() {
    if (curr.type == TokenType::ICONST) {
        int v = std::stoi(curr.lexeme);
        advance();
        return std::make_shared<IntNode>(v);
    }
    if (curr.type == TokenType::IDENT) {
        std::string name = curr.lexeme;
        advance();
        return std::make_shared<VarNode>(name);
    }
    return nullptr;
}

static AST parseExpr() {
    AST left = parseFactor();
    while (curr.type == TokenType::PLUS || curr.type == TokenType::MINUS) {
        char op = curr.lexeme[0];
        advance();
        AST right = parseFactor();
        left = std::make_shared<BinOpNode>(op, left, right);
    }
    return left;
}

AST parseProgram(std::istream& in) {
    input = &in;
    line = 1;
    advance();

    AST stmt;
    if (curr.type == TokenType::IDENT) {
        std::string name = curr.lexeme;
        advance();
        advance(); // =
        AST expr = parseExpr();
        stmt = std::make_shared<AssignNode>(name, expr);
    }
    return stmt;
}
