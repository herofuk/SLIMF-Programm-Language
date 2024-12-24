#include <iostream>
#include "lexer.h"
#include "parser.h"

int main() {
    std::string code = R"(def main() {
        echo "Hello, world";
        return 0;
    })";

    Lexer lexer(code);
    auto tokens = lexer.tokenize();

    std::cout << "Tokens:\n";
    for (const auto& token : tokens) {
        std::cout << token.value << " (" << token.type << ")\n";
    }

    Parser parser(tokens);
    ASTNode ast = parser.parse();

    std::cout << "\nAST:\n";
    std::cout << ast.type << "\n";
    for (const auto& child : ast.children) {
        std::cout << "  " << child.type << ": " << child.value << "\n";
    }

    return 0;
}
