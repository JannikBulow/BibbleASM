// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEASM_PARSER_PARSER_H
#define BIBBLEASM_PARSER_PARSER_H 1

#include "BibbleASM/codegen/builder/module_builder.h"

#include "BibbleASM/instruction/builder.h"

#include "BibbleASM/lexer/lexer.h"

#include "BibbleASM/api.h"

#include <functional>
#include <unordered_map>
#include <vector>


namespace bibbleasm {
    class BIBBLEASM_EXPORT Parser {
    public:
        Parser(std::string_view fileName, std::vector<Token>& tokens);

        ModuleBuilder parse();

    private:
        using InstructionParser = std::function<void(InstructionBuilder&)>;

        std::string_view mFileName;
        std::vector<Token>& mTokens;

        size_t mPosition = 0;

        ModuleBuilder* mOut = nullptr;

        std::unordered_map<std::string, InstructionParser> mInstructionParsers;
        void buildInstructionParsers();

        const Token& current() const;
        const Token& consume();
        const Token& peek(int offset) const;

        const Token& expect(TokenType type, std::string_view context);

        // C++ primitive parsing
        ConstantIndex parseConstantIndex();
        intmax_t parseInt();
        uint16_t parseUInt16(); // range checked immediate parse
        std::string parseString();

        // operand parsing
        Register parseRegister();
        Immediate parseImmediate();
        Immediate parseImmediate8();
        ConstPoolIndex parseConstPoolIndex(); // legit just calls parseConstantIndex and puts it in a ConstPoolIndex
        Operand parseBranchTarget(); // either BranchOgffset or Label

        // misc parsing
        uint8_t parseTypeID();
        void parseComma(); // helper for expecting comma and consuming

        // segment parsing
        void parseModuleSegment();
        void parseConstPoolSegment();
        void parseClassSegment();
        void parseFunctionSegment();

        void parseInstruction(Assembler& as);

        [[noreturn]] void error(const std::string& message) {
            std::exit(69);
        }

        [[noreturn]] void errorAt(const Token& token, const std::string& message) {
            std::exit(69);
        }
    };
}

#endif // BIBBLEASM_PARSER_PARSER_H
