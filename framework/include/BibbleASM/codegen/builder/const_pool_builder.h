// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEASM_CODEGEN_BUILDER_CONST_POOL_BUILDER_H
#define BIBBLEASM_CODEGEN_BUILDER_CONST_POOL_BUILDER_H 1

#include "BibbleASM/api.h"

#include <BibbleBytecode/module/const_pool.h>

#include <deque>
#include <string>
#include <vector>

namespace bibbleasm {
    using ConstantIndex = bibblebytecode::ConstantIndex;

    class BIBBLEASM_EXPORT ConstPoolBuilder {
    friend class ModuleBuilder;
    public:
        ConstPoolBuilder();

        ConstPoolBuilder(const ConstPoolBuilder&) = delete;
        ConstPoolBuilder(ConstPoolBuilder&&) noexcept = default;

        ConstPoolBuilder& operator=(const ConstPoolBuilder&) = delete;
        ConstPoolBuilder& operator=(ConstPoolBuilder&&) = default;

        uint16_t getEntryCount() const { return static_cast<uint16_t>(mEntries.size()); }

        ConstantIndex addByte(int8_t value);
        ConstantIndex addShort(int16_t value);
        ConstantIndex addInt(int32_t value);
        ConstantIndex addLong(int64_t value);

        ConstantIndex addFloat(float value);
        ConstantIndex addDouble(double value);

        ConstantIndex addString(std::string value);

        ConstantIndex addModuleInfo(ConstantIndex name);
        ConstantIndex addClassInfo(ConstantIndex module, ConstantIndex name);
        ConstantIndex addFieldInfo(ConstantIndex clas, ConstantIndex name);
        ConstantIndex addMethodInfo(ConstantIndex clas, ConstantIndex name);
        ConstantIndex addFunctionInfo(ConstantIndex module, ConstantIndex name);

    private:
        std::vector<bibblebytecode::ConstPool::Entry> mEntries;
        std::deque<std::string> mStrings; // deque cuz it doesn't reallocate ever

        ConstantIndex nextIndex() const;
        ConstantIndex push(bibblebytecode::ConstPool::Entry entry);
    };
}

#endif // BIBBLEASM_CODEGEN_BUILDER_CONST_POOL_BUILDER_H