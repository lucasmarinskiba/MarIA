cmake_minimum_required(VERSION 3.15)
project(MarIA LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar SFML con todos los componentes necesarios
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# Lista explícita de archivos fuente (evita problemas con GLOB)
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
    src/ui/Optionsmenu.cpp  # Asegúrate que el nombre coincide con el archivo real
    src/ui/QuestSelector.cpp
    src/utils/ResourceManager.cpp
    # Agrega aquí otros archivos .cpp que tengas
    # Ejemplo adicional: src/ui/HUD.cpp
)

# Directorios de inclusión
target_include_directories(MarIA PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/ui
    ${CMAKE_SOURCE_DIR}/src/utils
    ${CMAKE_SOURCE_DIR}/include
    # Agrega rutas adicionales si es necesario
)

# Vincular SFML y otras dependencias
target_link_libraries(MarIA PRIVATE 
    sfml-graphics 
    sfml-window 
    sfml-system 
    sfml-audio
    # Agrega otras bibliotecas si es necesario
)

# Copiar recursos después de compilar (opcional pero recomendado)
add_custom_command(TARGET MarIA POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets 
        $<TARGET_FILE_DIR:MarIA>/assets
    COMMENT "Copiando recursos al directorio de salida"
)

# Mensaje de confirmación
message(STATUS "Configuración completa para proyecto MarIA")
message(STATUS "Usando SFML v${SFML_VERSION}")
