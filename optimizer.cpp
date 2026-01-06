#include "optimizer.h"
#include <memory>

AST foldConstants(AST node) {
    auto bin = std::dynamic_pointer_cast<BinOpNode>(node);
    if (!bin) return node;

    auto l = foldConstants(bin->left);
    auto r = foldConstants(bin->right);

    auto lc = std::dynamic_pointer_cast<IntNode>(l);
    auto rc = std::dynamic_pointer_cast<IntNode>(r);

    if (lc && rc) {
        std::map<std::string, Value> env;
        return std::make_shared<IntNode>(bin->eval(env).i);
    }
    return node;
}
