// Copyright 2026 Jannik Laugmand Bülow

#include "BibbleASM/codegen/builder/module_builder.h"

#include "BibbleASM/instruction/builder.h"

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
    bibbleasm::InstructionBuilder instructionBuilder(mainFunc.assembler());

    instructionBuilder.load_imm(0, 67);
    instructionBuilder.return_(0);

    bibbleasm::Module module = moduleBuilder.build();
    const bibblebytecode::Module& mod = module.module();

    bibblebytecode::WritableByteBuffer buf;
    if (!bibblebytecode::writer::WriteModule(buf, mod)) {
        return 67;
    }

    std::ofstream out("Main.bmod", std::ios::binary);
    if (out.fail()) return 67;
    buf.emit(out);

    return 0;
}
