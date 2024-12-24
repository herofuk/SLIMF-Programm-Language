#include "parser.h"

Parser::Parser(const std::vector<Token>& toks) : tokens(toks) {}

Token Parser::peek() {
    return tokens[pos];
}

Token Parser::advance() {
    return tokens[pos++];
}

bool Parser::match(TokenType type) {
    if (peek().type == type) {
        advance();
        return true;
    }
    return false;
}

ASTNode Parser::parse() {
    ASTNode root{"Program", ""};

    while (peek().type != END_OF_FILE) {
        if (match(DEF)) {
            ASTNode func{"Function", "main"};
            match(IDENTIFIER); // main
            match(LEFT_PAREN);
            match(RIGHT_PAREN);
            match(LEFT_BRACE);

            if (match(ECHO)) {
                ASTNode echo{"Echo", ""};
                echo.value = peek().value;
                match(STRING);
                func.children.push_back(echo);
            }

            match(SEMICOLON);
            match(RETURN);
            func.children.push_back({"Return", "0"});
            match(NUMBER);

            match(SEMICOLON);
            match(RIGHT_BRACE);

            root.children.push_back(func);
        }
    }

    return root;
}
