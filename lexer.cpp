#include "lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& src) : source(src) {}

char Lexer::peek() {
    return pos < source.size() ? source[pos] : '\0';
}

char Lexer::advance() {
    return source[pos++];
}

void Lexer::skipWhitespace() {
    while (isspace(peek())) advance();
}

std::string Lexer::parseString() {
    std::string result;
    advance(); // Пропускаем начальные кавычки
    while (peek() != '"' && peek() != '\0') {
        result += advance();
    }
    advance(); // Пропускаем закрывающие кавычки
    return result;
}

std::string Lexer::parseIdentifier() {
    std::string result;
    while (isalnum(peek()) || peek() == '_') {
        result += advance();
    }
    return result;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (pos < source.size()) {
        skipWhitespace();
        char current = peek();

        if (isalpha(current)) {
            std::string identifier = parseIdentifier();
            if (identifier == "def") tokens.push_back({DEF, identifier});
            else if (identifier == "echo") tokens.push_back({ECHO, identifier});
            else if (identifier == "return") tokens.push_back({RETURN, identifier});
            else tokens.push_back({IDENTIFIER, identifier});
        } else if (isdigit(current)) {
            tokens.push_back({NUMBER, std::string(1, advance())});
        } else if (current == '"') {
            tokens.push_back({STRING, parseString()});
        } else if (current == '(') {
            tokens.push_back({LEFT_PAREN, "("});
            advance();
        } else if (current == ')') {
            tokens.push_back({RIGHT_PAREN, ")"});
            advance();
        } else if (current == '{') {
            tokens.push_back({LEFT_BRACE, "{"});
            advance();
        } else if (current == '}') {
            tokens.push_back({RIGHT_BRACE, "}"});
            advance();
        } else if (current == ';') {
            tokens.push_back({SEMICOLON, ";"});
            advance();
        } else {
            tokens.push_back({UNKNOWN, std::string(1, advance())});
        }
    }

    tokens.push_back({END_OF_FILE, ""});
    return tokens;
}
