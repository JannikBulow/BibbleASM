// Copyright 2026 Jannik Laugmand Bülow

#include "BibbleASM/codegen/builder/module_builder.h"

namespace bibbleasm {
    void ModuleBuilder::setVersion(uint16_t version) {
        mVersion = version;
    }

    void ModuleBuilder::setName(ConstantIndex name) {
        mName = name;
    }

    ClassBuilder& ModuleBuilder::addClass(ConstantIndex name, ConstantIndex superClass) {
        if (mClasses.size() >= UINT16_MAX) {
            std::exit(67);
        }

        mClasses.push_back(std::unique_ptr<ClassBuilder>(new ClassBuilder(name, superClass)));
        return *mClasses.back();
    }

    FunctionBuilder& ModuleBuilder::addFunction(ConstantIndex name, uint16_t flags, uint16_t registerCount, uint16_t parameterCount) {
        if (mFunctions.size() >= UINT16_MAX) {
            std::exit(67);
        }

        mFunctions.push_back(std::unique_ptr<FunctionBuilder>(new FunctionBuilder(name, flags, registerCount, parameterCount)));
        return *mFunctions.back();
    }

    Module ModuleBuilder::build() {
        Module module;

        module.mConstEntries = std::move(mConstPool.mEntries);
        module.mStrings = std::move(mConstPool.mStrings);

        module.mModule.constPool = {static_cast<uint16_t>(module.mConstEntries.size()), module.mConstEntries.data()};

        module.mClassFields.reserve(mClasses.size());
        module.mClassMethods.reserve(mClasses.size());
        module.mClasses.reserve(mClasses.size());

        for (auto& builder : mClasses) {
            module.mClassFields.push_back(std::move(builder->mFields));
            module.mClassMethods.push_back(std::move(builder->mMethods));

            auto& fields = module.mClassFields.back();
            auto& methods = module.mClassMethods.back();

            bibblebytecode::Class cls{};
            cls.name = builder->getName();
            cls.superClass = builder->getSuperClass();
            cls.fieldCount = static_cast<uint16_t>(fields.size());
            cls.methodCount = static_cast<uint16_t>(methods.size());
            cls.fields = fields.empty() ? nullptr : fields.data();
            cls.methods = methods.empty() ? nullptr : methods.data();

            module.mClasses.push_back(std::move(cls));
        }

        module.mFunctionBytecodes.reserve(mFunctions.size());
        module.mFunctions.reserve(mFunctions.size());

        for (auto& builder : mFunctions) {
            std::vector<uint8_t> bytecode = builder->mAssembler.assemble();

            if (bytecode.size() > UINT32_MAX) {
                std::exit(67);
            }

            module.mFunctionBytecodes.push_back(std::move(bytecode));
            const std::vector<uint8_t> storedBytecode = module.mFunctionBytecodes.back();

            bibblebytecode::Function fn{};
            fn.name = builder->getName();
            fn.flags = builder->getFlags();
            fn.registerCount = builder->getRegisterCount();
            fn.parameterCount = builder->getParameterCount();
            fn.bytecodeSize = static_cast<uint32_t>(storedBytecode.size());
            fn.bytecode = storedBytecode.empty() ? nullptr : storedBytecode.data();

            module.mFunctions.push_back(std::move(fn));
        }

        module.mModule.magic = bibblebytecode::MAGIC;
        module.mModule.formatVersion = mVersion;
        module.mModule.name = mName;
        module.mModule.classCount = static_cast<uint16_t>(module.mClasses.size());
        module.mModule.functionCount = static_cast<uint16_t>(module.mFunctions.size());
        module.mModule.classes = module.mClasses.empty() ? nullptr : module.mClasses.data();
        module.mModule.functions = module.mFunctions.empty() ? nullptr : module.mFunctions.data();

        return module;
    }
}
