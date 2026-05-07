// Copyright 2026 Jannik Laugmand Bülow

#include "BibbleASM/lexer/lexer.h"

#include <fstream>
#include <iostream>
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

    buffer.clear();
    input.close();

    bibbleasm::Lexer lexer(text);
    std::vector<bibbleasm::Token> tokens = lexer.lex();

    for (const auto& token : tokens) {
        std::cout << token << std::endl;
    }

    return 0;
}
