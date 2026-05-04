#pragma once

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace dbmvp {

enum class DataType {
    Int,
    Float,
    Bool,
    Text,
    Varchar
};

struct Column {
    std::string name;
    DataType type = DataType::Text;
    int varcharLimit = 0;
};

struct Value {
    bool isNull = false;
    std::string text;
};

using Row = std::vector<Value>;

struct Table {
    std::string name;
    std::vector<Column> columns;
    std::vector<Row> rows;
};

enum class ComparisonOp {
    Equal,
    NotEqual,
    Less,
    Greater,
    LessOrEqual,
    GreaterOrEqual
};

enum class ConditionKind {
    Comparison,
    And,
    Or,
    Not
};

struct Condition {
    ConditionKind kind = ConditionKind::Comparison;
    std::string column;
    ComparisonOp op = ComparisonOp::Equal;
    Value value;
    std::unique_ptr<Condition> left;
    std::unique_ptr<Condition> right;
};

using ConditionPtr = std::unique_ptr<Condition>;

enum class CommandType {
    CreateDatabase,
    DropDatabase,
    UseDatabase,
    CreateTable,
    DropTable,
    Select,
    Insert,
    Update,
    Delete
};

struct Assignment {
    std::string column;
    Value value;
};

struct Query {
    CommandType type = CommandType::Select;
    std::string databaseName;
    std::string tableName;
    std::vector<Column> columns;
    std::vector<std::string> projection;
    std::vector<std::string> insertColumns;
    std::vector<Row> insertRows;
    std::vector<Assignment> assignments;
    ConditionPtr where;
};

std::string dataTypeToString(const Column& column);
std::optional<Column> parseColumnType(const std::string& name, const std::string& typeName, int varcharLimit);

} // namespace dbmvp
