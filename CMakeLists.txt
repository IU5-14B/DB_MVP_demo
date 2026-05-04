cmake_minimum_required(VERSION 3.16)

project(DB_MVP VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(db_mvp STATIC
    src/******.cpp
    src/******.cpp
    src/******.cpp
    src/Result.cpp
    src/******.cpp
)

target_include_directories(db_mvp PUBLIC include)

add_executable(db_mvp_cli src/main.cpp)
target_link_libraries(db_mvp_cli PRIVATE db_mvp)

set_target_properties(db_mvp_cli PROPERTIES OUTPUT_NAME db_mvp)
