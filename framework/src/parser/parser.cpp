// Copyright 2026 Jannik Laugmand Bülow

#include "BibbleASM/parser/parser.h"

#include <array>

namespace bibbleasm {
    Parser::Parser(std::string_view fileName, std::vector<Token>& tokens, IErrorReporter& errorReporter)
        : mFileName(fileName)
        , mTokens(tokens)
        , mErrorReporter(errorReporter) {
        buildInstructionParsers();

        auto it = std::remove_if(
            mTokens.begin(),
            mTokens.end(),
            [](const Token& token) { return token.getType() == TokenType::Comment; }
        );
        mTokens.erase(it, mTokens.end());
    }

    ModuleBuilder Parser::parse() {
        ModuleBuilder moduleBuilder;
        mOut = &moduleBuilder;

        while (current().getType() != TokenType::End) {
            try {
                mCurrentSegment = SegmentKind::None;

                const Token& segment = expect(TokenType::Segment, "'segment'");
                const Token& segmentName = expect(TokenType::Identifier, "segment name");

                if (segmentName.getText() == ".module") parseModuleSegment();
                else if (segmentName.getText() == ".constpool") parseConstPoolSegment();
                else if (segmentName.getText() == ".class") parseClassSegment();
                else if (segmentName.getText() == ".function") parseFunctionSegment();
                else errorAt(segmentName, "unknown segment: '" + segmentName.getText() + "'");
            } catch (const Abort& a) {
                synchronize();
            }
        }

        mErrorReporter.handleQueuedErrors();

        mOut = nullptr;
        return moduleBuilder;
    }

    // DISCLAIMER: AI Generated
    void Parser::buildInstructionParsers() {
        // Helpers to keep the table compact.
        auto R = [this]() { return parseRegister(); };
        auto I = [this]() { return parseImmediate(); };
        auto C = [this]() { return parseConstantIndex(); };
        auto I8 = [this]() { return parseImmediate8(); };
        auto BR = [this]() { return parseBranchTarget(); };
        auto cm = [this]() { parseComma(); };

        using IB = InstructionBuilder;

        mInstructionParsers = {
            // ---- Misc ----
            {"nop", [](IB& ib) { ib.nop(); }},

            // ---- Register moves ----
            {
                "mov", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto s = R();
                    ib.mov(d, s);
                }
            },
            {
                "mov_range", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto s = R();
                    cm();
                    auto n = I();
                    ib.mov_range(d, s, n);
                }
            },
            {
                "swap", [=](IB& ib) {
                    auto a = R();
                    cm();
                    auto b = R();
                    ib.swap(a, b);
                }
            },

