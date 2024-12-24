#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"
#include <vector>

class Parser {
private:
    std::vector<Token> tokens;
    size_t pos = 0;

    Token peek();
    Token advance();
    bool match(TokenType type);

public:
    Parser(const std::vector<Token>& toks);
    ASTNode parse();
};

#endif // PARSER_H
