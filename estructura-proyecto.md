# Estructura de Carpetas Sugerida para MarIA (SFML)

Esta estructura está pensada para un juego modular, ordenado, fácil de expandir y mantener.  
Puedes adaptarla según tus necesidades, pero es ideal para proyectos C++ con SFML.

```
MarIA/
├── assets/                     # Recursos del juego (NO código)
│   ├── fonts/
│   ├── textures/
│   ├── sounds/
│   └── music/
│
├── src/                        # Código fuente C++
│   ├── core/                   # Lógica central del juego
│   │   ├── Player.h/cpp        # todos los .h los pasé al include/
│   │   ├── Enemy.h/cpp
│   │   ├── NPC.h/cpp
│   │   ├── AnimatedSprite.h/cpp
│   │   ├── Level.h/cpp
│   │   ├── CombatSystem.h/cpp
│   │   ├── QuestSystem.h/cpp
│   │   ├── SaveSystem.h/cpp
│   │   └── GameState.h
│   │
│   ├── ui/                     # Interfaz de usuario, HUD, menús
│   │   ├── HUD.h
│   │   ├── Menu.h/cpp
│   │   ├── GameOverScreen.h/cpp
│   │   ├── OptionsMenu.h/cpp
│   │   ├── QuestHUD.h
│   │   └── QuestSelector.h/cpp
│   │
│   ├── utils/                  # Utilidades generales
│   │   ├── ResourceManager.h/cpp
│   │   └── (otros utilitarios...)
│   │
│   └── main.cpp
│
├── include/                    # (Opcional) Headers públicos, si usas librerías externas o para instalar
│
├── build/                      # (No versionar) Carpeta de compilación
│
├── CMakeLists.txt              # Configuración de CMake
├── README.md                   # Documentación principal
├── .gitignore
└── (otros archivos de proyecto)
```

**Notas útiles:**
- Pon todos los recursos (imágenes, sonidos, fuentes) en la carpeta `assets/`, así no mezclas recursos con código.
- Los archivos `.h` y `.cpp` para cada clase van juntos en el mismo subdirectorio según su función.
- El archivo `main.cpp` va en `src/` para centralizar el punto de entrada.
- Si tu juego crece, puedes agregar más subcarpetas bajo `core/` (por ejemplo, `core/systems/` o `core/entities/`).

---

¿Quieres ejemplos de cómo referenciar rutas a assets en tu código usando esta estructura? ¿O necesitas ayuda para escribir el `CMakeLists.txt` básico para compilar esto?
