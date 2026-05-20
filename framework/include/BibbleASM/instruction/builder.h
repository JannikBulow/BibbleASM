// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEASM_INSTRUCTION_BUILDER_H
#define BIBBLEASM_INSTRUCTION_BUILDER_H 1

#include "BibbleASM/codegen/assembler.h"

#include "BibbleASM/instruction/builder_funcs.h"
#include "BibbleASM/instruction/instruction.h"

// DISCLAIMER: AI Generated
namespace bibbleasm {
    class InstructionBuilder {
    public:
        explicit InstructionBuilder(Assembler& assembler) : mAssembler(assembler) {}

        InstructionBuilder(const InstructionBuilder&) = delete;
        InstructionBuilder& operator=(const InstructionBuilder&) = delete;

        // ---- Label control ----

        /// Define a label at the current (next) instruction position.
        InstructionBuilder& label(std::string name) {
            mAssembler.label(std::move(name));
            return *this;
        }

        // ---- Misc ----

        InstructionBuilder& nop() {
            return emit(build::nop());
        }

        // ---- Register moves ----

        InstructionBuilder& mov(Register dst, Register src) {
            return emit(build::mov(dst, src));
        }

        InstructionBuilder& mov_range(Register dst, Register src, Immediate count) {
            return emit(build::mov_range(dst, src, count));
        }

        InstructionBuilder& swap(Register a, Register b) {
            return emit(build::swap(a, b));
        }

        // ---- Load ----

        InstructionBuilder& load_const(Register dst, ConstPoolIndex idx) {
            return emit(build::load_const(dst, idx));
        }

        InstructionBuilder& load_imm(Register dst, Immediate imm) {
            return emit(build::load_imm(dst, imm));
        }

        InstructionBuilder& load_null(Register dst) {
            return emit(build::load_null(dst));
        }

        // ---- Integer arithmetic ----

        InstructionBuilder& add(Register dst, Register lhs, Register rhs) {
            return emit(build::add(dst, lhs, rhs));
        }

        InstructionBuilder& sub(Register dst, Register lhs, Register rhs) {
            return emit(build::sub(dst, lhs, rhs));
        }

        InstructionBuilder& mul(Register dst, Register lhs, Register rhs) {
            return emit(build::mul(dst, lhs, rhs));
        }

        InstructionBuilder& sdiv(Register dst, Register lhs, Register rhs) {
            return emit(build::sdiv(dst, lhs, rhs));
        }

        InstructionBuilder& udiv(Register dst, Register lhs, Register rhs) {
            return emit(build::udiv(dst, lhs, rhs));
        }

        InstructionBuilder& smod(Register dst, Register lhs, Register rhs) {
            return emit(build::smod(dst, lhs, rhs));
        }

        InstructionBuilder& umod(Register dst, Register lhs, Register rhs) {
            return emit(build::umod(dst, lhs, rhs));
        }

        InstructionBuilder& neg(Register dst, Register value) {
            return emit(build::neg(dst, value));
        }

        InstructionBuilder& abs(Register dst, Register value) {
            return emit(build::abs(dst, value));
        }

        // ---- Bitwise ----

        InstructionBuilder& and_(Register dst, Register lhs, Register rhs) {
            return emit(build::and_(dst, lhs, rhs));
        }

        InstructionBuilder& or_(Register dst, Register lhs, Register rhs) {
            return emit(build::or_(dst, lhs, rhs));
        }

        InstructionBuilder& xor_(Register dst, Register lhs, Register rhs) {
            return emit(build::xor_(dst, lhs, rhs));
        }

        InstructionBuilder& not_(Register dst, Register value) {
            return emit(build::not_(dst, value));
        }

        InstructionBuilder& shl(Register dst, Register lhs, Register rhs) {
            return emit(build::shl(dst, lhs, rhs));
        }

        InstructionBuilder& shr(Register dst, Register lhs, Register rhs) {
            return emit(build::shr(dst, lhs, rhs));
        }

        InstructionBuilder& sar(Register dst, Register lhs, Register rhs) {
            return emit(build::sar(dst, lhs, rhs));
        }

        // ---- Float arithmetic ----

        InstructionBuilder& fadd(Register dst, Register lhs, Register rhs) {
            return emit(build::fadd(dst, lhs, rhs));
        }

        InstructionBuilder& fsub(Register dst, Register lhs, Register rhs) {
            return emit(build::fsub(dst, lhs, rhs));
        }

        InstructionBuilder& fmul(Register dst, Register lhs, Register rhs) {
            return emit(build::fmul(dst, lhs, rhs));
        }

        InstructionBuilder& fdiv(Register dst, Register lhs, Register rhs) {
            return emit(build::fdiv(dst, lhs, rhs));
        }

        InstructionBuilder& fneg(Register dst, Register value) {
            return emit(build::fneg(dst, value));
        }

        InstructionBuilder& fabs(Register dst, Register value) {
            return emit(build::fabs(dst, value));
        }

        // ---- Truncation ----