            // ---- Load ----
            {
                "load_const", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto c = C();
                    ib.load_const(d, c);
                }
            },
            {
                "load_imm", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto i = I();
                    ib.load_imm(d, i);
                }
            },
            {
                "load_null", [=](IB& ib) {
                    auto d = R();
                    ib.load_null(d);
                }
            },

            // ---- Integer arithmetic ----
            {
                "add", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.add(d, l, r);
                }
            },
            {
                "sub", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.sub(d, l, r);
                }
            },
            {
                "mul", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.mul(d, l, r);
                }
            },
            {
                "sdiv", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.sdiv(d, l, r);
                }
            },
            {
                "udiv", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.udiv(d, l, r);
                }
            },
            {
                "smod", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.smod(d, l, r);
                }
            },
            {
                "umod", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.umod(d, l, r);
                }
            },
            {
                "neg", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.neg(d, v);
                }
            },
            {
                "abs", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.abs(d, v);
                }
            },

            // ---- Bitwise ----
            {
                "and", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.and_(d, l, r);
                }
            },
            {
                "or", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.or_(d, l, r);
                }
            },
            {
                "xor", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.xor_(d, l, r);
                }
            },
            {
                "not", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.not_(d, v);
                }
            },
            {
                "shl", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.shl(d, l, r);
                }
            },
            {
                "shr", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.shr(d, l, r);
                }
            },
            {
                "sar", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.sar(d, l, r);
                }
            },

            // ---- Float arithmetic ----
            {
                "fadd", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.fadd(d, l, r);
                }
            },
            {
                "fsub", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.fsub(d, l, r);
                }
            },
            {
                "fmul", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.fmul(d, l, r);
                }
            },
            {
                "fdiv", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.fdiv(d, l, r);
                }
            },
            {
                "fneg", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.fneg(d, v);
                }
            },
            {
                "fabs", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.fabs(d, v);
                }
            },

            // ---- Truncation ----
            {
                "tr8", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.tr8(d, v);
                }
            },
            {
                "tr16", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.tr16(d, v);
                }
            },
            {
                "tr32", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.tr32(d, v);
                }
            },

            // ---- Sign extension ----
            {
                "sex8", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.sex8(d, v);
                }
            },
            {
                "sex16", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.sex16(d, v);
                }
            },
            {
                "sex32", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.sex32(d, v);
                }
            },

            // ---- Zero extension ----
            {
                "zex8", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.zex8(d, v);
                }
            },
            {
                "zex16", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.zex16(d, v);
                }
            },
            {
                "zex32", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.zex32(d, v);
                }
            },

            // ---- Type conversions ----
            {
                "i2f", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.i2f(d, v);
                }
            },
            {
                "u2f", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.u2f(d, v);
                }
            },
            {
                "i2d", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.i2d(d, v);
                }
            },
            {
                "u2d", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.u2d(d, v);
                }
            },
            {
                "f2i", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.f2i(d, v);
                }
            },
            {
                "f2u", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.f2u(d, v);
                }
            },
            {
                "d2i", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.d2i(d, v);
                }
            },
            {
                "d2u", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.d2u(d, v);
                }
            },
            {
                "f2d", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.f2d(d, v);
                }
            },
            {
                "d2f", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto v = R();
                    ib.d2f(d, v);
                }
            },

            // ---- Comparisons ----
            {
                "icmp", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.icmp(d, l, r);
                }
            },
            {
                "ucmp", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.ucmp(d, l, r);
                }
            },
            {
                "fcmp", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.fcmp(d, l, r);
                }
            },
            {
                "strcmp", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto r = R();
                    ib.strcmp_(d, l, r);
                }
            },

            // ---- Inc / Dec ----
            {
                "inc", [=](IB& ib) {
                    auto v = R();
                    cm();
                    auto i = I();
                    ib.inc(v, i);
                }
            },
            {
                "dec", [=](IB& ib) {
                    auto v = R();
                    cm();
                    auto i = I();
                    ib.dec(v, i);
                }
            },

            // ---- Branches ----
            {
                "jmp", [=](IB& ib) {
                    auto t = BR();
                    std::visit([&](auto& o) {
                        using T = std::decay_t<decltype(o)>;
                        if constexpr (std::is_same_v<T, Label> || std::is_same_v<T, BranchOffset>)
                            ib.jmp(o);
                    }, t);
                }
            },

#define BRANCH_OP(name, method) \
        {name, [=](IB& ib) { \
            auto v = R(); \
            cm(); \
            auto t = BR(); \
            std::visit([&](auto& o) { \
                using T = std::decay_t<decltype(o)>; \
                if constexpr (std::is_same_v<T, Label> || std::is_same_v<T, BranchOffset>) \
                    ib.method(v, o); \
            }, t); \
        }},

            BRANCH_OP("jeq", jeq)
            BRANCH_OP("jne", jne)
            BRANCH_OP("jlt", jlt)
            BRANCH_OP("jle", jle)
            BRANCH_OP("jgt", jgt)
            BRANCH_OP("jge", jge)
