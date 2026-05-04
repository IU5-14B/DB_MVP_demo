#include "Database.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace {

std::string displayValue(const dbmvp::Value& value) {
    return value.isNull ? "NULL" : value.text;
}

void printTable(const dbmvp::Result& result) {
    const auto& columns = result.columns();
    const auto& rows = result.rows();
    std::vector<std::size_t> widths(columns.size(), 0);

    for (std::size_t i = 0; i < columns.size(); ++i) {
        widths[i] = columns[i].size();
    }
    for (const auto& row : rows) {
        for (std::size_t i = 0; i < row.size(); ++i) {
            widths[i] = std::max(widths[i], displayValue(row[i]).size());
        }
    }

    auto printSeparator = [&]() {
        std::cout << '+';
        for (std::size_t width : widths) {
            std::cout << std::string(width + 2, '-') << '+';
        }
        std::cout << '\n';
    };

    printSeparator();
    std::cout << '|';
    for (std::size_t i = 0; i < columns.size(); ++i) {
        std::cout << ' ' << std::left << std::setw(static_cast<int>(widths[i])) << columns[i] << " |";
    }
    std::cout << '\n';
    printSeparator();

    for (const auto& row : rows) {
        std::cout << '|';
        for (std::size_t i = 0; i < row.size(); ++i) {
            std::cout << ' ' << std::left << std::setw(static_cast<int>(widths[i])) << displayValue(row[i]) << " |";
        }
        std::cout << '\n';
    }
    printSeparator();
    std::cout << "Rows: " << rows.size() << '\n';
}

void printResult(const dbmvp::Result& result) {
    if (!result.ok()) {
        std::cout << "Ошибка: " << result.message() << '\n';
        return;
    }
    if (result.hasTable()) {
        printTable(result);
        return;
    }
    std::cout << result.message() << '\n';
}

bool endsWithSemicolon(const std::string& text) {
    for (auto it = text.rbegin(); it != text.rend(); ++it) {
        if (!std::isspace(static_cast<unsigned char>(*it))) {
            return *it == ';';
        }
    }
    return false;
}

} // namespace

int main(int argc, char* argv[]) {
    std::string host = argc > 1 ? argv[1] : "localhost";
    std::string port = argc > 2 ? argv[2] : "7432";

    std::cout << "Учебная СУБД запущена\n";
    std::cout << "Host: " << host << '\n';
    std::cout << "Port: " << port << '\n';
    std::cout << "Введите SQL-запрос и завершите его ';'. Команды выхода: exit, quit.\n\n";

    dbmvp::Database database("data/databases");
    std::string buffer;
    std::string line;

    while (true) {
        std::cout << database.currentDatabase() << "> ";
        if (!std::getline(std::cin, line)) {
            break;
        }

        std::string lowerLine = line;
        std::transform(lowerLine.begin(), lowerLine.end(), lowerLine.begin(), [](unsigned char ch) {
            return static_cast<char>(std::tolower(ch));
        });
        if (buffer.empty() && (lowerLine == "exit" || lowerLine == "quit")) {
            break;
        }

        buffer += line;
        buffer += '\n';
        if (!endsWithSemicolon(buffer)) {
            continue;
        }

        printResult(database.execute(buffer));
        buffer.clear();
    }

    std::cout << "СУБД остановлена\n";
    return 0;
}
