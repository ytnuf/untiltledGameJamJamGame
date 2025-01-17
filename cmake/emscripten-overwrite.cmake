
# This is so that emscripten can create shared library (it doesn't by default)
# This is used with the emscripten toolchain file (provided by emsdk)
# This is to be used via CMAKE_PROJECT_INCLUDE
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS ON)
set(CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS "-s SIDE_MODULE=1")
set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "-s SIDE_MODULE=1")

# https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)#53-using-cmake
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -sUSE_GLFW=3 -sASSERTIONS=1 -sWASM=1 -sASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1 -Wno-unused-command-line-argument")
set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
