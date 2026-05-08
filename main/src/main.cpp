// Copyright 2026 Jannik Laugmand Bülow

#include "BibbleASM/lexer/lexer.h"

#include "BibbleASM/parser/parser.h"

#include <BibbleBytecode/writer.h>

#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>

int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }

    std::string inputFile = argv[1];

    std::ifstream input(inputFile);
    std::stringstream buffer;
    buffer << input.rdbuf();

    std::string text = buffer.str();
    text += '\n';

    buffer.clear();
    input.close();

    bibbleasm::Lexer lexer(text);
    std::vector<bibbleasm::Token> tokens = lexer.lex();

    bibbleasm::Parser parser(argv[1], tokens);

    bibbleasm::ModuleBuilder moduleBuilder = parser.parse();
    bibbleasm::Module module = moduleBuilder.build();

    bibblebytecode::WritableByteBuffer buf;
    if (!bibblebytecode::writer::WriteModule(buf, module.module())) {
        return 70;
    }

    std::filesystem::path outputFile = argv[1];
    outputFile.replace_extension("bmod");

    std::ofstream output(outputFile, std::ios::binary);
    buf.emit(output);

    return 0;
}
