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
│   │   ├── Player.cpp        # todos los .h los pasé al include/
│   │   ├── Enemy.cpp
│   │   ├── NPC.cpp
│   │   ├── AnimatedSprite.cpp
│   │   ├── Level.cpp
│   │   ├── CombatSystem.cpp
│   │   ├── QuestSystem.cpp
│   │   ├── SaveSystem.cpp
│   │   
│   ├── ui/                     # Interfaz de usuario, HUD, menús
│   │   ├── Menu.cpp
│   │   ├── GameOverScreen.cpp
│   │   ├── OptionsMenu.cpp
│   │   └── QuestSelector.cpp
│   │
│   ├── utils/                  # Utilidades generales
│   │   ├── ResourceManager.cpp
│   │   └── (otros utilitarios...)
│   │
│   └── main.cpp
│
├── include/
│   ├── Player.h
│   ├── Enemy.h
│   ├── NPC.h
│   ├── AnimatedSprite.h
│   ├── Level.h
│   ├── CombatSystem.h
│   ├── QuestSystem.h
│   ├── SaveSystem.h
│   ├── GameState.h
│   ├── ResourceManager.h
│   ├── HUD.h
│   ├── Menu.h
│   ├── GameOverScreen.h
│   ├── OptionsMenu.h
│   ├── QuestHUD.h
│   └── QuestSelector.h                    # (Opcional) Headers públicos, si usas librerías externas o para instalar
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
