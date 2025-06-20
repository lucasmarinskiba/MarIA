#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>
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

// Ejemplo simple de objeto recolectable
struct Collectible {
    sf::Vector2f position;
    bool picked = false;
    Collectible(float x, float y) : position(x, y) {}
    sf::Vector2f getPosition() const { return position; }
};

std::vector<std::string> getDefaultDialogues() {
    return {"¡Hola!", "¡Buen trabajo!", "¡Chau!"};
}

int main() {
    // --- Inicialización de SFML y recursos ---
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Maria Game SFML");
    window.setFramerateLimit(60);
    ResourceManager rm;
    sf::Clock clock;

    // --- Cargar fuente PressStart2P-Regular ---
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/PressStart2P-Regular.ttf")) {
        std::cerr << "No se pudo cargar la fuente PressStart2P-Regular.ttf" << std::endl;
        return -1;
    }
    Menu menu(font);
    GameOverScreen gameOverScreen(font);
    OptionsMenu optionsMenu(font);

    // --- Estados del juego ---
    GameState state = GameState::MENU;

    // --- Texturas para sprites animados ---
    sf::Texture& playerTex = rm.loadTexture("assets/textures/player_sheet.png");
    sf::Texture& enemyTex = rm.loadTexture("assets/textures/enemy_sheet.png");
    sf::Texture& npcTex   = rm.loadTexture("assets/textures/npc_sheet.png");

    // --- NUEVAS TEXTURAS FÁTIMA ---
    sf::Texture& fatimaLandscapeTex = rm.loadTexture("assets/textures/fatima_landscape.jpg");
    sf::Sprite fatimaLandscapeSprite(fatimaLandscapeTex);

    sf::Texture& encinaTex = rm.loadTexture("assets/textures/encina.jpeg");
    sf::Sprite encinaSprite(encinaTex);
    encinaSprite.setPosition(600, 410);

    sf::Texture& virgenAparicionTex = rm.loadTexture("assets/textures/virgen_aparicion.jpg");
    sf::Sprite virgenAparicionSprite(virgenAparicionTex);
    virgenAparicionSprite.setPosition(650, 280);

    sf::Texture& luciaTex = rm.loadTexture("assets/textures/npc_lucia.png");
    sf::Sprite luciaSprite(luciaTex);
    luciaSprite.setPosition(580, 520);

    sf::Texture& jacintaTex = rm.loadTexture("assets/textures/npc_jacinta.jpg");
    sf::Sprite jacintaSprite(jacintaTex);
    jacintaSprite.setPosition(680, 520);

    sf::Texture& franciscoTex = rm.loadTexture("assets/textures/npc_francisco.jpg");
    sf::Sprite franciscoSprite(franciscoTex);
    franciscoSprite.setPosition(780, 520);

    // --- Inicialización del jugador ---
    Player player(rm);
    player.setTexture(playerTex, 64, 64, 4, 0.13f);
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

    // --- Cargar música de fondo ---
    sf::Music music;
    if (!music.openFromFile("assets/music/music 1.ogg")) {
        std::cerr << "No se pudo cargar la música de fondo." << std::endl;
    } else {
        music.setLoop(true);
        music.setVolume(70); // Ajusta el volumen si quieres
        music.play();
    }

    // --- Cargar efectos de sonido ---
    sf::SoundBuffer jumpBuffer, hitBuffer, pickupBuffer;
    if (!jumpBuffer.loadFromFile("assets/sounds/jump.wav")) {
        std::cerr << "No se pudo cargar jump.wav" << std::endl;
    }
    if (!hitBuffer.loadFromFile("assets/sounds/hit.wav")) {
        std::cerr << "No se pudo cargar hit.wav" << std::endl;
    }
    if (!pickupBuffer.loadFromFile("assets/sounds/pickup.wav")) {
        std::cerr << "No se pudo cargar pickup.wav" << std::endl;
    }
    sf::Sound jumpSound, hitSound, pickupSound;
    jumpSound.setBuffer(jumpBuffer);
    hitSound.setBuffer(hitBuffer);
    pickupSound.setBuffer(pickupBuffer);

    // --- Ejemplo de objetos recolectables ---
    std::vector<Collectible> collectibles;
    collectibles.emplace_back(300, 400);
    collectibles.emplace_back(600, 420);

    // --- Control de daño para evitar múltiples sonidos por segundo ---
    sf::Clock hitCooldownClock;
    float hitCooldown = 0.5f; // medio segundo entre golpes

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
                    // --- Salto: al presionar espacio y el jugador puede saltar ---
                    else if (event.key.code == sf::Keyboard::Space) {
                        if (player.canJump()) { // Suponiendo que tienes canJump()
                            jumpSound.play();
                            player.jump(); // Implementa esto según tu lógica
                        }
                        // Ataque del jugador a enemigos
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
                // Interacción con NPCs
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
                    for (auto& npc : npcs) {
                        if (npc.canInteract(player.getPosition()))
                            currentDialogue = npc.interact();
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

            // --- Ejemplo: Si el jugador muere, game over ---
            if (player.getHealth() <= 0)
                state = GameState::GAME_OVER;

            // --- SONIDO HIT: Si colisiona con un enemigo, recibe daño y suena hit ---
            for (auto& enemy : enemies) {
                if (enemy.isAlive()) {
                    sf::Vector2f diff = enemy.getPosition() - player.getPosition();
                    float distancia = std::sqrt(diff.x * diff.x + diff.y * diff.y);
                    if (distancia < 50.f) { // Umbral de colisión
                        if (hitCooldownClock.getElapsedTime().asSeconds() > hitCooldown) {
                            player.setHealth(player.getHealth() - 10.f);
                            hitSound.play();
                            hitCooldownClock.restart();
                        }
                    }
                }
            }

            // --- SONIDO PICKUP: Si recolecta un objeto ---
            for (auto& col : collectibles) {
                if (!col.picked) {
                    sf::Vector2f diff = col.getPosition() - player.getPosition();
                    float distancia = std::sqrt(diff.x * diff.x + diff.y * diff.y);
                    if (distancia < 40.f) { // Umbral de recogida
                        pickupSound.play();
                        col.picked = true;
                        score += 10; // Ejemplo: sumar puntos
                    }
                }
            }
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
            // DIBUJO DEL PAISAJE Y ELEMENTOS DE FÁTIMA
            window.draw(fatimaLandscapeSprite);
            window.draw(encinaSprite);
            window.draw(virgenAparicionSprite);
            window.draw(luciaSprite);
            window.draw(jacintaSprite);
            window.draw(franciscoSprite);

            // Aquí podrías dibujar tu nivel, fondo, etc.
            for (auto& enemy : enemies) if (enemy.isAlive()) window.draw(enemy);
            for (auto& npc : npcs) window.draw(npc);
            window.draw(player);

            // Dibuja los objetos recolectables no recogidos
            for (auto& col : collectibles) {
                if (!col.picked) {
                    sf::CircleShape shape(16);
                    shape.setFillColor(sf::Color::Yellow);
                    shape.setPosition(col.position);
                    window.draw(shape);
                }
            }

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
