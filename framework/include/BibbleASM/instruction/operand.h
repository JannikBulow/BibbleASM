// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEASM_INSTRUCTION_OPERAND_H
#define BIBBLEASM_INSTRUCTION_OPERAND_H 1

#include <memory>
#include <string>

namespace bibbleasm {
    class Operand {
    public:
        virtual ~Operand() = default;

        virtual std::unique_ptr<Operand> clone() const = 0;

        virtual std::string toString() const = 0;

        virtual bool operator==(const Operand& other) const = 0;
    };
}

#endif // BIBBLEASM_INSTRUCTION_OPERAND_H
