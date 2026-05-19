// Copyright 2026 Jannik Laugmand Bülow

#include "BibbleASM/lexer/lexer.h"

#include "BibbleASM/parser/parser.h"

#include <BibbleBytecode/writer.h>

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>

static int CompileOne(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream input(inputFile);
    std::stringstream buffer;
    buffer << input.rdbuf();

    std::string text = buffer.str();
    text += '\n';

    buffer.clear();
    input.close();

    bibbleasm::Lexer lexer(text);
    std::vector<bibbleasm::Token> tokens = lexer.lex();

    bibbleasm::DefaultErrorReporter errorReporter;

    bibbleasm::Parser parser(inputFile, tokens, errorReporter);

    bibbleasm::ModuleBuilder moduleBuilder = parser.parse();
    bibbleasm::Module module = moduleBuilder.build();

    bibblebytecode::WritableByteBuffer buf;
    if (!bibblebytecode::writer::WriteModule(buf, module.module())) {
        return 1;
    }

    std::ofstream output(outputFile, std::ios::binary);
    buf.emit(output);

    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "basm: no input file(s)" << std::endl;
        return 1;
    }

    std::optional<std::string> inputFile;
    std::optional<std::string> outputFile;

    for (int i = 1; i < argc; i++) {
        std::string_view arg = argv[i];

        if (arg[0] == '-' && arg.size() > 1) {
            switch (arg[1]) {
                case 'h': {
                    std::cout << "Usage: basm [options...] filename\n\n";
                    std::cout << "Options (values in brackets indicate defaults):\n\n";
                    std::array<std::pair<std::string, std::string>, 3> options = {{
                        { "-h", "show this text" },
                        { "-o outfile", "write output to outfile" },
                    }};
                    auto padding = std::ranges::max_element(options, [](const auto& option1, const auto& option2) {
                        return option1.first.length() < option2.first.length();
                    })->first.length();

                    for (const auto& option : options) {
                        std::cout << "\t" << option.first;
                        std::cout << std::string(padding - option.first.length() + 1, ' ');
                        std::cout << option.second;
                        std::cout << "\n";
                    }
                    return 0;
                }

                case 'o': {
                    if (arg.size() == 2) {
                        outputFile = argv[++i];
                    } else {
                        outputFile = arg.substr(2);
                    }
                    break;
                }

                default:
                    std::cerr << std::format("basm: unrecognized command-line option '\x1b[1m{}\x1b[0m'", arg);
                    return 1;
            }
        } else {
            if (inputFile.has_value()) {
                std::cerr << std::format("basm: input file already configured: '{}'", inputFile.value());
                return 1;
            }
            inputFile = arg;
        }
    }

    if (!inputFile.has_value()) {
        std::cerr << "basm: no input files\n";
        return 1;
    }

    if (!outputFile.has_value()) {
        outputFile = inputFile->substr(0, inputFile->rfind('.')) + ".bmod";
    }

    return CompileOne(inputFile.value(), outputFile.value());
}
