#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "utils/ResourceManager.h"
#include "core/Player.h"
#include "core/NPC.h"
#include "core/Level.h"
#include "ui/HUD.h"
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Maria Game SFML");
    window.setFramerateLimit(60);

    ResourceManager rm;
    sf::Font font = rm.loadFont("assets/fonts/pixel.ttf");

    Player player(rm);
    std::vector<NPC> npcs = {
        NPC(rm, {400, 400}, {"Hola!", "¿Cómo estás?", "Hasta luego!"})
    };
    Level level(rm);

    std::string currentDialogue;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
                for (auto& npc : npcs) {
                    if (npc.canInteract(player.getPosition())) {
                        currentDialogue = npc.interact();
                    }
                }
            }
        }

        float dt = 1.f / 60.f; // Usa clock si quieres precisión
        player.update(dt);
        for (auto& npc : npcs) npc.update(dt, player.getPosition());
        level.update(dt, player, npcs);

        window.clear(sf::Color(10,10,20));
        level.draw(window, player, npcs);
        drawHUD(window, font, player.getHealth(), player.getMaxHealth(), player.getFaith(), player.getMaxFaith());
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
        window.display();
    }
    return 0;
}
