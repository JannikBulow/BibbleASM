// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEASM_CODEGEN_ASSEMBLER_H
#define BIBBLEASM_CODEGEN_ASSEMBLER_H 1

#include "BibbleASM/instruction/instruction.h"

#include "BibbleASM/api.h"

#include <optional>
#include <span>
#include <string>
#include <unordered_map>

namespace bibbleasm {
    using InstructionId = size_t;

    /*
    struct LabeledInstruction {
        std::optional<std::string> label;
        Instruction insn;
        InstructionId id;

        explicit LabeledInstruction(Instruction insn, InstructionId id)
            : insn(std::move(insn))
            , id(id) {}

        LabeledInstruction(std::string label, Instruction insn, InstructionId id)
            : label(std::move(label))
            , insn(std::move(insn))
            , id(id) {}
    };
    */

    struct AssemblerNode {
        enum Type {
            Insn,
            Label
        };

        InstructionId id;
        Type type;
        union {
            Instruction insn;
            std::string label;
        };

        AssemblerNode(InstructionId id, Instruction insn) : id(id), type(Insn), insn(std::move(insn)) {}
        AssemblerNode(InstructionId id, std::string label) : id(id), type(Label), label(std::move(label)) {}

        AssemblerNode(const AssemblerNode& other)
            : id(other.id)
            , type(other.type) {
            switch (type) {
                case Insn:
                    new (&insn) Instruction(other.insn);
                    break;
                case Label:
                    new (&insn) Instruction(other.insn);
                    break;
            }
        }

        AssemblerNode(AssemblerNode&& other) noexcept
            : id(other.id)
            , type(other.type) {
            switch (type) {
                case Insn:
                    new (&insn) Instruction(std::move(other.insn));
                    break;
                case Label:
                    new (&insn) Instruction(std::move(other.insn));
                    break;
            }
        }

        ~AssemblerNode() {
            switch (type) {
                case Insn:
                    insn.~Instruction();
                    break;
                case Label:
                    label.~basic_string();
                    break;
            }
        }

        AssemblerNode& operator=(const AssemblerNode& other) {
            id = other.id;
            type = other.type;
            switch (type) {
                case Insn:
                    insn = other.insn;
                    break;
                case Label:
                    label = other.label;
                    break;
            }
            return *this;
        }

        AssemblerNode& operator=(AssemblerNode&& other) noexcept {
            id = other.id;
            type = other.type;
            switch (type) {
                case Insn:
                    insn = std::move(other.insn);
                    break;
                case Label:
                    label = std::move(other.label);
                    break;
            }
            return *this;
        }
    };

    class BIBBLEASM_EXPORT Assembler {
    public:
        InstructionId getLastInstructionId() const;

        void label(std::string name);

        void emit(Instruction insn);
        void emit(std::span<Instruction> insns);

        InstructionId emit(InstructionId insertAfterId, Instruction insn);

        void emit(std::string lbl, Instruction insn) {
            label(std::move(lbl));
            emit(std::move(insn));
        }

        const std::vector<AssemblerNode>& instructions() const { return mInstructions; }

        std::vector<uint8_t> assemble();
        std::string disassemble() const;

        void reset() {
            mInstructions.clear();
            mLabels.clear();
        }

    private:
        std::vector<AssemblerNode> mInstructions;
        std::unordered_map<std::string, size_t> mLabels; // will refer to the next instruction after a given label. computed in assemble()

        InstructionId mNextInstructionId = 0;

        std::vector<size_t> computeOffsets(const std::vector<int64_t>& resolvedBranches) const;
        std::vector<int64_t> resolveBranches(const std::vector<size_t>& offsets) const;

        static size_t GetInstructionSize(const Instruction& insn, int64_t resolvedBranch);
        static void EmitInstruction(const Instruction& insn, int64_t resolvedBranch, std::vector<uint8_t>& out);

        static void PushRegisterPrefix(std::vector<uint8_t>& out, uint8_t prefixByte, uint16_t index);
        static size_t PushImmediatePrefix(std::vector<uint8_t>& out, uint8_t widePrefixByte, OperandSize size, int64_t value);

        static size_t GetRegisterIndexSize(uint16_t index);
        static size_t GetImmediateSize(OperandSize size, int64_t value);
        static size_t GetBranchSize(int64_t value);
    };
}

#endif // BIBBLEASM_CODEGEN_ASSEMBLER_H