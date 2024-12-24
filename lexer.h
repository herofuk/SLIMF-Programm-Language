#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>

// Типы токенов
enum TokenType {
    DEF,
    IDENTIFIER,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    ECHO,
    STRING,
    RETURN,
    NUMBER,
    SEMICOLON,
    END_OF_FILE,
    UNKNOWN
};

// Структура токена
struct Token {
    TokenType type;
    std::string value;
};

// Класс Лексера
class Lexer {
private:
    std::string source;
    size_t pos = 0;

    char peek();
    char advance();
    void skipWhitespace();
    std::string parseString();
    std::string parseIdentifier();

public:
    Lexer(const std::string& src);
    std::vector<Token> tokenize();
};

#endif // LEXER_H
