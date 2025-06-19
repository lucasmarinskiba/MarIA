#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "utils/ResourceManager.h"
#include "core/Player.h"
#include "core/NPC.h"
#include "core/Level.h"
#include "core/CombatSystem.h"
#include "core/QuestSystem.h"
#include "ui/HUD.h"
#include "ui/Menu.h"
#include "ui/QuestHUD.h"
#include "core/GameState.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Maria Game SFML");
    window.setFramerateLimit(60);

    ResourceManager rm;
    sf::Font font = rm.loadFont("assets/fonts/pixel.ttf");

    // Menú y estados
    Menu menu(font);
    GameState state = GameState::MENU;

    // Jugador, enemigos y combate
    Player player(rm);
    CombatSystem combat;
    sf::Texture& enemyTex = rm.loadTexture("assets/textures/enemy.png");
    combat.addEnemy(Enemy(enemyTex, {700, 400}));
    combat.addEnemy(Enemy(enemyTex, {900, 500}));

    // Misiones
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

    // NPCs y nivel
    std::vector<NPC> npcs = { NPC(rm, {400, 400}, {"¡Buen trabajo derrotando enemigos!"}) };
    Level level(rm);

    std::string currentDialogue;

    // Bucle principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // --- Menú principal ---
            if (state == GameState::MENU && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                state = GameState::PLAYING;

            // --- Pausa y salida ---
            if (state == GameState::PLAYING && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                state = GameState::PAUSED;
            else if (state == GameState::PAUSED) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    state = GameState::PLAYING;
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
                    window.close();
            }

            // --- Interacción con NPCs ---
            if (state == GameState::PLAYING && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
                for (auto& npc : npcs) {
                    if (npc.canInteract(player.getPosition()))
                        currentDialogue = npc.interact();
                }
            }

            // --- Ataque del jugador (barra espaciadora) ---
            if (state == GameState::PLAYING && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                // Ataque circular alrededor del jugador
                combat.playerAttack(player.getPosition(), 60.f, 20.f);
            }
        }

        float dt = 1.f / 60.f; // Puedes usar un clock para mayor precisión

        // Lógica de juego solo si estamos jugando
        if (state == GameState::PLAYING) {
            player.update(dt);
            for (auto& npc : npcs) npc.update(dt, player.getPosition());
            combat.update(dt, player.getPosition());
            questSystem.update();
        }

        // --- DIBUJADO ---
        window.clear(sf::Color(10,10,20));

        if (state == GameState::MENU) {
            menu.drawMainMenu(window);
        } else if (state == GameState::PLAYING) {
            level.draw(window, player, npcs);
            combat.draw(window);
            drawHUD(window, font, player.getHealth(), player.getMaxHealth(), player.getFaith(), player.getMaxFaith());
            drawQuestHUD(window, font, questSystem);

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
        } else if (state == GameState::PAUSED) {
            menu.drawPauseMenu(window);
        }

        window.display();
    }
    return 0;
}
