#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "utils/ResourceManager.h"
#include "core/Player.h"
#include "core/NPC.h"
#include "core/Enemy.h"
#include "core/Level.h"
#include "core/CombatSystem.h"
#include "core/QuestSystem.h"
#include "ui/HUD.h"
#include "ui/Menu.h"
#include "ui/GameOverScreen.h"
#include "ui/OptionsMenu.h"
#include "ui/QuestHUD.h"
#include "ui/QuestSelector.h"
#include "core/GameState.h"
#include "core/SaveSystem.h"

int main() {
    // --- Inicialización de recursos y ventana ---
    ResourceManager rm;
    sf::Font font = rm.loadFont("assets/fonts/pixel.ttf");
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Maria Game SFML");
    window.setFramerateLimit(60);

    // --- Menús y pantallas ---
    Menu menu(font);
    GameOverScreen gameOverScreen(font);
    OptionsMenu optionsMenu(font);

    // --- Estados del juego ---
    GameState state = GameState::MENU;

    // --- Jugador, enemigos, combate, NPCs, nivel ---
    Player player(rm);
    CombatSystem combat;
    sf::Texture& enemyTex = rm.loadTexture("assets/textures/enemy.png");
    combat.addEnemy(Enemy(enemyTex, {700, 400}));
    combat.addEnemy(Enemy(enemyTex, {900, 500}));
    std::vector<NPC> npcs = { NPC(rm, {400, 400}, {"¡Buen trabajo derrotando enemigos!"}) };
    Level level(rm);

    // --- Misiones y selector ---
    QuestSystem questSystem;
    questSystem.addQuest(
        "Derrota a todos los enemigos",
        "Acaba con todos los enemigos en pantalla.",
        [&combat]() {
            for (const auto& e : combat.getEnemies())
                if (e.isAlive()) return false;
            return true;
        }
    );
    QuestSelector questSelector(font, questSystem);

    // --- Guardado/Carga ---
    bool showSaveNotice = false, showLoadNotice = false;
    sf::Clock noticeClock;

    // --- Variables de UI ---
    std::string currentDialogue;
    int score = 0;

    // --- Bucle principal ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // --- Menú principal ---
            if (state == GameState::MENU) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter)
                        state = GameState::PLAYING;
                    else if (event.key.code == sf::Keyboard::O)
                        state = GameState::OPTIONS;
                    else if (event.key.code == sf::Keyboard::L) {
                        if (SaveSystem::load(player)) {
                            showLoadNotice = true;
                            noticeClock.restart();
                        }
                    }
                }
            }

            // --- Opciones ---
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

            // --- Pausa y salida ---
            else if (state == GameState::PLAYING) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape)
                        state = GameState::PAUSED;
                    else if (event.key.code == sf::Keyboard::S) {
                        SaveSystem::save(player);
                        showSaveNotice = true;
                        noticeClock.restart();
                    }
                    else if (event.key.code == sf::Keyboard::L) {
                        if (SaveSystem::load(player)) {
                            showLoadNotice = true;
                            noticeClock.restart();
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Tab) {
                        state = GameState::SELECT_QUEST;
                    }
                }
                // --- Interacción con NPCs ---
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
                    for (auto& npc : npcs) {
                        if (npc.canInteract(player.getPosition()))
                            currentDialogue = npc.interact();
                    }
                }
                // --- Ataque del jugador ---
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                    combat.playerAttack(player.getPosition(), 60.f, 20.f);
                }
            }

            else if (state == GameState::PAUSED) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape)
                        state = GameState::PLAYING;
                    else if (event.key.code == sf::Keyboard::Q)
                        window.close();
                }
            }

            // --- Selector de misión ---
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

            // --- Game Over ---
            else if (state == GameState::GAME_OVER) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        player.reset(); // Debes implementar reset() en Player
                        combat = CombatSystem(); // Reinicia enemigos
                        state = GameState::MENU;
                        score = 0;
                    }
                    else if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                }
            }
        }

        float dt = 1.f / 60.f; // Usa clock para mayor precisión si quieres

        // --- Lógica de juego solo si estamos jugando ---
        if (state == GameState::PLAYING) {
            player.update(dt);
            for (auto& npc : npcs) npc.update(dt, player.getPosition());
            combat.update(dt, player.getPosition());
            questSystem.update();

            // Si el jugador muere, game over
            if (player.getHealth() <= 0)
                state = GameState::GAME_OVER;
        }

        // --- DIBUJADO ---
        window.clear(sf::Color(10,10,20));

        if (state == GameState::MENU) {
            menu.drawMainMenu(window);
            sf::Text saveMsg("S: Guardar partida | L: Cargar partida | O: Opciones", font, 22);
            saveMsg.setPosition(320, 500);
            saveMsg.setFillColor(sf::Color::White);
            window.draw(saveMsg);
            if (showSaveNotice && noticeClock.getElapsedTime().asSeconds() < 2.f) {
                sf::Text notice("¡Progreso guardado!", font, 28);
                notice.setPosition(500, 600);
                notice.setFillColor(sf::Color::Green);
                window.draw(notice);
            }
            if (showLoadNotice && noticeClock.getElapsedTime().asSeconds() < 2.f) {
                sf::Text notice("¡Progreso cargado!", font, 28);
                notice.setPosition(500, 600);
                notice.setFillColor(sf::Color::Cyan);
                window.draw(notice);
            }
        }
        else if (state == GameState::OPTIONS) {
            optionsMenu.draw(window);
        }
        else if (state == GameState::PLAYING) {
            level.draw(window, player, npcs);
            combat.draw(window);
            drawHUD(window, font, player.getHealth(), player.getMaxHealth(), player.getFaith(), player.getMaxFaith());
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
                notice.setPosition(500, 600);
                notice.setFillColor(sf::Color::Cyan);
                window.draw(notice);
            }

            // Diálogo
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

        // Quitar notificaciones tras 2 segundos
        if (noticeClock.getElapsedTime().asSeconds() > 2.f) {
            showSaveNotice = false;
            showLoadNotice = false;
        }
    }
    return 0;
}
