#pragma once

#include "Types.hpp"

#include <string>
#include <vector>

namespace dbmvp {

class Result {
public:
    static Result success(const std::string& message);
    static Result affected(int rows);
    static Result table(std::vector<std::string> columns, std::vector<Row> rows);
    static Result error(const std::string& message);

    bool ok() const;
    bool hasTable() const;
    int affectedRows() const;
    const std::string& message() const;
    const std::vector<std::string>& columns() const;
    const std::vector<Row>& rows() const;

private:
    bool ok_ = true;
    bool hasTable_ = false;
    int affectedRows_ = -1;
    std::string message_;
    std::vector<std::string> columns_;
    std::vector<Row> rows_;
};

} // namespace dbmvp
