#!/usr/bin/env bash
set -e

HOST="${1:-localhost}"
PORT="${2:-7432}"
EXECUTABLE="./build/db_mvp"

if [ ! -x "$EXECUTABLE" ]; then
    echo "Исполняемый файл не найден. Запускаю build.sh..."
    ./build.sh
fi

"$EXECUTABLE" "$HOST" "$PORT"
