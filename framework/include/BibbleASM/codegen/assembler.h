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

        const std::vector<LabeledInstruction>& instructions() const { return mInstructions; }

        std::vector<uint8_t> assemble();
        std::string disassemble();

        void reset() {
            mInstructions.clear();
            mLabels.clear();
            mPendingLabel.reset();
        }

    private:
        std::vector<LabeledInstruction> mInstructions;
        std::unordered_map<std::string, size_t> mLabels;
        std::optional<std::string> mPendingLabel;

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