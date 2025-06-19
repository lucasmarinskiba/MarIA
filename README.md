# MarIA

**MarIA** es un juego 2D de aventuras desarrollado en C++ usando [SFML](https://www.sfml-dev.org/).

## Características principales

- Jugabilidad inspirada en RPGs clásicos.
- Sistema de misiones, combate, NPCs, guardado/carga y animaciones.
- Código modular y fácil de expandir.
- Recursos externos manejados con un ResourceManager.

## Requisitos

- CMake >= 3.15
- SFML >= 2.5 (gráficos, audio, window, system)
- Un compilador C++17 (g++/clang++/MSVC)

## Compilación

```bash
git clone https://github.com/lucasmarinskiba/MarIA.git
cd MarIA
mkdir build && cd build
cmake ..
cmake --build .
```

Los ejecutables y los assets estarán en la carpeta `build/`.

## Estructura del Proyecto

```
assets/      # Imágenes, sonidos, fuentes, etc.
src/         # Código fuente (C++)
  core/      # Lógica del juego, entidades, sistemas
  ui/        # HUD, menús, pantallas
  utils/     # Utilidades generales
  main.cpp
CMakeLists.txt
README.md
.gitignore
```

## Créditos

- [SFML](https://www.sfml-dev.org/) - Librería multimedia
- Recursos artísticos y sonoros: ver carpeta `assets/`

## Licencia

MIT. Consulta el archivo LICENSE para más detalles.
