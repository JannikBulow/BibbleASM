// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEASM_CODEGEN_BUILDER_MODULE_BUILDER_H
#define BIBBLEASM_CODEGEN_BUILDER_MODULE_BUILDER_H 1

#include "BibbleASM/codegen/builder/class_builder.h"
#include "BibbleASM/codegen/builder/const_pool_builder.h"
#include "BibbleASM/codegen/builder/function_builder.h"

#include "BibbleASM/api.h"

#include <BibbleBytecode/module/module.h>

#include <memory>
#include <vector>

namespace bibbleasm {
    class Module {
    friend class ModuleBuilder;
    public:
        Module(const Module&) = delete;
        Module& operator=(const Module&) = delete;

        Module(Module&&) = default;
        Module& operator=(Module&&) = default;

        const bibblebytecode::Module& module() const { return mModule; }

    private:
        bibblebytecode::Module mModule;

        std::vector<bibblebytecode::ConstPool::Entry> mConstEntries;

        std::deque<std::string> mStrings;

        std::vector<std::vector<bibblebytecode::Field>> mClassFields;
        std::vector<std::vector<bibblebytecode::Method>> mClassMethods;

        std::vector<bibblebytecode::Class> mClasses;

        std::vector<std::vector<uint8_t>> mFunctionBytecodes;

        std::vector<bibblebytecode::Function> mFunctions;

        Module() = default;
    };

    class BIBBLEASM_EXPORT ModuleBuilder {
    public:
        ModuleBuilder() = default;

        ModuleBuilder(const ModuleBuilder&) = delete;
        ModuleBuilder& operator=(const ModuleBuilder&) = delete;

        ModuleBuilder(ModuleBuilder&&) = default;
        ModuleBuilder& operator=(ModuleBuilder&&) = default;

        ConstPoolBuilder& constPool() { return mConstPool; }
        const ConstPoolBuilder& constPool() const { return mConstPool; }

        void setVersion(uint16_t version);
        void setName(ConstantIndex name);

        ClassBuilder& addClass(ConstantIndex name, ConstantIndex superClass = 0);

        FunctionBuilder& addFunction(ConstantIndex name, uint16_t flags, uint16_t registerCount, uint16_t parameterCount);

        Module build();

    private:
        uint16_t mVersion = 1;
        ConstantIndex mName = 0;
        ConstPoolBuilder mConstPool;

        std::vector<std::unique_ptr<ClassBuilder>> mClasses;
        std::vector<std::unique_ptr<FunctionBuilder>> mFunctions;
    };
}

#endif // BIBBLEASM_CODEGEN_BUILDER_MODULE_BUILDER_H