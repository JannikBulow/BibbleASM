// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEASM_INSTRUCTION_BUILDER_FUNCS_H
#define BIBBLEASM_INSTRUCTION_BUILDER_FUNCS_H 1

#include "BibbleASM/codegen/opcodes.h"

#include "BibbleASM/instruction/instruction.h"

// DISCLAIMER: AI Generated
// The function naming conventions don't match my regular ones because they're meant to represent the opcode names 1:1
namespace bibbleasm::build {
    inline Instruction nop() {
        return Instruction{NOP};
    }

    // ============================================================
    //  Register moves
    // ============================================================

    /// MOV dst, src
    inline Instruction mov(Register dst, Register src) {
        return Instruction{MOV, {dst, src}};
    }

    /// MOV_RANGE dst, src, count
    ///   Copies `count` consecutive registers starting at src into
    ///   registers starting at dst.
    inline Instruction mov_range(Register dst, Register src, Immediate count) {
        return Instruction{MOV_RANGE, {dst, src, count}};
    }

    /// SWAP a, b
    inline Instruction swap(Register a, Register b) {
        return Instruction{SWAP, {a, b}};
    }

    // ============================================================
    //  Load instructions
    // ============================================================

    /// LOAD_CONST dst, idx  — loads constant-pool entry idx into dst.
    inline Instruction load_const(Register dst, ConstPoolIndex idx) {
        return Instruction{LOAD_CONST, {dst, idx}};
    }

    /// LOAD_IMM dst, imm  — loads an immediate integer into dst.
    inline Instruction load_imm(Register dst, Immediate imm) {
        return Instruction{LOAD_IMM, {dst, imm}};
    }

    inline Instruction load_null(Register dst) {
        return Instruction{LOAD_NULL, {dst}};
    }

    // ============================================================
    //  Integer arithmetic
    // ============================================================

    inline Instruction add(Register dst, Register lhs, Register rhs) {
        return Instruction{ADD, {dst, lhs, rhs}};
    }

    inline Instruction sub(Register dst, Register lhs, Register rhs) {
        return Instruction{SUB, {dst, lhs, rhs}};
    }

    inline Instruction mul(Register dst, Register lhs, Register rhs) {
        return Instruction{MUL, {dst, lhs, rhs}};
    }

    inline Instruction sdiv(Register dst, Register lhs, Register rhs) {
        return Instruction{SDIV, {dst, lhs, rhs}};
    }

    inline Instruction udiv(Register dst, Register lhs, Register rhs) {
        return Instruction{UDIV, {dst, lhs, rhs}};
    }

    inline Instruction smod(Register dst, Register lhs, Register rhs) {
        return Instruction{SMOD, {dst, lhs, rhs}};
    }

    inline Instruction umod(Register dst, Register lhs, Register rhs) {
        return Instruction{UMOD, {dst, lhs, rhs}};
    }

    inline Instruction neg(Register dst, Register value) {
        return Instruction{NEG, {dst, value}};
    }

    inline Instruction abs(Register dst, Register value) {
        return Instruction{ABS, {dst, value}};
    }

    // ============================================================
    //  Bitwise operations
    // ============================================================

    inline Instruction and_(Register dst, Register lhs, Register rhs) {
        return Instruction{AND, {dst, lhs, rhs}};
    }

    inline Instruction or_(Register dst, Register lhs, Register rhs) {
        return Instruction{OR, {dst, lhs, rhs}};
    }

    inline Instruction xor_(Register dst, Register lhs, Register rhs) {
        return Instruction{XOR, {dst, lhs, rhs}};
    }

    inline Instruction not_(Register dst, Register value) {
        return Instruction{NOT, {dst, value}};
    }

    inline Instruction shl(Register dst, Register lhs, Register rhs) {
        return Instruction{SHL, {dst, lhs, rhs}};
    }

    inline Instruction shr(Register dst, Register lhs, Register rhs) {
        return Instruction{SHR, {dst, lhs, rhs}};
    }

    /// SAR — arithmetic (sign-preserving) right shift.
    inline Instruction sar(Register dst, Register lhs, Register rhs) {
        return Instruction{SAR, {dst, lhs, rhs}};
    }

    // ============================================================
    //  Float arithmetic
    // ============================================================

    inline Instruction fadd(Register dst, Register lhs, Register rhs) {
        return Instruction{FADD, {dst, lhs, rhs}};
    }

    inline Instruction fsub(Register dst, Register lhs, Register rhs) {
        return Instruction{FSUB, {dst, lhs, rhs}};
    }

    inline Instruction fmul(Register dst, Register lhs, Register rhs) {
        return Instruction{FMUL, {dst, lhs, rhs}};
    }

