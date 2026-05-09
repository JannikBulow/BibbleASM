// Copyright 2026 Jannik Laugmand Bülow

#include "BibbleASM/error/error_reporter.h"

#include "BibbleASM/lexer/token.h"

#include <format>
#include <iostream>

namespace bibbleasm {
    void DefaultErrorReporter::handleQueuedErrors() {
        if (mHadError) std::exit(1);
    }

    void DefaultErrorReporter::warning(ErrorContext ctx) {
        std::cerr << std::format("warning[A{}]: {}:{}:{}: {}\n", ctx.diagnosticCode, ctx.file, ctx.token.getSourceLocation().line, ctx.token.getSourceLocation().column, ctx.message);
    }

    void DefaultErrorReporter::error(ErrorContext ctx) {
        std::cerr << std::format("error[A{}]: {}:{}:{}: {}\n", ctx.diagnosticCode, ctx.file, ctx.token.getSourceLocation().line, ctx.token.getSourceLocation().column, ctx.message);
        mHadError = true;
    }
}
