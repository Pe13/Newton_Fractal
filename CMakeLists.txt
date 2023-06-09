cmake_minimum_required(VERSION 3.22)
project(Newton_Fractal)

# abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

string(APPEND CMAKE_CXX_FLAGS
        " -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wcast-qual -Wformat=2"
        " -Wundef -Wshadow -Wcast-align -Wunused -Wnull-dereference"
        " -Wdouble-promotion -Wimplicit-fallthrough -Wextra-semi -Woverloaded-virtual"
        " -Wnon-virtual-dtor -Wold-style-cast")

# abilita l'address sanitizer e l'undefined-behaviour sanitizer in debug mode
#string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
#string(APPEND CMAKE_CXX_FLAGS_DEBUG " -static-libasan")
#string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

# richiedi il componente graphics della libreria SFML, versione 2.5
#   le dipendenze vengono identificate automaticamente
#find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(Newton_Fractal
        main.cpp)

target_link_directories(Newton_Fractal PRIVATE lib)
target_link_libraries(Newton_Fractal PRIVATE sfml-graphics-d sfml-window-d sfml-system-d)

target_include_directories(Newton_Fractal PRIVATE include)

#target_link_libraries(Newton_Fractal sfml-graphics sfml-window sfml-system)

