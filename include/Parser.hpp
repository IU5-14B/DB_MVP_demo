#pragma once

#include "Types.hpp"

#include <string>
#include <vector>

namespace dbmvp {

class Parser {
public:
    struct Token {
        std::string text;
        bool stringLiteral = false;
    };

    Query parse(const std::string& sql) const;

private:
    class Cursor {
    public:
        explicit Cursor(std::vector<Token> tokens);

        bool atEnd() const;
        const Token& peek() const;
        Token take();
        bool match(const std::string& text);
        bool matchKeyword(const std::string& text);
        void expect(const std::string& text);
        void expectKeyword(const std::string& text);
        std::string expectIdentifier();
        Value expectValue();

    private:
        std::vector<Token> tokens_;
        std::size_t pos_ = 0;
    };

    std::vector<Token> tokenize(const std::string& sql) const;
    Query parseCreate(Cursor& cursor) const;
    Query parseDrop(Cursor& cursor) const;
    Query parseUse(Cursor& cursor) const;
    Query parseSelect(Cursor& cursor) const;
    Query parseInsert(Cursor& cursor) const;
    Query parseUpdate(Cursor& cursor) const;
    Query parseDelete(Cursor& cursor) const;
    ConditionPtr parseCondition(Cursor& cursor) const;
    ConditionPtr parseOr(Cursor& cursor) const;
    ConditionPtr parseAnd(Cursor& cursor) const;
    ConditionPtr parseNot(Cursor& cursor) const;
    ConditionPtr parsePrimary(Cursor& cursor) const;
};

} // namespace dbmvp
