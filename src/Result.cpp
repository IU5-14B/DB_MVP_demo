#include "Result.hpp"

namespace dbmvp {

Result Result::success(const std::string& message) {
    Result result;
    result.ok_ = true;
    result.message_ = message;
    return result;
}

Result Result::affected(int rows) {
    Result result;
    result.ok_ = true;
    result.affectedRows_ = rows;
    result.message_ = "Affected rows: " + std::to_string(rows);
    return result;
}

Result Result::table(std::vector<std::string> columns, std::vector<Row> rows) {
    Result result;
    result.ok_ = true;
    result.hasTable_ = true;
    result.columns_ = std::move(columns);
    result.rows_ = std::move(rows);
    return result;
}

Result Result::error(const std::string& message) {
    Result result;
    result.ok_ = false;
    result.message_ = message;
    return result;
}

bool Result::ok() const {
    return ok_;
}

bool Result::hasTable() const {
    return hasTable_;
}

int Result::affectedRows() const {
    return affectedRows_;
}

const std::string& Result::message() const {
    return message_;
}

const std::vector<std::string>& Result::columns() const {
    return columns_;
}

const std::vector<Row>& Result::rows() const {
    return rows_;
}

} // namespace dbmvp
