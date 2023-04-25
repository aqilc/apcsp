cmake_minimum_required(VERSION 3.21)
project(cdungeon C)

set(CMAKE_C_STANDARD 17)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

include_directories(. ./deps/include)
link_directories(./deps/lib)
link_libraries(freetype.lib glew32s.lib shell32.lib Gdi32.lib user32.lib opengl32.lib glfw3.lib zlib.lib)
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:msvcrt.lib /NODEFAULTLIB:libcmtd.lib /NODEFAULTLIB:msvcrtd.lib)
endif()

add_executable(cdungeon
        deps/2dgraphics.c
        deps/glapi.c
        deps/hash.c
        deps/hashfunc.c
        deps/spng.c
        deps/util.c
        deps/futil.c
        main.c)

add_custom_command(
        TARGET cdungeon POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/Roboto-Medium.ttf
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/Roboto-Medium.ttf)

add_custom_command(
        TARGET cdungeon POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/Roboto-Medium.ttf
                ${CMAKE_CURRENT_BINARY_DIR}/Roboto-Medium.ttf)

add_custom_command(
        TARGET cdungeon POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/graphics.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/graphics.glsl)

add_custom_command(
        TARGET cdungeon POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/graphics.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/graphics.glsl)

add_custom_command(
        TARGET cdungeon POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/DawnLike/
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/DawnLike/)

add_custom_command(
        TARGET cdungeon POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/DawnLike/
                ${CMAKE_CURRENT_BINARY_DIR}/DawnLike/)

add_custom_command(
        TARGET cdungeon POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/maps/
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/maps/)

add_custom_command(
        TARGET cdungeon POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/maps/
                ${CMAKE_CURRENT_BINARY_DIR}/maps/)
