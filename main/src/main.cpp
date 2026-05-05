// Copyright 2026 Jannik Laugmand Bülow

#include "BibbleASM/codegen/builder/module_builder.h"

#include <BibbleBytecode/buffer.h>
#include <BibbleBytecode/writer.h>

#include <fstream>

int main() {
    bibbleasm::ModuleBuilder moduleBuilder;
    auto& cp = moduleBuilder.constPool();

    auto moduleName = cp.addString("Main");
    auto mainFunctionName = cp.addString("main");

    moduleBuilder.setVersion(1);
    moduleBuilder.setName(moduleName);

    bibbleasm::FunctionBuilder& mainFunc = moduleBuilder.addFunction(mainFunctionName, 0, 1, 0);
    bibbleasm::Assembler& as = mainFunc.assembler();

    as.emit(bibbleasm::Instruction(bibbleasm::LOAD_IMM, {{bibbleasm::Register(0)}, {bibbleasm::Immediate(69)}}));
    as.emit(bibbleasm::Instruction(bibbleasm::RETURN, {{bibbleasm::Register(0)}}));

    bibbleasm::Module module = moduleBuilder.build();
    const bibblebytecode::Module& mod = module.module();

    bibblebytecode::WritableByteBuffer buf;
    if (!bibblebytecode::writer::WriteModule(buf, mod)) {
        return 67;
    }

    std::ofstream out("Test.bmod", std::ios::binary);
    buf.emit(out);

    return 0;
}