#undef BRANCH_OP

            // ---- Object allocation ----
            {
                "newinstance", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto c = C();
                    ib.newinstance(d, c);
                }
            },
            {
                "newarray", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto l = R();
                    cm();
                    auto t = I8();
                    ib.newarray(d, l, t);
                }
            },
            {
                "newstring", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto s = R();
                    ib.newstring(d, s);
                }
            },
            {
                "newfuture", [=](IB& ib) {
                    auto d = R();
                    ib.newfuture(d);
                }
            },

            // ---- Object introspection ----
            {
                "objkind", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto o = R();
                    ib.objkind(d, o);
                }
            },
            {
                "iskind", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto o = R();
                    cm();
                    auto k = I8();
                    ib.iskind(d, o, k);
                }
            },
            {
                "instanceof", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto o = R();
                    cm();
                    auto c = C();
                    ib.instanceof_(d, o, c);
                }
            },

            // ---- Field / method access ----
            {
                "getfield", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto o = R();
                    cm();
                    auto f = C();
                    ib.getfield(d, o, f);
                }
            },
            {
                "setfield", [=](IB& ib) {
                    auto o = R();
                    cm();
                    auto f = C();
                    cm();
                    auto v = R();
                    ib.setfield(o, f, v);
                }
            },
            {
                "dispatchmethod", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto o = R();
                    cm();
                    auto m = C();
                    ib.dispatchmethod(d, o, m);
                }
            },
            {
                "getclass", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto o = R();
                    ib.getclass(d, o);
                }
            },

            // ---- Array operations ----
            {
                "arraylength", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto o = R();
                    ib.arraylength(d, o);
                }
            },
            {
                "arrayget", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto o = R();
                    cm();
                    auto i = R();
                    ib.arrayget(d, o, i);
                }
            },
            {
                "arrayset", [=](IB& ib) {
                    auto o = R();
                    cm();
                    auto i = R();
                    cm();
                    auto v = R();
                    ib.arrayset(o, i, v);
                }
            },

            // ---- String operations ----
            {
                "strlength", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto o = R();
                    ib.strlength(d, o);
                }
            },
            {
                "strget", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto o = R();
                    cm();
                    auto i = R();
                    ib.strget(d, o, i);
                }
            },
            {
                "str2array", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto o = R();
                    ib.str2array(d, o);
                }
            },

            // ---- Future / async operations ----
            {
                "resolve", [=](IB& ib) {
                    auto o = R();
                    cm();
                    auto v = R();
                    ib.resolve(o, v);
                }
            },
            {
                "cancel", [=](IB& ib) {
                    auto o = R();
                    cm();
                    auto m = R();
                    ib.cancel(o, m);
                }
            },
            {
                "isfutureready", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto o = R();
                    ib.isfutureready(d, o);
                }
            },
            {
                "poll", [=](IB& ib) {
                    auto s = R();
                    cm();
                    auto v = R();
                    cm();
                    auto o = R();
                    ib.poll(s, v, o);
                }
            },
            {
                "await", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto o = R();
                    ib.await_(d, o);
                }
            },

            // ---- Static calls ----
            {
                "call", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto i = C();
                    cm();
                    auto a = R();
                    ib.call(d, i, a);
                }
            },
            {
                "tail_call", [=](IB& ib) {
                    auto i = C();
                    cm();
                    auto a = R();
                    ib.tail_call(i, a);
                }
            },
            {
                "calla", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto i = C();
                    cm();
                    auto a = R();
                    ib.calla(d, i, a);
                }
            },
            {
                "callap", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto p = R();
                    cm();
                    auto i = C();
                    cm();
                    auto a = R();
                    ib.callap(d, p, i, a);
                }
            },
            {
                "callarp", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto p = I8();
                    cm();
                    auto i = C();
                    cm();
                    auto a = R();
                    ib.callarp(d, p, i, a);
                }
            },

            // ---- Dynamic calls ----
            {
                "call_dyn", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto f = R();
                    cm();
                    auto a = R();
                    ib.call_dyn(d, f, a);
                }
            },
            {
                "tail_call_dyn", [=](IB& ib) {
                    auto f = R();
                    cm();
                    auto a = R();
                    ib.tail_call_dyn(f, a);
                }
            },
            {
                "calla_dyn", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto f = R();
                    cm();
                    auto a = R();
                    ib.calla_dyn(d, f, a);
                }
            },
            {
                "callap_dyn", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto p = R();
                    cm();
                    auto f = R();
                    cm();
                    auto a = R();
                    ib.callap_dyn(d, p, f, a);
                }
            },
            {
                "callarp_dyn", [=](IB& ib) {
                    auto d = R();
                    cm();
                    auto p = I8();
                    cm();
                    auto f = R();
                    cm();
                    auto a = R();
                    ib.callarp_dyn(d, p, f, a);
                }
            },

            // ---- Return / yield ----
            {
                "return", [=](IB& ib) {
                    auto v = R();
                    ib.return_(v);
                }
            },
            {"yield", [](IB& ib) { ib.yield(); }},
        };
    }

    const Token& Parser::current() const {
        return mTokens[mPosition];
    }

    const Token& Parser::consume() {
        const Token& token = mTokens[mPosition];
        if (token.getType() != TokenType::End) mPosition += 1;
        return token;
    }

    const Token& Parser::peek(int offset) const {
        size_t index = mPosition + offset;
        if (index >= mTokens.size()) return mTokens.back();
        return mTokens[index];
    }

    const Token& Parser::expect(TokenType type, std::string_view context) {
        if (current().getType() != type) {
            error("expected " + std::string(context) + ", got '" + current().getText() + "'");
        }
        return consume();
    }

    void Parser::synchronize() {
        consume(); // EAT the offender

        while (current().getType() != TokenType::End) {
            if (current().getType() == TokenType::Segment) {
                mInsideCode = false;
                return;
            }

            if (mInsideCode) {
                switch (current().getType()) {
                    case TokenType::Instruction:
                    case TokenType::EndCode:
                        return;
                    default:
                        consume();
                        continue;
                }
            }

            switch (mCurrentSegment) {
                case SegmentKind::Module:
                    switch (current().getType()) {
                        case TokenType::Version:
                        case TokenType::Name:
                            return;
                        default:
                            break;
                    }
                    break;

                case SegmentKind::ConstPool:
                    switch (current().getType()) {
                        case TokenType::Byte:
                        case TokenType::Short:
                        case TokenType::Int:
                        case TokenType::Long:
                        case TokenType::Float:
                        case TokenType::Double:
                        case TokenType::String:
                        case TokenType::ModuleInfo:
                        case TokenType::ClassInfo:
                        case TokenType::FieldInfo:
                        case TokenType::MethodInfo:
                        case TokenType::FunctionInfo:
                            return;

                        default:
                            break;
                    }
                    break;

                case SegmentKind::Class:
                    switch (current().getType()) {
                        case TokenType::Name:
                        case TokenType::SuperClass:
                        case TokenType::Field:
                        case TokenType::Method:
                            return;

                        default:
                            break;
                    }
                    break;

                case SegmentKind::Function:
                    switch (current().getType()) {
                        case TokenType::Name:
                        case TokenType::Flags:
                        case TokenType::Registers:
                        case TokenType::Parameters:
                        case TokenType::Code:
                        case TokenType::EndCode:
                            return;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }

            consume();
        }
    }

    ConstantIndex Parser::parseConstantIndex() {
        expect(TokenType::Hash, "'#'");
        uint16_t value = parseUInt16();
        return static_cast<ConstantIndex>(value);
    }

    intmax_t Parser::parseInt() {
        const Token& token = expect(TokenType::Immediate, "integer immediate");
        std::string_view text = token.getText();

        bool negative = false;
        if (text.front() == '-') {
            negative = true;
            text.remove_prefix(1);

            if (text.empty()) errorAt(token, "invalid integer");
        }

        int base = 10;

        if (text.starts_with("0x") || text.starts_with("0X")) {
            base = 16;
            text.remove_prefix(2);
        } else if (text.starts_with("0b") || text.starts_with("0B")) {
            base = 2;
            text.remove_prefix(2);
        } else if (text.front() == '0' && text.size() > 1) {
            base = 8;
            text.remove_prefix(1);
        }

        if (text.empty()) errorAt(token, "missing digits");

        intmax_t value = 0;
        auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), value, base);

        if (ec != std::errc()) errorAt(token, "std::errc error. should never happen");

        return negative ? -value : value;
    }

    uint16_t Parser::parseUInt16() {
        const Token& token = current();
        intmax_t value = parseInt();
        if (value < 0 || value > UINT16_MAX) errorAt(token, "integer range out of bounds [0, 65535]");
        return static_cast<uint16_t>(value);
    }

    std::string Parser::parseString() {
        return expect(TokenType::StringLiteral, "string literal").getText();
    }

    Register Parser::parseRegister() {
        const Token& token = expect(TokenType::Register, "register");
        intmax_t value = 0;
        auto [ptr, ec] = std::from_chars(token.getText().data() + 1, token.getText().data() + token.getText().size(), value);
        if (value < 0 || value > UINT16_MAX) errorAt(token, "integer range out of bounds [0, 65535]");
        return {static_cast<uint16_t>(value)};
    }

    Immediate Parser::parseImmediate() {
        return {parseInt()};
    }

    Immediate Parser::parseImmediate8() {
        const Token& token = current();
        Immediate value = parseImmediate();
        if (value.value < 0 || value.value > UINT8_MAX) errorAt(token, "integer range out of bounds [0, 255]");
        return value;
    }

    ConstPoolIndex Parser::parseConstPoolIndex() {
        return {parseConstantIndex()};
    }

    Operand Parser::parseBranchTarget() {
        if (current().getType() == TokenType::Immediate) {
            return BranchOffset(parseInt());
        }

        const Token& name = expect(TokenType::Identifier, "label name");
        return Label(name.getText());
    }

    uint8_t Parser::parseTypeID() {
        const Token& token = expect(TokenType::Type, "type");
        std::string_view text = token.getText();
        if (text == "byte") return 0;
        if (text == "ubyte") return 1;
        if (text == "short") return 2;
        if (text == "ushort") return 3;
        if (text == "int") return 4;
        if (text == "uint") return 5;
        if (text == "long") return 6;
        if (text == "ulong") return 7;
        if (text == "float") return 8;
        if (text == "double") return 9;
        if (text == "handle") return 10;
        if (text == "reference") return 11;
        errorAt(token, "unknown type '" + token.getText() + "'");
    }

    void Parser::parseComma() {
        expect(TokenType::Comma, "','");
    }

    void Parser::parseModuleSegment() {
        constexpr std::array keywords = {
            TokenType::Name,
            TokenType::Version,
        };

        mCurrentSegment = SegmentKind::Module;

        while (std::ranges::find(keywords, current().getType()) != keywords.end()
            && current().getType() != TokenType::Segment) {

            const Token& token = consume();

            switch (token.getType()) {
                case TokenType::Name:
                    mOut->setName(parseConstantIndex());
                    break;
                case TokenType::Version:
                    mOut->setVersion(parseUInt16());
                    break;
                default:
                    errorAt(token, "unknown .module directive '" + token.getText() + "'");
            }
        }
    }

    void Parser::parseConstPoolSegment() {
        constexpr std::array keywords = {
            TokenType::Byte,
            TokenType::Short,
            TokenType::Int,
            TokenType::Long,
            TokenType::Float,
            TokenType::Double,
            TokenType::String,
            TokenType::ModuleInfo,
            TokenType::ClassInfo,
            TokenType::FieldInfo,
            TokenType::MethodInfo,
            TokenType::FunctionInfo,
        };

        mCurrentSegment = SegmentKind::ConstPool;

        auto& cp = mOut->constPool();

        while (std::ranges::find(keywords, current().getType()) != keywords.end()
            && current().getType() != TokenType::Segment) {

            try {
                const Token& token = consume();

                switch (token.getType()) {
                    case TokenType::Byte: {
                        intmax_t value = parseInt();
                        if (value < INT8_MIN || value > INT8_MAX) errorAt(token, "byte constant out of range");
                        cp.addByte(static_cast<int8_t>(value));
                        break;
                    }
                    case TokenType::Short: {
                        intmax_t value = parseInt();
                        if (value < INT16_MIN || value > INT16_MAX) errorAt(token, "short constant out of range");
                        cp.addShort(static_cast<int16_t>(value));
                        break;
                    }
                    case TokenType::Int: {
                        intmax_t value = parseInt();
                        if (value < INT32_MIN || value > INT32_MAX) errorAt(token, "int constant out of range");
                        cp.addInt(static_cast<int32_t>(value));
                        break;
                    }
                    case TokenType::Long: {
                        intmax_t value = parseInt();
                        if (value < INT64_MIN || value > INT64_MAX) errorAt(token, "long constant out of range");
                        cp.addLong(static_cast<int64_t>(value));
                        break;
                    }
                    case TokenType::Float: {
                        errorAt(token, "float constant not implemented");
                    }
                    case TokenType::Double: {
                        errorAt(token, "double constant not implemented");
                    }
                    case TokenType::String: {
                        cp.addString(parseString());
                        break;
                    }
                    case TokenType::ModuleInfo: {
                        ConstantIndex name = parseConstantIndex();
                        cp.addModuleInfo(name);
                        break;
                    }
                    case TokenType::ClassInfo: {
                        ConstantIndex module = parseConstantIndex();
                        parseComma();
                        ConstantIndex name = parseConstantIndex();
                        cp.addClassInfo(module, name);
                        break;
                    }
                    case TokenType::FieldInfo: {
                        ConstantIndex clas = parseConstantIndex();
                        parseComma();
                        ConstantIndex name = parseConstantIndex();
                        cp.addFieldInfo(clas, name);
                        break;
                    }
                    case TokenType::MethodInfo: {
                        ConstantIndex clas = parseConstantIndex();
                        parseComma();
                        ConstantIndex name = parseConstantIndex();
                        cp.addMethodInfo(clas, name);
                        break;
                    }
                    case TokenType::FunctionInfo: {
                        ConstantIndex module = parseConstantIndex();
                        parseComma();
                        ConstantIndex name = parseConstantIndex();
                        cp.addFunctionInfo(module, name);
                        break;
                    }
                    default:
                        errorAt(token, "unknown .constpool directive '" + token.getText() + "'");
                }
            } catch (const Abort& a) {
                synchronize();
            }
        }
    }

    void Parser::parseClassSegment() {
        constexpr std::array keywords = {
            TokenType::Name,
            TokenType::SuperClass,
            TokenType::Field,
            TokenType::Method,
        };

        mCurrentSegment = SegmentKind::Class;

        std::optional<ConstantIndex> name;
        std::optional<ConstantIndex> superClass;

        struct PendingField { uint8_t typeID; ConstantIndex name; };
        struct PendingMethod { ConstantIndex name, function; };
        std::vector<PendingField> fields;
        std::vector<PendingMethod> methods;

        while (std::ranges::find(keywords, current().getType()) != keywords.end()
            && current().getType() != TokenType::Segment) {

            try {
                const Token& token = consume();

                switch (token.getType()) {
                    case TokenType::Name: {
                        if (name.has_value()) errorAt(token, "duplicate 'name' in .class segment");
                        name = parseConstantIndex();
                        break;
                    }
                    case TokenType::SuperClass: {
                        if (superClass.has_value()) errorAt(token, "duplicate 'superclass' in .class segment");
                        superClass = parseConstantIndex();
                        break;
                    }
                    case TokenType::Field: {
                        uint8_t typeID = parseTypeID();
                        parseComma();
                        ConstantIndex fieldName = parseConstantIndex();
                        fields.push_back({typeID, fieldName});
                        break;
                    }
                    case TokenType::Method: {
                        ConstantIndex methodName = parseConstantIndex();
                        parseComma();
                        ConstantIndex function = parseConstantIndex();
                        methods.push_back({methodName, function});
                        break;
                    }
                    default:
                        errorAt(token, "unknown .class directive '" + token.getText() + "'");
                }
            } catch (const Abort& a) {
                synchronize();
            }
        }

        if (!name.has_value()) error(".class segment missing 'name' directive");
        if (!superClass.has_value()) error(".class segment missing 'superclass' directive");

        ClassBuilder& classBuilder = mOut->addClass(name.value(), superClass.value());
        for (auto& field : fields) classBuilder.addField(field.typeID, field.name);
        for (auto& method : methods) classBuilder.addMethod(method.name, method.function);
    }

    void Parser::parseFunctionSegment() {
        constexpr std::array keywords = {
            TokenType::Name,
            TokenType::Flags,
            TokenType::Registers,
            TokenType::Parameters,
            TokenType::Code,
            TokenType::EndCode,
        };

        mCurrentSegment = SegmentKind::Function;

        std::optional<ConstantIndex> name;
        std::optional<uint16_t> flags;
        std::optional<uint16_t> registers;
        std::optional<uint16_t> parameters;
        std::optional<size_t> codeStart;
        std::optional<size_t> codeEnd;

        while (std::ranges::find(keywords, current().getType()) != keywords.end()
            && current().getType() != TokenType::Segment) {

            try {
                const Token& token = consume();

                switch (token.getType()) {
                    case TokenType::Name: {
                        if (name.has_value()) errorAt(token, "duplicate 'name' in .function segment");
                        name = parseConstantIndex();
                        break;
                    }
                    case TokenType::Flags: {
                        if (flags.has_value()) errorAt(token, "duplicate 'flags' in .function segment");
                        flags = parseUInt16();
                        break;
                    }
                    case TokenType::Registers: {
                        if (registers.has_value()) errorAt(token, "duplicate 'registers' in .function segment");
                        registers = parseUInt16();
                        break;
                    }
                    case TokenType::Parameters: {
                        if (parameters.has_value()) errorAt(token, "duplicate 'parameters' in .function segment");
                        parameters = parseUInt16();
                        break;
                    }
                    case TokenType::Code: {
                        if (codeStart.has_value()) errorAt(token, "duplicate 'code' in .function segment");
                        codeStart = mPosition - 1;

                        mInsideCode = true;

                        while (current().getType() != TokenType::EndCode) {
                            if (current().getType() == TokenType::End) error("unexpected end of file inside 'code' block; expected 'endcode'");
                            consume();
                        }

                        codeEnd = mPosition;
                        consume();

                        mInsideCode = false;

                        break;
                    }
                    case TokenType::EndCode: {
                        if (codeEnd.has_value()) errorAt(token, "duplicate 'endcode' in .function segment");
                        codeEnd = mPosition - 1;
                        break;
                    }
                    case TokenType::Identifier:
                    case TokenType::Instruction:
                        break;

                    default:
                        errorAt(token, "unknown .function directive '" + token.getText() + "'");
                }
            } catch (const Abort& a) {
                synchronize();
            }
        }

        if (!name.has_value()) error(".function segment missing 'name' directive");
        if (!flags.has_value()) error(".function segment missing 'flags' directive");
        if (!registers.has_value()) error(".function segment missing 'registers' directive");
        if (!parameters.has_value()) parameters = 0;

        FunctionBuilder& functionBuilder = mOut->addFunction(name.value(), flags.value(), registers.value(), parameters.value());

        if (codeStart.has_value()) {
            if (!codeEnd.has_value()) error("code directive without endcode directive");

            Assembler& as = functionBuilder.assembler();
            size_t savedPosition = mPosition;
            mPosition = codeStart.value() + 1;

            mInsideCode = true;

            while (mPosition < codeEnd.value()) {
                try {
                    parseInstruction(as);
                } catch (const Abort& a) {
                    synchronize();
                }
            }

            mPosition = savedPosition;
            mInsideCode = false;
        }
    }

    void Parser::parseInstruction(Assembler& as) {
        if (current().getType() == TokenType::Identifier && peek(1).getType() == TokenType::Colon) {
            std::string labelName = consume().getText();
            consume();

            as.label(std::move(labelName));
        }

        const Token& token = expect(TokenType::Instruction, "instruction");

        auto it = mInstructionParsers.find(token.getText());
        if (it == mInstructionParsers.end()) errorAt(token, "unknown instruction '" + token.getText() + "'");

        InstructionBuilder builder(as);
        it->second(builder);
    }
}
