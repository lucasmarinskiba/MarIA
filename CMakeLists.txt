set(CMAKE_CXX_STANDARDcmake_minimum_required(VERSION 3.15)
project(MarIA LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ruta a los archivos fuente
file(GLOB_RECURSE SOURCES src/*.cpp)

# SFML
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(MarIA ${SOURCES})

add_executable(MarIA 
    src/main.cpp
    src/core/Player.cpp
    src/core/QuestSystem.cpp
    src/core/SaveSystem.cpp
    src/core/NPC.cpp
    src/core/Level.cpp
    src/core/Enemy.cpp
    src/core/CombatSystem.cpp
    src/core/AnimatedSprite.cpp
    src/ui/GameOverScreen.cpp
    src/ui/Menu.cpp
    src/ui/Optionsmenu.cpp
    src/ui/QuestSelector.cpp
    src/utils/ResourceManager.cpp
    # ... todos los demás archivos CPP ...
)


target_include_directories(MarIA PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/utils
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(MarIA PRIVATE sfml-graphics sfml-window sfml-system)

# Para copiar assets tras la build (opcional)
add_custom_command(TARGET MarIA POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:MarIA>/assets)