        InstructionBuilder& tr8(Register dst, Register value) {
            return emit(build::tr8(dst, value));
        }

        InstructionBuilder& tr16(Register dst, Register value) {
            return emit(build::tr16(dst, value));
        }

        InstructionBuilder& tr32(Register dst, Register value) {
            return emit(build::tr32(dst, value));
        }

        // ---- Sign extension ----

        InstructionBuilder& sex8(Register dst, Register value) {
            return emit(build::sex8(dst, value));
        }

        InstructionBuilder& sex16(Register dst, Register value) {
            return emit(build::sex16(dst, value));
        }

        InstructionBuilder& sex32(Register dst, Register value) {
            return emit(build::sex32(dst, value));
        }

        // ---- Zero extension ----

        InstructionBuilder& zex8(Register dst, Register value) {
            return emit(build::zex8(dst, value));
        }

        InstructionBuilder& zex16(Register dst, Register value) {
            return emit(build::zex16(dst, value));
        }

        InstructionBuilder& zex32(Register dst, Register value) {
            return emit(build::zex32(dst, value));
        }

        // ---- Type conversions ----

        InstructionBuilder& i2f(Register dst, Register value) {
            return emit(build::i2f(dst, value));
        }

        InstructionBuilder& u2f(Register dst, Register value) {
            return emit(build::u2f(dst, value));
        }

        InstructionBuilder& i2d(Register dst, Register value) {
            return emit(build::i2d(dst, value));
        }

        InstructionBuilder& u2d(Register dst, Register value) {
            return emit(build::u2d(dst, value));
        }

        InstructionBuilder& f2i(Register dst, Register value) {
            return emit(build::f2i(dst, value));
        }

        InstructionBuilder& f2u(Register dst, Register value) {
            return emit(build::f2u(dst, value));
        }

        InstructionBuilder& d2i(Register dst, Register value) {
            return emit(build::d2i(dst, value));
        }

        InstructionBuilder& d2u(Register dst, Register value) {
            return emit(build::d2u(dst, value));
        }

        InstructionBuilder& f2d(Register dst, Register value) {
            return emit(build::f2d(dst, value));
        }

        InstructionBuilder& d2f(Register dst, Register value) {
            return emit(build::d2f(dst, value));
        }

        // ---- Comparisons ----

        InstructionBuilder& icmp(Register dst, Register lhs, Register rhs) {
            return emit(build::icmp(dst, lhs, rhs));
        }

        InstructionBuilder& ucmp(Register dst, Register lhs, Register rhs) {
            return emit(build::ucmp(dst, lhs, rhs));
        }

        InstructionBuilder& fcmp(Register dst, Register lhs, Register rhs) {
            return emit(build::fcmp(dst, lhs, rhs));
        }

        InstructionBuilder& strcmp_(Register dst, Register lhs, Register rhs) {
            return emit(build::strcmp_(dst, lhs, rhs));
        }

        // ---- Increment / Decrement ----

        InstructionBuilder& inc(Register value, Immediate imm) {
            return emit(build::inc(value, imm));
        }

        InstructionBuilder& dec(Register value, Immediate imm) {
            return emit(build::dec(value, imm));
        }

        // ---- Branches ----

        InstructionBuilder& jmp(Label target) {
            return emit(build::jmp(std::move(target)));
        }

        InstructionBuilder& jmp(BranchOffset off) {
            return emit(build::jmp(off));
        }

        InstructionBuilder& jeq(Register value, Label target) {
            return emit(build::jeq(value, std::move(target)));
        }

        InstructionBuilder& jeq(Register value, BranchOffset off) {
            return emit(build::jeq(value, off));
        }

        InstructionBuilder& jne(Register value, Label target) {
            return emit(build::jne(value, std::move(target)));
        }

        InstructionBuilder& jne(Register value, BranchOffset off) {
            return emit(build::jne(value, off));
        }

        InstructionBuilder& jlt(Register value, Label target) {
            return emit(build::jlt(value, std::move(target)));
        }

        InstructionBuilder& jlt(Register value, BranchOffset off) {
            return emit(build::jlt(value, off));
        }

        InstructionBuilder& jle(Register value, Label target) {
            return emit(build::jle(value, std::move(target)));
        }

        InstructionBuilder& jle(Register value, BranchOffset off) {
            return emit(build::jle(value, off));
        }

        InstructionBuilder& jgt(Register value, Label target) {
            return emit(build::jgt(value, std::move(target)));
        }

        InstructionBuilder& jgt(Register value, BranchOffset off) {
            return emit(build::jgt(value, off));
        }

        InstructionBuilder& jge(Register value, Label target) {
            return emit(build::jge(value, std::move(target)));
        }

        InstructionBuilder& jge(Register value, BranchOffset off) {
            return emit(build::jge(value, off));
        }

        // ---- Object allocation ----

        InstructionBuilder& newinstance(Register dst, ConstPoolIndex class_) {
            return emit(build::newinstance(dst, class_));
        }

