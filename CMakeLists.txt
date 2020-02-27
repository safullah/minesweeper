cmake_minimum_required(VERSION 3.15)
project(minespr C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wno-unused-parameter -lncurses")
set(CMAKE_C_STANDARD 99)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(minespr src/main.c src/lib/board/board.c src/lib/board/board.h src/lib/validators/validators.c src/lib/validators/validators.h src/lib/utilities/neighbor_util.c src/lib/utilities/neighbor_util.h src/lib/utilities/playing_util.c src/lib/utilities/playing_util.h src/lib/utilities/mines_util.c src/lib/utilities/mines_util.h src/lib/utilities/game_util.c src/lib/utilities/game_util.h src/lib/board/board_variables.c src/lib/board/board_variables.h src/lib/converter/strtoint.c src/lib/converter/strtoint.h src/lib/player/player.c src/lib/player/player.h src/lib/utilities/string_util.c src/lib/utilities/string_util.h src/lib/service/set/setparam.c src/lib/service/get/getpath.c src/lib/service/get/getservice.h src/lib/service/get/loadgame.c src/lib/service/get/loadplayer.c src/lib/service/set/setservice.h src/lib/service/get/getopt.c src/lib/service/set/setboard.c)
target_link_libraries(minespr ${CURSES_LIBRARY})