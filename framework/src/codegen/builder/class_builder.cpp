// Copyright 2026 Jannik Laugmand Bülow

#include "BibbleASM/codegen/builder/class_builder.h"

namespace bibbleasm {
    void ClassBuilder::addField(uint8_t typeID, ConstantIndex name) {
        if (mFields.size() >= UINT16_MAX) {
            std::exit(67);
        }

        bibblebytecode::Field field{};
        field.typeID = typeID;
        field.padding_ = 0;
        field.name = name;
        mFields.push_back(field);
    }

    void ClassBuilder::addMethod(ConstantIndex name, ConstantIndex implementationFunction) {
        if (mMethods.size() >= UINT16_MAX) {
            std::exit(67);
        }

        bibblebytecode::Method method{};
        method.name = name;
        method.function = implementationFunction;
        mMethods.push_back(method);
    }

    ClassBuilder::ClassBuilder(ConstantIndex name, ConstantIndex superClass)
        : mName(name)
        , mSuperClass(superClass) {}
}
