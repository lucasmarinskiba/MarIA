cmake_minimum_required(VERSION 3.15)
project(MarIA LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ruta a los archivos fuente
file(GLOB_RECURSE SOURCES src/*.cpp)

# SFML
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

add_executable(MarIA ${SOURCES})

target_include_directories(MarIA PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/utils
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(MarIA sfml-graphics sfml-window sfml-system sfml-audio)

# Para copiar assets tras la build (opcional)
add_custom_command(TARGET MarIA POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:MarIA>/assets)
