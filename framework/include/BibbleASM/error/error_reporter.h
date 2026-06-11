// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEASM_ERROR_ERROR_REPORTER_H
#define BIBBLEASM_ERROR_ERROR_REPORTER_H 1

#include "BibbleASM/api.h"

#include <string>

namespace bibbleasm {
    class Token;

    struct ErrorContext {
        int diagnosticCode;
        std::string file;
        std::string message;
        const Token& token;
    };

    class IErrorReporter {
    public:
        virtual ~IErrorReporter() = default;

        virtual void handleQueuedErrors() = 0;
        virtual void warning(ErrorContext ctx) = 0;
        virtual void error(ErrorContext ctx) = 0;
    };

    class BIBBLEASM_EXPORT DefaultErrorReporter : public IErrorReporter {
    public:
        void handleQueuedErrors() override;
        void warning(ErrorContext ctx) override;
        void error(ErrorContext ctx) override;

    private:
        bool mHadError = false;
    };
}

#endif // BIBBLEASM_ERROR_ERROR_REPORTER_H
