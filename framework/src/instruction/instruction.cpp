// Copyright 2026 Jannik Laugmand Bülow

#include "BibbleASM/instruction/instruction.h"

namespace bibbleasm {
    Instruction::Instruction(Opcode opcode, std::vector<Operand> operands)
        : mOpcode(opcode)
        , mOperands(std::move(operands)) {}

    void Instruction::print(std::ostream& os) const {}
}
