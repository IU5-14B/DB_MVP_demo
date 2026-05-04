#!/usr/bin/env bash
set -e

echo "Определение операционной системы..."
OS="$(uname -s)"
echo "OS: ${OS}"

install_with_manager() {
    if command -v apt >/dev/null 2>&1; then
        echo "Найден apt. Установка зависимостей..."
        sudo apt update
        sudo apt install -y build-essential cmake make
    elif command -v brew >/dev/null 2>&1; then
        echo "Найден brew. Установка зависимостей..."
        brew list cmake >/dev/null 2>&1 || brew install cmake
    elif command -v pacman >/dev/null 2>&1; then
        echo "Найден pacman. Установка зависимостей..."
        sudo pacman -Sy --needed base-devel cmake make
    else
        echo "Пакетный менеджер apt/brew/pacman не найден."
        echo "Проверьте вручную, что установлены C++ компилятор, CMake и make."
    fi
}

if ! command -v cmake >/dev/null 2>&1 || ! command -v make >/dev/null 2>&1; then
    install_with_manager
else
    echo "CMake и make уже установлены."
fi

mkdir -p build
cmake -S . -B build
cmake --build build

echo "Сборка завершена."
echo "Библиотека и исполняемый файл находятся в папке build/."
