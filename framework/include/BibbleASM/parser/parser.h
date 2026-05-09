// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEASM_PARSER_PARSER_H
#define BIBBLEASM_PARSER_PARSER_H 1

#include "BibbleASM/codegen/builder/module_builder.h"

#include "BibbleASM/error/error_reporter.h"

#include "BibbleASM/instruction/builder.h"

#include "BibbleASM/lexer/lexer.h"

#include "BibbleASM/api.h"

#include <functional>
#include <unordered_map>
#include <vector>

namespace bibbleasm {
    class BIBBLEASM_EXPORT Parser {
    public:
        Parser(std::string_view fileName, std::vector<Token>& tokens, IErrorReporter& errorReporter);

        ModuleBuilder parse();

    private:
        enum class SegmentKind {
            None,
            Module,
            ConstPool,
            Class,
            Function,
        };

        struct Abort {};

        using InstructionParser = std::function<void(InstructionBuilder&)>;

        std::string_view mFileName;
        std::vector<Token>& mTokens;
        IErrorReporter& mErrorReporter;

        size_t mPosition = 0;

        SegmentKind mCurrentSegment = SegmentKind::None;
        bool mInsideCode = false;

        ModuleBuilder* mOut = nullptr;

        std::unordered_map<std::string, InstructionParser> mInstructionParsers;
        void buildInstructionParsers();

        const Token& current() const;
        const Token& consume();
        const Token& peek(int offset) const;

        const Token& expect(TokenType type, std::string_view context);

        // sync to
        void synchronize();

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

        void warning(std::string message) {
            warningAt(current(), std::move(message));
        }

        void warningAt(const Token& token, std::string message) {
            mErrorReporter.warning({0, std::string(mFileName), std::move(message), token});
        }

        [[noreturn]] void error(std::string message) {
            errorAt(current(), std::move(message));
        }

        [[noreturn]] void errorAt(const Token& token, std::string message) {
            mErrorReporter.error({0, std::string(mFileName), std::move(message), token});
            throw Abort();
        }
    };
}

#endif // BIBBLEASM_PARSER_PARSER_H
