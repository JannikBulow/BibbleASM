// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEASM_LEXER_LEXER_H
#define BIBBLEASM_LEXER_LEXER_H 1

#include "BibbleASM/lexer/token.h"

#include "BibbleASM/api.h"

#include <optional>
#include <vector>

namespace bibbleasm {
    class BIBBLEASM_EXPORT Lexer {
    public:
        explicit Lexer(std::string_view text) : mText(text) {}

        std::vector<Token> lex();

    private:
        std::string_view mText;
        size_t mPosition = 0;
        size_t mLine = 1;
        size_t mColumn = 1;

        char current() const;
        char consume();
        char peek(int offset) const;

        std::optional<Token> nextToken();
    };
}

#endif // BIBBLEASM_LEXER_LEXER_H
