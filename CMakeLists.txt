cmake_minimum_required(VERSION 3.15)
project(minespr C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wno-unused-parameter -lncurses")
set(CMAKE_C_STANDARD 99)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(minespr src/main.c src/lib/boards/board.c src/lib/boards/board.h src/lib/validators/validators.c src/lib/validators/validators.h src/lib/utilities/neighbor_cells.c src/lib/utilities/neighbor_cells.h src/lib/utilities/playing_util.c src/lib/utilities/playing_util.h src/lib/utilities/mines_util.c src/lib/utilities/mines_util.h src/lib/utilities/play_game.c src/lib/utilities/play_game.h src/lib/boards/board_variables.c src/lib/boards/board_variables.h src/lib/converter/strtoint.c src/lib/converter/strtoint.h src/lib/player/player_profile.c src/lib/player/player_profile.h)
target_link_libraries(minespr ${CURSES_LIBRARY})