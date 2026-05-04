#pragma once

#include "Parser.hpp"
#include "Result.hpp"
#include "Storage.hpp"

#include <string>

namespace dbmvp {

class QueryExecutor {
public:
    explicit QueryExecutor(Storage storage);

    Result execute(const Query& query);
    const std::string& currentDatabase() const;

private:
    Storage storage_;
    std::string currentDatabase_ = "default";

    Result executeCreateDatabase(const Query& query);
    Result executeDropDatabase(const Query& query);
    Result executeUseDatabase(const Query& query);
    Result executeCreateTable(const Query& query);
    Result executeDropTable(const Query& query);
    Result executeSelect(const Query& query);
    Result executeInsert(const Query& query);
    Result executeUpdate(const Query& query);
    Result executeDelete(const Query& query);

    bool matchesWhere(const Table& table, const Row& row, const Condition* condition) const;
    bool compareValues(const Column& column, const Value& left, ComparisonOp op, const Value& right) const;
    int columnIndex(const Table& table, const std::string& columnName) const;
    Value normalizeValue(const Column& column, const Value& value) const;
};

} // namespace dbmvp
