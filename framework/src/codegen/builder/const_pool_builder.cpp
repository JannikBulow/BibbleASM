// Copyright 2026 Jannik Laugmand Bülow

#include "BibbleASM/codegen/builder/const_pool_builder.h"

#include <format>

namespace bibbleasm {
    ConstPoolBuilder::ConstPoolBuilder() {
        mEntries.push_back({});
    }

    std::string ConstPoolBuilder::stringifyEntry(ConstantIndex index) const { // TODO: remake this so it doesn't print 44 comments on a field info
        const auto& entry = mEntries[index];
        switch (entry.tag) {
            case bibblebytecode::ConstPool::BYTE:
                return std::format("byte {}", entry.u.b);
            case bibblebytecode::ConstPool::SHORT:
                return std::format("short {}", entry.u.s);
            case bibblebytecode::ConstPool::INT:
                return std::format("int {}", entry.u.i);
            case bibblebytecode::ConstPool::LONG:
                return std::format("long {}", entry.u.l);
            case bibblebytecode::ConstPool::STRING:
                return std::format("string \"{}\"", entry.u.str);
            case bibblebytecode::ConstPool::MODULE_INFO:
                return std::format("module_info #{} ; #{} = {}", entry.u.mi.name, entry.u.mi.name, stringifyEntry(entry.u.mi.name));
            case bibblebytecode::ConstPool::CLASS_INFO:
                return std::format("class_info #{}, #{} ; #{} = {}, #{} = {}", entry.u.ci.module, entry.u.ci.name, entry.u.ci.module, stringifyEntry(entry.u.ci.module), entry.u.ci.name, stringifyEntry(entry.u.ci.name));
            case bibblebytecode::ConstPool::FIELD_INFO:
                return std::format("field_info #{}, #{} ; #{} = {}, #{} = {}", entry.u.fi.clas, entry.u.fi.name, entry.u.fi.clas, stringifyEntry(entry.u.fi.clas), entry.u.fi.name, stringifyEntry(entry.u.fi.name));
            case bibblebytecode::ConstPool::METHOD_INFO:
                return std::format("method_info #{}, #{} ; #{} = {}, #{} = {}", entry.u.mei.clas, entry.u.mei.name, entry.u.mei.clas, stringifyEntry(entry.u.mei.clas), entry.u.mei.name, stringifyEntry(entry.u.mei.name));
            case bibblebytecode::ConstPool::FUNCTION_INFO:
                return std::format("function_info #{}, #{} ; #{} = {}, #{} = {}", entry.u.fni.module, entry.u.fni.name, entry.u.fni.module, stringifyEntry(entry.u.fni.module), entry.u.fni.name, stringifyEntry(entry.u.fni.name));
        }

        return "<unreachable>";
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
