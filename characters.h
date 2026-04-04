#pragma once
#include <string>
#include <iostream>
#include <vector>

#include "items.h"

class Character {
protected:
    int health;
    int maxHealth;
    int baseAttack;

public:
    std::string name;

    Character(std::string name, int health, int baseAttack) {
        this->name = name;
        maxHealth = health;
        this->health = health;
        this->baseAttack = baseAttack;
    }

    int getHealth() {
        return health;
    }
    int getMaxHealth() {
        return maxHealth;
    }
     int getBaseAttack() {
        return baseAttack;
    }

    void attackTarget(Character* target) {
        target->takeDamage(baseAttack);
        std::cout << name << " attacked " << target->name << " for " << baseAttack << " Damage!\n";
    }

    void takeDamage(int amount) {
        health -= amount;
        if (health < 0) {
            health = 0;
        }
    }

    void heal(int amount) {
        health += amount;
        if (health > maxHealth) {
            health = maxHealth;
        }
    }
};

class Player : public Character {
public:
    std::vector<Item*> inventory;
    
    // Constructor (Set stats and items)
    Player(std::string name) : Character(name, 100, 20) {

        inventory.push_back(new Potion("Small Potion", 25));
        inventory.push_back(new Bomb("Grenade", 30));
    }

    // Deconstructor (Removes every item in inventory)
    ~Player() {
        for (Item* item : inventory) {
            delete item;
        }
    }
};

class Enemy : public Character {
public:
    Enemy(std::string name, int health, int baseAttack) : Character(name, health, baseAttack) {

    }
};