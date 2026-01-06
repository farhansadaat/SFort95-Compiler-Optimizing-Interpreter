#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"
#include <istream>

AST parseProgram(std::istream& in);

#endif
