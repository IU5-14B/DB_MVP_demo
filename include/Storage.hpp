#pragma once

#include "Types.hpp"

#include <filesystem>
#include <string>

namespace dbmvp {

class Storage {
public:
    explicit Storage(std::string rootPath);

    void ensureRoot() const;
    bool databaseExists(const std::string& databaseName) const;
    void createDatabase(const std::string& databaseName) const;
    void dropDatabase(const std::string& databaseName) const;
    bool tableExists(const std::string& databaseName, const std::string& tableName) const;
    void createTable(const std::string& databaseName, const Table& table) const;
    void dropTable(const std::string& databaseName, const std::string& tableName) const;
    Table loadTable(const std::string& databaseName, const std::string& tableName) const;
    void saveTable(const std::string& databaseName, const Table& table) const;

private:
    std::filesystem::path root_;

    std::filesystem::path databasePath(const std::string& databaseName) const;
    std::filesystem::path schemaPath(const std::string& databaseName, const std::string& tableName) const;
    std::filesystem::path dataPath(const std::string& databaseName, const std::string& tableName) const;
};

} // namespace dbmvp
