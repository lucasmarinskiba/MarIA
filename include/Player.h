#pragma once

#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "ResourceManager.h"
#include <fstream>
#include <vector>
#include <string>

class NPC;

struct Item {
    std::string name;
    int quantity;
};

class Player : public AnimatedSprite {
public:
    Player(ResourceManager& rm);

    // Serialización
    void save(std::ofstream& out) const;
    void load(std::ifstream& in);

    // Actualización
    void update(float dt);
    
    // Usamos el draw de la clase base (eliminado el draw redundante)
    // Getters y setters
    float getHealth() const { return health; }
    float getMaxHealth() const { return maxHealth; }
    float getFaith() const { return faith; }
    float getMaxFaith() const { return maxFaith; }
    int getLevel() const { return level; }
    int getExperience() const { return experience; }
    
    // Usamos getPosition de AnimatedSprite
    bool isAlive() const { return alive; }

    void setHealth(float h);
    void setFaith(float f);
    void addExperience(int amount);
    void reset();

    // Inventario
    void addItem(const std::string& name, int quantity = 1);
    bool hasItem(const std::string& name, int quantity = 1) const;
    void removeItem(const std::string& name, int quantity = 1);
    const std::vector<Item>& getInventory() const { return inventory; }

    // Combate
    void attack(NPC& npc);
    void takeDamage(float amount);

    // Interacción
    void interact(NPC& npc);

private:
    float health = 100.f;
    float maxHealth = 100.f;
    float faith = 100.f;
    float maxFaith = 100.f;
    float speed = 200.f;
    int experience = 0;
    int level = 1;
    bool alive = true;
    std::vector<Item> inventory;
};
