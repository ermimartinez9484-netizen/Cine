cmake_minimum_required(VERSION 3.15)
project(Cine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Cine
    main.cpp
    Cine.cpp
    Archivos.cpp
    BaseDatos.cpp
    sqlite/sqlite3.c
)

target_compile_definitions(Cine PRIVATE SQLITE_THREADSAFE=0 SQLITE_OMIT_LOAD_EXTENSION)
