// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEASM_INSTRUCTION_OPERAND_H
#define BIBBLEASM_INSTRUCTION_OPERAND_H 1

#include "BibbleASM/codegen/builder/const_pool_builder.h"

#include "BibbleASM/api.h"

#include <memory>
#include <optional>
#include <string>
#include <variant>

namespace bibbleasm {
    enum class OperandSize : uint8_t {
        Unknown = 0,
        Byte = 1,
        Short = 2,
        Int = 4,
        Long = 8,
    };

    struct Register {
        uint16_t index;

        constexpr Register(uint16_t index) : index(index) {}
        bool operator==(const Register&) const = default;
    };

    struct Immediate {
        OperandSize size;
        int64_t value;

        constexpr Immediate(int64_t value) : size(OperandSize::Unknown), value(value) {}
        constexpr Immediate(OperandSize size, int64_t value) : size(size), value(value) {}
        bool operator==(const Immediate&) const = default;
    };

    struct ConstPoolIndex {
        ConstantIndex index;

        constexpr ConstPoolIndex(ConstantIndex index) : index(index) {}
        bool operator==(const ConstPoolIndex&) const = default;
    };

    struct Label {
        std::string name;

        Label(std::string name) : name(std::move(name)) {}
        bool operator==(const Label&) const = default;
    };

    struct BranchOffset {
        int64_t offset;

        constexpr BranchOffset(int64_t offset) : offset(offset) {}
        bool operator==(const BranchOffset&) const = default;
    };

    using Operand = std::variant<
        Register,
        Immediate,
        ConstPoolIndex,
        Label,
        BranchOffset
    >;

    std::string GetOperandIdentifier(const Operand& operand);
}


#endif // BIBBLEASM_INSTRUCTION_OPERAND_H
