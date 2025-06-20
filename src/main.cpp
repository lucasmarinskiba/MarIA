#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "utils/ResourceManager.h"
#include "core/Player.h"
#include "core/Enemy.h"
#include "core/NPC.h"
#include "core/Level.h"
#include "core/QuestSystem.h"
#include "core/SaveSystem.h"
#include "ui/Menu.h"
#include "ui/HUD.h"
#include "ui/GameOverScreen.h"
#include "ui/OptionsMenu.h"
#include "ui/QuestHUD.h"
#include "ui/QuestSelector.h"
#include "core/GameState.h"

// Utilidad para crear diálogos de NPCs
std::vector<std::string> getDefaultDialogues() {
    return {"¡Hola!", "¡Buen trabajo!", "¡Chau!"};
}

int main() {
    // --- Inicialización de SFML y recursos ---
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Maria Game SFML");
    window.setFramerateLimit(60);
    ResourceManager rm;
    sf::Clock clock;

    // --- Carga de fuentes y menús ---
    sf::Font font = rm.loadFont("assets/fonts/PressStart2P-Regular.ttf");
    Menu menu(font);
    GameOverScreen gameOverScreen(font);
    OptionsMenu optionsMenu(font);

    // carga audio, música 
    sf::Music music;
    if (!music.openFromFile("assets/music/music 1.mp3")) {
        std::cerr << "No se pudo cargar la música." << std::endl;
    } else {
        music.setLoop(true); // Para que suene en bucle
        music.play();
    }

    // --- Estados del juego ---
    GameState state = GameState::MENU;

    // --- Texturas para sprites animados ---
    sf::Texture& playerTex = rm.loadTexture("assets/textures/player_sheet.png");
    sf::Texture& enemyTex = rm.loadTexture("assets/textures/enemy_sheet.png");
    sf::Texture& npcTex   = rm.loadTexture("assets/textures/npc_sheet.png");

    // --- Inicialización del jugador ---
    Player player(rm);
    player.setTexture(playerTex, 64, 64, 4, 0.13f); // 4 frames animación
    player.setPosition({100, 400});

    // --- Inicialización de enemigos animados ---
    std::vector<Enemy> enemies;
    enemies.emplace_back(); enemies.back().init(enemyTex, {700, 400});
    enemies.emplace_back(); enemies.back().init(enemyTex, {900, 500});

    // --- Inicialización de NPCs animados ---
    std::vector<NPC> npcs;
    npcs.emplace_back(); npcs.back().init(npcTex, {400, 400}, getDefaultDialogues());

    // --- Inicialización de misiones y selector ---
    QuestSystem questSystem;
    questSystem.addQuest(
        "Derrota a todos los enemigos",
        "Acaba con todos los enemigos en pantalla.",
        [&enemies]() {
            for (const auto& e : enemies)
                if (e.isAlive()) return false;
            return true;
        }
    );
    QuestSelector questSelector(font, questSystem);

    // --- Guardado/Carga y notificaciones ---
    bool showSaveNotice = false, showLoadNotice = false;
    sf::Clock noticeClock;

    // --- Variables de UI ---
    std::string currentDialogue;
    int score = 0;

    // --- Bucle principal ---
    while (window.isOpen()) {
        // --- Manejo de eventos (input del usuario) ---
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Menú principal
            if (state == GameState::MENU) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter)
                        state = GameState::PLAYING;
                    else if (event.key.code == sf::Keyboard::O)
                        state = GameState::OPTIONS;
                    else if (event.key.code == sf::Keyboard::L) {
                        if (SaveSystem::load(player, enemies, enemyTex, npcs, npcTex, questSystem)) {
                            showLoadNotice = true;
                            noticeClock.restart();
                        }
                    }
                }
            }

            // Opciones gráficas
            else if (state == GameState::OPTIONS) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape)
                        state = GameState::MENU;
                    else if (event.key.code == sf::Keyboard::Right)
                        optionsMenu.nextResolution();
                    else if (event.key.code == sf::Keyboard::Left)
                        optionsMenu.prevResolution();
                }
            }

            // Juego en curso (jugar)
            else if (state == GameState::PLAYING) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape)
                        state = GameState::PAUSED;
                    else if (event.key.code == sf::Keyboard::S) {
                        SaveSystem::save(player, enemies, npcs, questSystem);
                        showSaveNotice = true;
                        noticeClock.restart();
                    }
                    else if (event.key.code == sf::Keyboard::L) {
                        if (SaveSystem::load(player, enemies, enemyTex, npcs, npcTex, questSystem)) {
                            showLoadNotice = true;
                            noticeClock.restart();
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Tab) {
                        state = GameState::SELECT_QUEST;
                    }
                }
                // Interacción con NPCs
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
                    for (auto& npc : npcs) {
                        // Suponiendo que tienes canInteract y interact implementados
                        if (npc.canInteract(player.getPosition()))
                            currentDialogue = npc.interact();
                    }
                }
                // Ataque del jugador
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                    for (auto& enemy : enemies) {
                        if (enemy.isAlive()) {
                            sf::Vector2f diff = enemy.getPosition() - player.getPosition();
                            if (sqrt(diff.x*diff.x + diff.y*diff.y) < 60.f)
                                enemy.setHealth(enemy.getHealth() - 20.f);
                            if (enemy.getHealth() <= 0) enemy.setAlive(false);
                        }
                    }
                }
            }

            // Pausa y salida
            else if (state == GameState::PAUSED) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape)
                        state = GameState::PLAYING;
                    else if (event.key.code == sf::Keyboard::Q)
                        window.close();
                }
            }

            // Selector de misiones
            else if (state == GameState::SELECT_QUEST) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Tab)
                        state = GameState::PLAYING;
                    else if (event.key.code == sf::Keyboard::Down)
                        questSelector.next();
                    else if (event.key.code == sf::Keyboard::Up)
                        questSelector.prev();
                }
            }

            // Game Over
            else if (state == GameState::GAME_OVER) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        player.setPosition({100, 400});
                        player.setHealth(100.f);
                        player.setFaith(100.f);
                        for (auto& enemy : enemies) enemy.setAlive(true), enemy.setHealth(30.f);
                        state = GameState::MENU;
                        score = 0;
                    }
                    else if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                }
            }
        }

        // --- Cálculo del delta time ---
        float dt = clock.restart().asSeconds();

        // --- Actualización de lógica del juego ---
        if (state == GameState::PLAYING) {
            player.update(dt);

            for (auto& enemy : enemies)
                if (enemy.isAlive()) enemy.update(dt);

            for (auto& npc : npcs)
                npc.update(dt);

            questSystem.update();

            // Ejemplo: Si el jugador muere, game over
            if (player.getHealth() <= 0)
                state = GameState::GAME_OVER;
        }

        // --- Dibujo ---
        window.clear(sf::Color(10,10,20));

        if (state == GameState::MENU) {
            menu.drawMainMenu(window);
            sf::Text auxMsg("S: Guardar | L: Cargar | O: Opciones", font, 22);
            auxMsg.setPosition(320, 500);
            auxMsg.setFillColor(sf::Color::White);
            window.draw(auxMsg);
            if (showSaveNotice && noticeClock.getElapsedTime().asSeconds() < 2.f) {
                sf::Text notice("¡Progreso guardado!", font, 28);
                notice.setPosition(500, 600);
                notice.setFillColor(sf::Color::Green);
                window.draw(notice);
            }
            if (showLoadNotice && noticeClock.getElapsedTime().asSeconds() < 2.f) {
                sf::Text notice("¡Progreso cargado!", font, 28);
                notice.setPosition(500, 630);
                notice.setFillColor(sf::Color::Cyan);
                window.draw(notice);
            }
        }
        else if (state == GameState::OPTIONS) {
            optionsMenu.draw(window);
        }
        else if (state == GameState::PLAYING) {
            // Aquí podrías dibujar tu nivel, fondo, etc.
            for (auto& enemy : enemies) if (enemy.isAlive()) window.draw(enemy);
            for (auto& npc : npcs) window.draw(npc);
            window.draw(player);

            drawHUD(window, font, player.getHealth(), 100.f, player.getFaith(), 100.f);
            drawQuestHUD(window, font, questSystem);

            // Notificaciones de guardado/carga
            if (showSaveNotice && noticeClock.getElapsedTime().asSeconds() < 2.f) {
                sf::Text notice("¡Progreso guardado!", font, 28);
                notice.setPosition(500, 600);
                notice.setFillColor(sf::Color::Green);
                window.draw(notice);
            }
            if (showLoadNotice && noticeClock.getElapsedTime().asSeconds() < 2.f) {
                sf::Text notice("¡Progreso cargado!", font, 28);
                notice.setPosition(500, 630);
                notice.setFillColor(sf::Color::Cyan);
                window.draw(notice);
            }

            // Diálogo NPC
            if (!currentDialogue.empty()) {
                sf::RectangleShape bg({800, 60});
                bg.setFillColor(sf::Color(0,0,0,180));
                bg.setPosition(240, 600);
                window.draw(bg);
                sf::Text dialogue(currentDialogue, font, 28);
                dialogue.setFillColor(sf::Color::White);
                dialogue.setPosition(250, 610);
                window.draw(dialogue);
            }
        }
        else if (state == GameState::PAUSED) {
            menu.drawPauseMenu(window);
        }
        else if (state == GameState::SELECT_QUEST) {
            questSelector.draw(window);
        }
        else if (state == GameState::GAME_OVER) {
            gameOverScreen.draw(window, score);
        }

        window.display();

        if (noticeClock.getElapsedTime().asSeconds() > 2.f) {
            showSaveNotice = false;
            showLoadNotice = false;
        }
    }
    return 0;
}