        InstructionBuilder& newarray(Register dst, Register length, Immediate typeid_) {
            return emit(build::newarray(dst, length, typeid_));
        }

        InstructionBuilder& newstring(Register dst, Register data) {
            return emit(build::newstring(dst, data));
        }

        InstructionBuilder& newfuture(Register dst) {
            return emit(build::newfuture(dst));
        }

        // ---- Object introspection ----

        InstructionBuilder& objkind(Register dst, Register obj) {
            return emit(build::objkind(dst, obj));
        }

        InstructionBuilder& iskind(Register dst, Register obj, Immediate kind) {
            return emit(build::iskind(dst, obj, kind));
        }

        InstructionBuilder& instanceof_(Register dst, Register obj, ConstPoolIndex class_) {
            return emit(build::instanceof_(dst, obj, class_));
        }

        // ---- Field / method access ----

        InstructionBuilder& getfield(Register dst, Register obj, ConstPoolIndex field) {
            return emit(build::getfield(dst, obj, field));
        }

        InstructionBuilder& setfield(Register obj, ConstPoolIndex field, Register value) {
            return emit(build::setfield(obj, field, value));
        }

        InstructionBuilder& dispatchmethod(Register dst, Register obj, ConstPoolIndex method) {
            return emit(build::dispatchmethod(dst, obj, method));
        }

        InstructionBuilder& getclass(Register dst, Register obj) {
            return emit(build::getclass(dst, obj));
        }

        // ---- Array operations ----

        InstructionBuilder& arraylength(Register dst, Register obj) {
            return emit(build::arraylength(dst, obj));
        }

        InstructionBuilder& arrayget(Register dst, Register obj, Register idx) {
            return emit(build::arrayget(dst, obj, idx));
        }

        InstructionBuilder& arrayset(Register obj, Register idx, Register value) {
            return emit(build::arrayset(obj, idx, value));
        }

        // ---- String operations ----

        InstructionBuilder& strlength(Register dst, Register obj) {
            return emit(build::strlength(dst, obj));
        }

        InstructionBuilder& strget(Register dst, Register obj, Register idx) {
            return emit(build::strget(dst, obj, idx));
        }

        InstructionBuilder& str2array(Register dst, Register obj) {
            return emit(build::str2array(dst, obj));
        }

        // ---- Future / async operations ----

        InstructionBuilder& resolve(Register obj, Register value) {
            return emit(build::resolve(obj, value));
        }

        InstructionBuilder& cancel(Register obj, Register msg) {
            return emit(build::cancel(obj, msg));
        }

        InstructionBuilder& isfutureready(Register dst, Register obj) {
            return emit(build::isfutureready(dst, obj));
        }

        InstructionBuilder& poll(Register status_dst, Register value_dst, Register obj) {
            return emit(build::poll(status_dst, value_dst, obj));
        }

        InstructionBuilder& await_(Register dst, Register obj) {
            return emit(build::await_(dst, obj));
        }

        // ---- Static calls ----

        InstructionBuilder& call(Register dst, ConstPoolIndex idx, Register args) {
            return emit(build::call(dst, idx, args));
        }

        InstructionBuilder& tail_call(ConstPoolIndex idx, Register args) {
            return emit(build::tail_call(idx, args));
        }

        InstructionBuilder& calla(Register dst, ConstPoolIndex idx, Register args) {
            return emit(build::calla(dst, idx, args));
        }

        InstructionBuilder& callap(Register dst, Register priority,
                                   ConstPoolIndex idx, Register args) {
            return emit(build::callap(dst, priority, idx, args));
        }

        InstructionBuilder& callarp(Register dst, Immediate priority,
                                    ConstPoolIndex idx, Register args) {
            return emit(build::callarp(dst, priority, idx, args));
        }

        // ---- Dynamic calls ----

        InstructionBuilder& call_dyn(Register dst, Register fn, Register args) {
            return emit(build::call_dyn(dst, fn, args));
        }

        InstructionBuilder& tail_call_dyn(Register fn, Register args) {
            return emit(build::tail_call_dyn(fn, args));
        }

        InstructionBuilder& calla_dyn(Register dst, Register fn, Register args) {
            return emit(build::calla_dyn(dst, fn, args));
        }

        InstructionBuilder& callap_dyn(Register dst, Register priority,
                                       Register fn, Register args) {
            return emit(build::callap_dyn(dst, priority, fn, args));
        }

        InstructionBuilder& callarp_dyn(Register dst, Immediate priority,
                                        Register fn, Register args) {
            return emit(build::callarp_dyn(dst, priority, fn, args));
        }

        // ---- Return / yield ----

        InstructionBuilder& return_(Register value) {
            return emit(build::return_(value));
        }

        InstructionBuilder& yield() {
            return emit(build::yield());
        }

    private:
        Assembler& mAssembler;

        InstructionBuilder& emit(Instruction insn) {
            mAssembler.emit(std::move(insn));
            return *this;
        }
    };
}

#endif // BIBBLEASM_INSTRUCTION_BUILDER_H
