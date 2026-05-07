// Copyright 2026 Jannik Laugmand Bülow

#include "BibbleASM/lexer/lexer.h"

#include <array>
#include <unordered_map>

namespace bibbleasm {
    constexpr std::array instructions = {
        "nop",

        "mov",
        "mov_range",
        "swap",

        "load_const",
        "load_imm",

        "add",
        "sub",
        "mul",
        "sdiv",
        "udiv",
        "smod",
        "umod",

        "neg",
        "abs",

        "and",
        "or",
        "xor",
        "not",

        "shl",
        "shr",
        "sar",

        "fadd",
        "fsub",
        "fmul",
        "fdiv",
        "fneg",
        "fabs",

        "tr8",
        "tr16",
        "tr32",

        "sex8",
        "sex16",
        "sex32",

        "zex8",
        "zex16",
        "zex32",

        "i2f",
        "u2f",
        "i2d",
        "u2d",

        "f2i",
        "f2u",
        "d2i",
        "d2u",

        "f2d",
        "d2f",

        "icmp",
        "ucmp",
        "fcmp",
        "strcmp",

        "inc",
        "dec",

        "jmp",

        "jeq",
        "jne",
        "jlt",
        "jle",
        "jgt",
        "jge",

        "newinstance",
        "newarray",
        "newstring",
        "newfuture",

        "objkind",
        "iskind",
        "instanceof",

        "getfield",
        "setfield",
        "dispatchmethod",
        "getclass",

        "arraylength",
        "arrayget",
        "arrayset",

        "strlength",
        "strget",
        "str2array",

        "resolve",
        "cancel",
        "isfutureready",
        "poll",
        "await",

        "call",
        "tail_call",
        "calla",
        "callap",
        "callarp",

        "call_dyn",
        "tail_call_dyn",
        "calla_dyn",
        "callap_dyn",
        "callarp_dyn",

        "return",
        "yield",
    };

    constexpr std::array sizes = {
        "BYTE",
        "SHORT",
        "INT",
        "LONG",
    };

    constexpr std::array types = {
        "byte",
        "ubyte",
        "short",
        "ushort",
        "int",
        "uint",
        "long",
        "ulong",
        "float",
        "double",
        "handle",
        "reference"
    };

    const std::unordered_map<std::string, TokenType> keywords {
        {"segment", TokenType::Segment},

        {"version", TokenType::Version},

        {"cp_byte", TokenType::Byte},
        {"cp_short", TokenType::Short},
        {"cp_int", TokenType::Int},
        {"cp_long", TokenType::Long},
        {"cp_float", TokenType::Float},
        {"cp_double", TokenType::Double},
        {"string", TokenType::String},
        {"module_info", TokenType::ModuleInfo},
        {"class_info", TokenType::ClassInfo},
        {"field_info", TokenType::FieldInfo},
        {"method_info", TokenType::MethodInfo},
        {"function_info", TokenType::FunctionInfo},

        {"name", TokenType::Name},

        {"superclass", TokenType::SuperClass},
        {"field", TokenType::Field},
        {"method", TokenType::Method},

        {"flags", TokenType::Flags},
        {"registers", TokenType::Registers},
        {"parameters", TokenType::Parameters},
        {"code", TokenType::Code},
        {"endcode", TokenType::EndCode},
    };

    std::vector<Token> Lexer::lex() {
        std::vector<Token> tokens;

        while (mPosition < mText.length()) {
            std::optional<Token> token = nextToken();
            if (token.has_value()) {
                tokens.push_back(std::move(*token));
            }
            consume();
        }
        tokens.emplace_back(TokenType::End, SourceLocation(mLine, mColumn));

        return tokens;
    }

    char Lexer::current() const {
        return mText[mPosition];
    }

    char Lexer::consume() {
        char c = mText[mPosition++];
        if (c == '\n') {
            mLine += 1;
            mColumn = 1;
        } else {
            mColumn += 1;
        }
        return c;
    }

    char Lexer::peek(int offset) const {
        return mText[mPosition + offset];
    }

    std::optional<Token> Lexer::nextToken() {
        if (std::isspace(current())) return std::nullopt;

        SourceLocation start(mLine, mColumn);

        if (std::isalpha(current()) || current() == '_' || current() == '.') { // identifier
            std::string text(1, current());
            while (std::isalnum(peek(1)) || peek(1) == '_' || peek(1) == '.') {
                consume();
                text += current();
            }

            for (std::string_view insn : instructions) {
                if (text == insn) {
                    return Token(TokenType::Instruction, start, std::move(text));
                }
            }

            for (std::string_view size : sizes) {
                if (text == size) {
                    return Token(TokenType::Size, start, std::move(text));
                }
            }

            for (std::string_view type : types) {
                if (text == type) {

                }
            }

            // check register
            if (text.size() >= 2 && text[0] == 'r') {
                bool allDigits = true;
                for (size_t i = 1; i < text.size(); ++i) {
                    if (!std::isdigit(text[i])) {
                        allDigits = false;
                        break;
                    }
                }
                if (allDigits) {
                    return Token(TokenType::Register, start, std::move(text));
                }
            }

            if (auto it = keywords.find(text); it != keywords.end()) {
                return Token(it->second, start);
            }

            return Token(TokenType::Identifier, start, std::move(text));
        }

        if ((current() == '-' && std::isdigit(peek(1))) || std::isdigit(current())) {
            std::string text(1, current());

            if (current() == '-') {
                consume();
                text += current();
            }

            if (current() == '0') {
                if (peek(1) == 'x') { // hex
                    consume();
                    text += current();

                    while (std::isxdigit(peek(1))) {
                        consume();
                        text += current();
                    }
                } else if (peek(1) == 'b') { // binary
                    consume();
                    text += current();

                    while (peek(1) == '0' || peek(1) == '1') {
                        consume();
                        text += current();
                    }
                } else {
                    while (peek(1) >= '0' && peek(1) <= '7') {
                        consume();
                        text += current();
                    }
                }
            } else {
                while (std::isdigit(peek(1))) {
                    consume();
                    text += current();
                }
            }

            return Token(TokenType::Immediate, start, std::move(text));
        }

        switch (current()) {
            case ',':
                return Token(TokenType::Comma, start);
            case ';':
                while (current() != '\n') {
                    consume();
                }
                return std::nullopt;
            case ':':
                return Token(TokenType::Colon, start);
            case '#':
                return Token(TokenType::Hash, start);

            case '"': {
                consume();
                std::string value;
                while (current() != '"') {
                    switch (current()) {
                        case '\\': {
                            consume();
                            switch (current()) {
                                case 'n':
                                    value += '\n';
                                    break;
                                case '\'':
                                    value += '\'';
                                    break;
                                case '\\':
                                    value += '\\';
                                    break;
                                case '0':
                                    value += '\0';
                                    break;
                                default:
                                    std::exit(68); // proper errors in 1 year
                            }
                            break;
                        }

                        default:
                            value += current();
                            break;
                    }
                    consume();
                }
                return Token(TokenType::String, start, std::move(value));
            }

            default:
                return Token(TokenType::Error, start, std::string(1, current()));
        }

    }
}
