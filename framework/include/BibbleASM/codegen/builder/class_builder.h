// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEASM_CODEGEN_BUILDER_CLASS_BUILDER_H
#define BIBBLEASM_CODEGEN_BUILDER_CLASS_BUILDER_H 1

#include "BibbleASM/codegen/builder/const_pool_builder.h"

#include "BibbleASM/api.h"

#include <BibbleBytecode/module/class.h>

#include <vector>

namespace bibbleasm {
    class BIBBLEASM_EXPORT ClassBuilder {
    friend class ModuleBuilder;
    public:
        ConstantIndex getName() const { return mName; }
        ConstantIndex getSuperClass() const { return mSuperClass; }

        uint16_t getFieldCount() const { return static_cast<uint16_t>(mFields.size()); }
        uint16_t getMethodCount() const { return static_cast<uint16_t>(mMethods.size()); }

        void addField(uint8_t typeID, ConstantIndex name);
        void addMethod(ConstantIndex name, ConstantIndex implementationFunction);

    private:
        ConstantIndex mName;
        ConstantIndex mSuperClass;

        std::vector<bibblebytecode::Field> mFields;
        std::vector<bibblebytecode::Method> mMethods;

        ClassBuilder(ConstantIndex name, ConstantIndex superClass);
    };
}

#endif // BIBBLEASM_CODEGEN_BUILDER_CLASS_BUILDER_H