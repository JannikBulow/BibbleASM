// Copyright 2026 Jannik Laugmand Bülow

#include "BibbleASM/lexer/token.h"

namespace bibbleasm {
    std::string TokenTypeToString(TokenType tokenType) {
        switch (tokenType) {
            case TokenType::Error: return "Error";
            case TokenType::Comma: return "Comma";
            case TokenType::Colon: return "Colon";
            case TokenType::Hash: return "Hash";
            case TokenType::Size: return "Size";
            case TokenType::Identifier: return "Identifier";
            case TokenType::Segment: return "Segment";
            case TokenType::Version: return "Version";
            case TokenType::Byte: return "Byte";
            case TokenType::Short: return "Short";
            case TokenType::Int: return "Int";
            case TokenType::Long: return "Long";
            case TokenType::Float: return "Float";
            case TokenType::Double: return "Double";
            case TokenType::String: return "String";
            case TokenType::ModuleInfo: return "ModuleInfo";
            case TokenType::ClassInfo: return "ClassInfo";
            case TokenType::FieldInfo: return "FieldInfo";
            case TokenType::MethodInfo: return "MethodInfo";
            case TokenType::FunctionInfo: return "FunctionInfo";
            case TokenType::Name: return "Name";
            case TokenType::SuperClass: return "SuperClass";
            case TokenType::Field: return "Field";
            case TokenType::Method: return "Method";
            case TokenType::Type: return "Type";
            case TokenType::Flags: return "Flags";
            case TokenType::Registers: return "Registers";
            case TokenType::Parameters: return "Parameters";
            case TokenType::Code: return "Code";
            case TokenType::EndCode: return "EndCode";
            case TokenType::Immediate: return "Immediate";
            case TokenType::StringLiteral: return "StringLiteral";
            case TokenType::Register: return "Register";
            case TokenType::Instruction: return "Instruction";
            case TokenType::End: return "End";
        }

        return "<unknown>";
    }
}
