cmake_minimum_required(VERSION 3.15)
project(minespr C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wno-unused-parameter -lncurses")
set(CMAKE_C_STANDARD 99)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(minespr src/main.c src/lib/sayBismillah.c src/lib/sayBismillah.h src/lib/winfuncs.c src/lib/winfuncs.h)
target_link_libraries(minespr ${CURSES_LIBRARY})