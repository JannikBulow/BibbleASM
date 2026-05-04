// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEASM_INSTRUCTION_INSTRUCTION_H
#define BIBBLEASM_INSTRUCTION_INSTRUCTION_H 1

#include "BibbleASM/instruction/operand.h"

#include "BibbleASM/opcodes.h"

#include <ostream>
#include <vector>

namespace bibbleasm {
    class Instruction {
    public:
        explicit Instruction(Opcode opcode, std::vector<Operand> operands = {});

        Opcode getOpcode() const { return mOpcode; }

        const std::vector<Operand>& operands() const { return mOperands; }
        std::vector<Operand>& operands() { return mOperands; }

        const Operand& operand(size_t index) const { return mOperands[index]; }
        Operand& operand(size_t index) { return mOperands[index]; }

        bool isTerminator() const { return opcodeutils::IsTerminator(mOpcode); }
        bool isConditionalBranch() const { return opcodeutils::IsConditionalBranch(mOpcode); }
        bool isBranch() const { return opcodeutils::IsBranch(mOpcode); }
        bool isCall() const { return opcodeutils::IsCall(mOpcode); }
        bool isAsyncCall() const { return opcodeutils::IsAsyncCall(mOpcode); }
        bool isFloatOp() const { return opcodeutils::IsFloatOp(mOpcode); }

        void print(std::ostream& os) const;

    private:
        Opcode mOpcode;
        std::vector<Operand> mOperands;
    };
}

#endif // BIBBLEASM_INSTRUCTION_INSTRUCTION_H
