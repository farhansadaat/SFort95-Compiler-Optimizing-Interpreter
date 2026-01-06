#include "lexer.h"
#include <cctype>

Token getNextToken(std::istream& in, int& line) {
    char ch;
    while (in.get(ch)) {
        if (ch == '\n') line++;
        if (isspace(ch)) continue;

        if (isalpha(ch)) {
            std::string lex(1, ch);
            while (isalnum(in.peek())) {
                lex += in.get();
            }
            if (lex == "PROGRAM") return {TokenType::PROGRAM, lex, line};
            if (lex == "END") return {TokenType::END, lex, line};
            if (lex == "PRINT") return {TokenType::PRINT, lex, line};
            if (lex == "IF") return {TokenType::IF, lex, line};
            if (lex == "THEN") return {TokenType::THEN, lex, line};
            if (lex == "ELSE") return {TokenType::ELSE, lex, line};
            return {TokenType::IDENT, lex, line};
        }

        if (isdigit(ch)) {
            std::string num(1, ch);
            while (isdigit(in.peek())) {
                num += in.get();
            }
            return {TokenType::ICONST, num, line};
        }

        switch (ch) {
            case '+': return {TokenType::PLUS, "+", line};
            case '-': return {TokenType::MINUS, "-", line};
            case '*': return {TokenType::MULT, "*", line};
            case '/': return {TokenType::DIV, "/", line};
            case '=': return {TokenType::ASSIGN, "=", line};
            case '(': return {TokenType::LPAREN, "(", line};
            case ')': return {TokenType::RPAREN, ")", line};
            case ',': return {TokenType::COMMA, ",", line};
        }
        return {TokenType::ERR, std::string(1, ch), line};
    }
    return {TokenType::DONE, "", line};
}
