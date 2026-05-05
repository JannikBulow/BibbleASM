// Copyright 2026 Jannik Laugmand Bülow

#include "BibbleASM/codegen/builder/function_builder.h"

namespace bibbleasm {
    FunctionBuilder::FunctionBuilder(ConstantIndex name, uint16_t flags, uint16_t registerCount, uint16_t parameterCount)
        : mName(name)
        , mFlags(flags)
        , mRegisterCount(registerCount)
        , mParameterCount(parameterCount) {}
}
