#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <istream>

enum class TokenType {
    PROGRAM, END, PRINT, IF, THEN, ELSE,
    IDENT, ICONST,
    PLUS, MINUS, MULT, DIV, ASSIGN,
    LPAREN, RPAREN, COMMA,
    DONE, ERR
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
};

Token getNextToken(std::istream& in, int& line);

#endif
