cmake_minimum_required(VERSION 3.15)
project(fmu2host VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Raiz del repositorio. Los CMakeLists generados por fmu_codegen_host.py
# resuelven las rutas a fuentes/recursos del FMU contra esta variable, de modo
# que el proyecto es reproducible al clonarlo en cualquier ubicacion.
set(FMU2HOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Raiz del repositorio fmu2host")

# Genera compile_commands.json en build/ → lo usa clangd/IntelliSense del IDE
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ── Librería principal: fmi ───────────────────────────────────────────────────
# Compila los solvers (euler, rk4) en una librería estática.
# Los headers de include/ se exponen públicamente a los targets que dependan de fmi.
add_library(fmi STATIC
    src/fmu_euler.c
    src/fmu_rk4.c
)

target_include_directories(fmi PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(fmi PRIVATE
    $<$<C_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<C_COMPILER_ID:MSVC>:/W4>
)

# CTest — debe declararse ANTES de add_subdirectory para que add_test() en
# los subdirectorios genere los CTestTestfile.cmake correctamente.
enable_testing()

# ── Subdirectorios ────────────────────────────────────────────────────────────
add_subdirectory(examples)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
    add_subdirectory(test)
endif()
