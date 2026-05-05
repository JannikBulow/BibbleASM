// Copyright 2026 Jannik Laugmand Bülow

#include "BibbleASM/codegen/builder/const_pool_builder.h"

namespace bibbleasm {
    ConstPoolBuilder::ConstPoolBuilder() {
        mEntries.push_back({});
    }

    ConstantIndex ConstPoolBuilder::addByte(int8_t value) {
        bibblebytecode::ConstPool::Entry entry{};
        entry.tag = bibblebytecode::ConstPool::BYTE;
        entry.u.b = value;
        return push(std::move(entry));
    }

    ConstantIndex ConstPoolBuilder::addShort(int16_t value) {
        bibblebytecode::ConstPool::Entry entry{};
        entry.tag = bibblebytecode::ConstPool::SHORT;
        entry.u.s = value;
        return push(std::move(entry));
    }

    ConstantIndex ConstPoolBuilder::addInt(int32_t value) {
        bibblebytecode::ConstPool::Entry entry{};
        entry.tag = bibblebytecode::ConstPool::INT;
        entry.u.i = value;
        return push(std::move(entry));
    }

    ConstantIndex ConstPoolBuilder::addLong(int64_t value) {
        bibblebytecode::ConstPool::Entry entry{};
        entry.tag = bibblebytecode::ConstPool::LONG;
        entry.u.l = value;
        return push(std::move(entry));
    }

    ConstantIndex ConstPoolBuilder::addFloat(float value) {
        exit(67);
    }

    ConstantIndex ConstPoolBuilder::addDouble(double value) {
        exit(67);
    }

    ConstantIndex ConstPoolBuilder::addString(std::string value) {
        mStrings.push_back(std::move(value));
        const std::string& interned = mStrings.back();

        bibblebytecode::ConstPool::Entry entry{};
        entry.tag = bibblebytecode::ConstPool::STRING;
        entry.u.str = std::string_view(interned);
        return push(std::move(entry));
    }

    ConstantIndex ConstPoolBuilder::addModuleInfo(ConstantIndex name) {
        bibblebytecode::ConstPool::Entry entry{};
        entry.tag = bibblebytecode::ConstPool::MODULE_INFO;
        entry.u.mi = {name};
        return push(std::move(entry));
    }

    ConstantIndex ConstPoolBuilder::addClassInfo(ConstantIndex module, ConstantIndex name) {
        bibblebytecode::ConstPool::Entry entry{};
        entry.tag = bibblebytecode::ConstPool::CLASS_INFO;
        entry.u.ci = {module, name};
        return push(std::move(entry));
    }

    ConstantIndex ConstPoolBuilder::addFieldInfo(ConstantIndex clas, ConstantIndex name) {
        bibblebytecode::ConstPool::Entry entry{};
        entry.tag = bibblebytecode::ConstPool::FIELD_INFO;
        entry.u.fi = {clas, name};
        return push(std::move(entry));
    }

    ConstantIndex ConstPoolBuilder::addMethodInfo(ConstantIndex clas, ConstantIndex name) {
        bibblebytecode::ConstPool::Entry entry{};
        entry.tag = bibblebytecode::ConstPool::METHOD_INFO;
        entry.u.mei = {clas, name};
        return push(std::move(entry));
    }

    ConstantIndex ConstPoolBuilder::addFunctionInfo(ConstantIndex module, ConstantIndex name) {
        bibblebytecode::ConstPool::Entry entry{};
        entry.tag = bibblebytecode::ConstPool::FUNCTION_INFO;
        entry.u.fni = {module, name};
        return push(std::move(entry));
    }

    ConstantIndex ConstPoolBuilder::nextIndex() const {
        return static_cast<ConstantIndex>(mEntries.size());
    }

    ConstantIndex ConstPoolBuilder::push(bibblebytecode::ConstPool::Entry entry) {
        ConstantIndex index = nextIndex();
        if (index == 0) {
            std::exit(67); // TODO: replace with proper error system. maybe exceptions since this is a compiler anyway and speed is irrelevant?
        }
        mEntries.push_back(std::move(entry));
        return index;
    }
}