    inline Instruction fdiv(Register dst, Register lhs, Register rhs) {
        return Instruction{FDIV, {dst, lhs, rhs}};
    }

    inline Instruction fneg(Register dst, Register value) {
        return Instruction{FNEG, {dst, value}};
    }

    inline Instruction fabs(Register dst, Register value) {
        return Instruction{FABS, {dst, value}};
    }

    // ============================================================
    //  Truncation
    // ============================================================

    inline Instruction tr8(Register dst, Register value) {
        return Instruction{TR8, {dst, value}};
    }

    inline Instruction tr16(Register dst, Register value) {
        return Instruction{TR16, {dst, value}};
    }

    inline Instruction tr32(Register dst, Register value) {
        return Instruction{TR32, {dst, value}};
    }

    // ============================================================
    //  Sign extension
    // ============================================================

    inline Instruction sex8(Register dst, Register value) {
        return Instruction{SEX8, {dst, value}};
    }

    inline Instruction sex16(Register dst, Register value) {
        return Instruction{SEX16, {dst, value}};
    }

    inline Instruction sex32(Register dst, Register value) {
        return Instruction{SEX32, {dst, value}};
    }

    // ============================================================
    //  Zero extension
    // ============================================================

    inline Instruction zex8(Register dst, Register value) {
        return Instruction{ZEX8, {dst, value}};
    }

    inline Instruction zex16(Register dst, Register value) {
        return Instruction{ZEX16, {dst, value}};
    }

    inline Instruction zex32(Register dst, Register value) {
        return Instruction{ZEX32, {dst, value}};
    }

    // ============================================================
    //  Type conversions
    // ============================================================

    inline Instruction i2f(Register dst, Register value) {
        return Instruction{I2F, {dst, value}};
    }

    inline Instruction u2f(Register dst, Register value) {
        return Instruction{U2F, {dst, value}};
    }

    inline Instruction i2d(Register dst, Register value) {
        return Instruction{I2D, {dst, value}};
    }

    inline Instruction u2d(Register dst, Register value) {
        return Instruction{U2D, {dst, value}};
    }

    inline Instruction f2i(Register dst, Register value) {
        return Instruction{F2I, {dst, value}};
    }

    inline Instruction f2u(Register dst, Register value) {
        return Instruction{F2U, {dst, value}};
    }

    inline Instruction d2i(Register dst, Register value) {
        return Instruction{D2I, {dst, value}};
    }

    inline Instruction d2u(Register dst, Register value) {
        return Instruction{D2U, {dst, value}};
    }

    inline Instruction f2d(Register dst, Register value) {
        return Instruction{F2D, {dst, value}};
    }

    inline Instruction d2f(Register dst, Register value) {
        return Instruction{D2F, {dst, value}};
    }

    // ============================================================
    //  Comparisons
    // ============================================================

    /// ICMP dst, lhs, rhs  — signed three-way comparison (-1, 0, 1).
    inline Instruction icmp(Register dst, Register lhs, Register rhs) {
        return Instruction{ICMP, {dst, lhs, rhs}};
    }

    /// UCMP dst, lhs, rhs  — unsigned three-way comparison.
    inline Instruction ucmp(Register dst, Register lhs, Register rhs) {
        return Instruction{UCMP, {dst, lhs, rhs}};
    }

    /// FCMP dst, lhs, rhs  — float three-way comparison.
    inline Instruction fcmp(Register dst, Register lhs, Register rhs) {
        return Instruction{FCMP, {dst, lhs, rhs}};
    }

    /// STRCMP dst, lhs, rhs  — UTF-8 lexicographic string comparison.
    inline Instruction strcmp_(Register dst, Register lhs, Register rhs) {
        return Instruction{STRCMP, {dst, lhs, rhs}};
    }

    // ============================================================
    //  Increment / Decrement
    // ============================================================

    /// INC value, imm  — value += imm (in-place).
    inline Instruction inc(Register value, Immediate imm) {
        return Instruction{INC, {value, imm}};
    }

    /// DEC value, imm  — value -= imm (in-place).
    inline Instruction dec(Register value, Immediate imm) {
        return Instruction{DEC, {value, imm}};
    }

    // ============================================================
    //  Branches (label-reference variants — preferred)
    // ============================================================

    /// JMP label — unconditional jump to label.
    inline Instruction jmp(Label target) {
        return Instruction{JMP, {target}};
    }

    /// JMP off — unconditional jump with a pre-computed signed offset.
    inline Instruction jmp(BranchOffset off) {
        return Instruction{JMP, {off}};
    }

    /// JEQ value, label — jump if value == 0.
    inline Instruction jeq(Register value, Label target) {
        return Instruction{JEQ, {value, target}};
    }

    inline Instruction jeq(Register value, BranchOffset off) {
        return Instruction{JEQ, {value, off}};
    }

