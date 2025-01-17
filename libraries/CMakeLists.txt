
add_library("raylib-linux" INTERFACE)
add_library("raylib::linux" ALIAS "raylib-linux")

target_link_libraries("raylib-linux" INTERFACE "${CMAKE_CURRENT_LIST_DIR}/libraylib.a")
target_include_directories("raylib-linux" INTERFACE "${CMAKE_CURRENT_LIST_DIR}")
