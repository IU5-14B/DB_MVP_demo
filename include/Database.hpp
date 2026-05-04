#pragma once

#include "Parser.hpp"
#include "QueryExecutor.hpp"
#include "Result.hpp"
#include "Storage.hpp"

#include <string>

namespace dbmvp {

class Database {
public:
    explicit Database(const std::string& storagePath);

    Result execute(const std::string& sql);
    const std::string& currentDatabase() const;

private:
    Parser parser_;
    QueryExecutor executor_;
};

} // namespace dbmvp