    /// JNE value, label — jump if value != 0.
    inline Instruction jne(Register value, Label target) {
        return Instruction{JNE, {value, target}};
    }

    inline Instruction jne(Register value, BranchOffset off) {
        return Instruction{JNE, {value, off}};
    }

    /// JLT value, label — jump if value < 0.
    inline Instruction jlt(Register value, Label target) {
        return Instruction{JLT, {value, target}};
    }

    inline Instruction jlt(Register value, BranchOffset off) {
        return Instruction{JLT, {value, off}};
    }

    /// JLE value, label — jump if value <= 0.
    inline Instruction jle(Register value, Label target) {
        return Instruction{JLE, {value, target}};
    }

    inline Instruction jle(Register value, BranchOffset off) {
        return Instruction{JLE, {value, off}};
    }

    /// JGT value, label — jump if value > 0.
    inline Instruction jgt(Register value, Label target) {
        return Instruction{JGT, {value, target}};
    }

    inline Instruction jgt(Register value, BranchOffset off) {
        return Instruction{JGT, {value, off}};
    }

    /// JGE value, label — jump if value >= 0.
    inline Instruction jge(Register value, Label target) {
        return Instruction{JGE, {value, target}};
    }

    inline Instruction jge(Register value, BranchOffset off) {
        return Instruction{JGE, {value, off}};
    }

    // ============================================================
    //  Object / heap allocation
    // ============================================================

    /// NEWINSTANCE dst, class  — allocate a new uninitialized instance.
    inline Instruction newinstance(Register dst, ConstPoolIndex class_) {
        return Instruction{NEWINSTANCE, {dst, class_}};
    }

    /// NEWARRAY dst, length, typeid
    ///   Allocates a zero-initialised array of element type `typeid`.
    ///   typeid is a fixed 8-bit immediate (never widened).
    inline Instruction newarray(Register dst, Register length, Immediate typeid_) {
        return Instruction{NEWARRAY, {dst, length, typeid_}};
    }

    /// NEWSTRING dst, data  — allocate a string from a byte-array register.
    inline Instruction newstring(Register dst, Register data) {
        return Instruction{NEWSTRING, {dst, data}};
    }

    /// NEWFUTURE dst  — allocate a new uncompleted future.
    inline Instruction newfuture(Register dst) {
        return Instruction{NEWFUTURE, {dst}};
    }

    // ============================================================
    //  Object introspection
    // ============================================================

    /// OBJKIND dst, obj  — get object kind (0=instance, 1=array, 2=string, 3=future).
    inline Instruction objkind(Register dst, Register obj) {
        return Instruction{OBJKIND, {dst, obj}};
    }

    /// ISKIND dst, obj, kind  — 0 if obj.kind == kind, nonzero otherwise.
    inline Instruction iskind(Register dst, Register obj, Immediate kind) {
        return Instruction{ISKIND, {dst, obj, kind}};
    }

    /// INSTANCEOF dst, obj, class  — 0 if obj is an instance of class.
    inline Instruction instanceof_(Register dst, Register obj, ConstPoolIndex class_) {
        return Instruction{INSTANCEOF, {dst, obj, class_}};
    }

    // ============================================================
    //  Field / method access
    // ============================================================

    /// GETFIELD dst, obj, field
    inline Instruction getfield(Register dst, Register obj, ConstPoolIndex field) {
        return Instruction{GETFIELD, {dst, obj, field}};
    }

    /// SETFIELD obj, field, value
    inline Instruction setfield(Register obj, ConstPoolIndex field, Register value) {
        return Instruction{SETFIELD, {obj, field, value}};
    }

    /// DISPATCHMETHOD dst, obj, method  — vtable lookup.
    inline Instruction dispatchmethod(Register dst, Register obj, ConstPoolIndex method) {
        return Instruction{DISPATCHMETHOD, {dst, obj, method}};
    }

    /// GETCLASS dst, obj
    inline Instruction getclass(Register dst, Register obj) {
        return Instruction{GETCLASS, {dst, obj}};
    }

    // ============================================================
    //  Array operations
    // ============================================================

    /// ARRAYLENGTH dst, obj
    inline Instruction arraylength(Register dst, Register obj) {
        return Instruction{ARRAYLENGTH, {dst, obj}};
    }

    /// ARRAYGET dst, obj, idx
    inline Instruction arrayget(Register dst, Register obj, Register idx) {
        return Instruction{ARRAYGET, {dst, obj, idx}};
    }

    /// ARRAYSET obj, idx, value
    inline Instruction arrayset(Register obj, Register idx, Register value) {
        return Instruction{ARRAYSET, {obj, idx, value}};
    }

    // ============================================================
    //  String operations
    // ============================================================

