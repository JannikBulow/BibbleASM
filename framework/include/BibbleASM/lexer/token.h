// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEASM_LEXER_TOKEN_H
#define BIBBLEASM_LEXER_TOKEN_H 1

#include "BibbleASM/api.h"

#include <format>
#include <ostream>
#include <string>

namespace bibbleasm {
    enum class TokenType {
        Error,

        Comma,
        Colon,
        Hash,

        Size,

        Identifier,

        Segment,

        // .module keywords
        Version,

        // .constpool keywords
        Byte,
        Short,
        Int,
        Long,
        Float,
        Double,
        String,
        ModuleInfo,
        ClassInfo,
        FieldInfo,
        MethodInfo,
        FunctionInfo,

        // shared .module, .class and .function keywords
        Name,

        // .class keywords
        SuperClass,
        Field,
        Method,
        Type, // type refers to any field type which gets mapped to a typeid.

        // .function keywords
        Flags,
        Registers,
        Parameters,
        Code,
        EndCode,

        Immediate,
        StringLiteral,

        Register,

        Instruction,

        End
    };

    BIBBLEASM_EXPORT std::string TokenTypeToString(TokenType tokenType);

    struct SourceLocation {
        size_t line;
        size_t column;

        SourceLocation(size_t line, size_t column)
            : line(line)
            , column(column) {}
    };

    class Token {
    public:
        Token(TokenType tokenType, SourceLocation location, std::string text)
            : mTokenType(tokenType)
            , mText(std::move(text))
            , mSourceLocation(location) {}

        TokenType getType() const { return mTokenType; }
        const std::string& getText() const { return mText; }
        SourceLocation getSourceLocation() const { return mSourceLocation; }

        std::string toString() const { return TokenTypeToString(mTokenType) + '(' + mText + ')'; }

        bool operator==(const Token& other) const {
            return mTokenType == other.mTokenType && mText == other.mText;
        }

    private:
        TokenType mTokenType;
        std::string mText;
        SourceLocation mSourceLocation;
    };

    inline std::ostream& operator<<(std::ostream& out, const Token& token) {
        return out << token.toString();
    }
}

template<>
struct std::formatter<bibbleasm::TokenType> : std::formatter<int> {
    template<typename FormatContext>
    auto format(bibbleasm::TokenType tokenType, FormatContext& context) const {
        return formatter<int>::format(static_cast<int>(tokenType), context);
    }
};

#endif // BIBBLEASM_LEXER_TOKEN_H
