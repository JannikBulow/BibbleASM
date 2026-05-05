// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEASM_INSTRUCTION_OPERAND_H
#define BIBBLEASM_INSTRUCTION_OPERAND_H 1

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

        explicit constexpr Register(uint16_t index) : index(index) {}
        bool operator==(const Register&) const = default;
    };

    struct Immediate {
        OperandSize size;
        int64_t value;

        explicit constexpr Immediate(int64_t value) : value(value) {}
        bool operator==(const Immediate&) const = default;
    };

    struct ConstPoolIndex {
        uint16_t index;

        explicit constexpr ConstPoolIndex(uint16_t index) : index(index) {}
        bool operator==(const ConstPoolIndex&) const = default;
    };

    struct Label {
        std::string name;

        explicit Label(std::string name) : name(std::move(name)) {}
        bool operator==(const Label&) const = default;
    };

    struct BranchOffset {
        int64_t offset;

        explicit constexpr BranchOffset(int64_t offset) : offset(offset) {}
        bool operator==(const BranchOffset&) const = default;
    };

    using OperandVariant = std::variant<
        Register,
        Immediate,
        ConstPoolIndex,
        Label,
        BranchOffset
    >;

    struct Operand {
        OperandVariant variant;

        std::optional<uint16_t> asRegister() const {
            if (const auto* r = std::get_if<Register>(&variant)) return r->index;
            return std::nullopt;
        }

        std::optional<int64_t> asImmediate() const {
            if (const auto* r = std::get_if<Immediate>(&variant)) return r->value;
            return std::nullopt;
        }

        std::optional<uint16_t> asConstPoolIndex() const {
            if (const auto* r = std::get_if<ConstPoolIndex>(&variant)) return r->index;
            return std::nullopt;
        }
    };
}

#endif // BIBBLEASM_INSTRUCTION_OPERAND_H