    /// STRLENGTH dst, obj  — number of UTF-8 bytes in the string.
    inline Instruction strlength(Register dst, Register obj) {
        return Instruction{STRLENGTH, {dst, obj}};
    }

    /// STRGET dst, obj, idx  — single byte at UTF-8 byte index.
    inline Instruction strget(Register dst, Register obj, Register idx) {
        return Instruction{STRGET, {dst, obj, idx}};
    }

    /// STR2ARRAY dst, obj  — copy string bytes into a new byte array.
    inline Instruction str2array(Register dst, Register obj) {
        return Instruction{STR2ARRAY, {dst, obj}};
    }

    // ============================================================
    //  Future / async operations
    // ============================================================

    /// RESOLVE obj, value  — manually resolve a pending future.
    inline Instruction resolve(Register obj, Register value) {
        return Instruction{RESOLVE, {obj, value}};
    }

    /// CANCEL obj, msg  — cancel a pending future with an error message.
    inline Instruction cancel(Register obj, Register msg) {
        return Instruction{CANCEL, {obj, msg}};
    }

    /// ISFUTUREREADY dst, obj  — 0 if ready, nonzero if not.
    inline Instruction isfutureready(Register dst, Register obj) {
        return Instruction{ISFUTUREREADY, {dst, obj}};
    }

    /// POLL status_dst, value_dst, obj
    ///   Non-blocking future poll: status is -1 (pending), 0 (ready), 1 (cancelled).
    inline Instruction poll(Register status_dst, Register value_dst, Register obj) {
        return Instruction{POLL, {status_dst, value_dst, obj}};
    }

    /// AWAIT dst, obj  — suspend until future is ready, then load its value.
    inline Instruction await_(Register dst, Register obj) {
        return Instruction{AWAIT, {dst, obj}};
    }

    // ============================================================
    //  Function calls (static — constant-pool function reference)
    // ============================================================

    /// CALL dst, idx, args
    ///   Synchronous call to CONST[idx]; args is the first register
    ///   of the argument range.
    inline Instruction call(Register dst, ConstPoolIndex idx, Register args) {
        return Instruction{CALL, {dst, idx, args}};
    }

    /// TAIL_CALL idx, args
    ///   Reuse current frame and jump to CONST[idx].
    inline Instruction tail_call(ConstPoolIndex idx, Register args) {
        return Instruction{TAIL_CALL, {idx, args}};
    }

    /// CALLA dst, idx, args
    ///   Async call inheriting current task priority.
    inline Instruction calla(Register dst, ConstPoolIndex idx, Register args) {
        return Instruction{CALLA, {dst, idx, args}};
    }

    /// CALLAP dst, priority, idx, args
    ///   Async call with explicit priority register.
    inline Instruction callap(Register dst, Register priority, ConstPoolIndex idx, Register args) {
        return Instruction{CALLAP, {dst, priority, idx, args}};
    }

    /// CALLARP dst, priority, idx, args
    ///   Async call with relative priority (signed 8-bit immediate offset).
    inline Instruction callarp(Register dst, Immediate priority,
                                             ConstPoolIndex idx, Register args) {
        return Instruction{CALLARP, {dst, priority, idx, args}};
    }

    // ============================================================
    //  Function calls (dynamic — function in register)
    // ============================================================

    /// CALL_DYN dst, fn, args
    inline Instruction call_dyn(Register dst, Register fn, Register args) {
        return Instruction{CALL_DYN, {dst, fn, args}};
    }

    /// TAIL_CALL_DYN fn, args
    inline Instruction tail_call_dyn(Register fn, Register args) {
        return Instruction{TAIL_CALL_DYN, {fn, args}};
    }

    /// CALLA_DYN dst, fn, args
    inline Instruction calla_dyn(Register dst, Register fn, Register args) {
        return Instruction{CALLA_DYN, {dst, fn, args}};
    }

    /// CALLAP_DYN dst, priority, fn, args
    inline Instruction callap_dyn(Register dst, Register priority,
                                                Register fn, Register args) {
        return Instruction{CALLAP_DYN, {dst, priority, fn, args}};
    }

    /// CALLARP_DYN dst, priority, fn, args
    ///   priority is a fixed 8-bit signed immediate.
    inline Instruction callarp_dyn(Register dst, Immediate priority,
                                                 Register fn, Register args) {
        return Instruction{CALLARP_DYN, {dst, priority, fn, args}};
    }

    // ============================================================
    //  Return / yield
    // ============================================================

    /// RETURN value
    inline Instruction return_(Register value) {
        return Instruction{RETURN, {value}};
    }

    /// YIELD — voluntarily yield the current task.
    inline Instruction yield() {
        return Instruction{YIELD};
    }
}

#endif // BIBBLEASM_INSTRUCTION_BUILDER_FUNCS_H
