
cmake_minimum_required(VERSION 3.30)

project("untitled_game_jam_jam_game"
    LANGUAGES "C"
)


# Create the game executable
add_executable("${PROJECT_NAME}")
file(GLOB MY_SRC CONFIGURE_DEPENDS "src/*.c")
target_sources("${PROJECT_NAME}" PRIVATE ${MY_SRC})
set_target_properties("${PROJECT_NAME}" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "out")
if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    set_target_properties("${PROJECT_NAME}" PROPERTIES OUTPUT_NAME "index")
endif()
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options("${PROJECT_NAME}" PRIVATE
        # Basic warnings
        -Wall
        -Wextra
        -Wpedantic
        # Additional warnings
        -Warray-bounds
        -Wcast-align
        -Wdangling-else
        -Wimplicit-fallthrough
        -Wmain
        -Wmissing-prototypes
        -Wparentheses
        -Wpointer-arith
        -Wredundant-decls
        -Wshadow
        -Wswitch
        -Wstrict-overflow
        -Wstrict-prototypes
        -Wuninitialized
        -Wundef
        -Wunused
        -Wwrite-strings
        #GCC-only warnings
        -Wduplicated-branches
        -Wduplicated-cond
        -Wlogical-op
    )
endif()


# Link to raylib
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_subdirectory("libraries")
    target_link_libraries("${PROJECT_NAME}"
        PRIVATE "raylib::linux"
        PRIVATE "m"
    )
else()
    find_package("raylib" CONFIG REQUIRED)
    target_link_libraries("${PROJECT_NAME}"
        PRIVATE "raylib"
    )
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        find_package("glfw3" CONFIG REQUIRED)
        target_link_libraries("${PROJECT_NAME}"
            PRIVATE "glfw"
            PRIVATE "winmm.lib"
        )
    endif()
endif()
