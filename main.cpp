#include "parser.h"
#include "optimizer.h"
#include <fstream>
#include <map>

int main(int argc, char* argv[]) {
    std::ifstream file(argv[1]);
    AST program = parseProgram(file);
    program = foldConstants(program);

    std::map<std::string, Value> env;
    program->eval(env);
    return 0;
}
