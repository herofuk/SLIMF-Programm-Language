#ifndef AST_H
#define AST_H

#include <string>
#include <vector>

struct ASTNode {
    std::string type;
    std::string value;
    std::vector<ASTNode> children;
};

#endif // AST_H
