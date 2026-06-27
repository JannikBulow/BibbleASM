// Copyright 2026 Jannik Laugmand Bülow

#include "BibbleASM/instruction/operand.h"

namespace bibbleasm {
    template<class... Ts>
    struct overloaded : Ts... {
        using Ts::operator()...;
    };

    template<class... Ts>
    overloaded(Ts...) -> overloaded<Ts...>;

    std::string GetOperandIdentifier(const Operand& operand) {
        return std::visit(overloaded{
            [](const Register& reg) {
                return "r" + std::to_string(reg.index);
            },
            [](const Immediate& imm) {
                return std::to_string(imm.value);
            },
            [](const ConstPoolIndex& idx) {
                return "#" + std::to_string(idx.index);
            },
            [](const Label& label) {
                return label.name;
            },
            [](const BranchOffset& offset) {
                return std::to_string(offset.offset);
            }
        }, operand);
    }
}
