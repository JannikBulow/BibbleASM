// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEASM_CODEGEN_BUILDER_FUNCTION_BUILDER_H
#define BIBBLEASM_CODEGEN_BUILDER_FUNCTION_BUILDER_H 1

#include "BibbleASM/codegen/builder/const_pool_builder.h"

#include "BibbleASM/codegen/assembler.h"

#include "BibbleASM/api.h"

#include <BibbleBytecode/module/function.h>

namespace bibbleasm {
    class BIBBLEASM_EXPORT FunctionBuilder {
    friend class ModuleBuilder;
    public:
        const Assembler& assembler() const { return mAssembler; }
        Assembler& assembler() { return mAssembler; }

        ConstantIndex getName() const { return mName; }
        uint16_t getFlags() const { return mFlags; }
        uint16_t getRegisterCount() const { return mRegisterCount; }
        uint16_t getParameterCount() const { return mParameterCount; }

    private:
        ConstantIndex mName;
        uint16_t mFlags;
        uint16_t mRegisterCount;
        uint16_t mParameterCount;
        Assembler mAssembler;

        FunctionBuilder(ConstantIndex name, uint16_t flags, uint16_t registerCount, uint16_t parameterCount);
    };
}

#endif // BIBBLEASM_CODEGEN_BUILDER_FUNCTION_BUILDER_H