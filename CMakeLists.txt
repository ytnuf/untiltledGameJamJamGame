
cmake_minimum_required(VERSION 3.30)

project("untitled_game_jam_jam_game" LANGUAGES "C"
)

add_executable("untitled_game_jam_jam_game")
file(GLOB MY_SRC CONFIGURE_DEPENDS "src/*.c")
target_sources("untitled_game_jam_jam_game" PRIVATE ${MY_SRC})


target_link_libraries("untitled_game_jam_jam_game"
    PRIVATE "${PROJECT_SOURCE_DIR}/libraries/libraylib.a"
    PRIVATE "m"
)
target_include_directories("untitled_game_jam_jam_game" PRIVATE "libraries")
