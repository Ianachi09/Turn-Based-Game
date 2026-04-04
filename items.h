#pragma once
#include <iostream>
#include <string>

class Character;

class Item {
public:
    std::string name;

    Item(std::string name) {
        this->name = name;
    }

    virtual void use(Character* target) = 0;
};

class Potion : public Item {
public:
    int healAmount;
    Potion(std::string name, int heal) : Item(name) {
        healAmount = heal;
    }
    void use(Character* target) override;
};

class Bomb : public Item {
public:
    int damageAmount;
    Bomb(std::string name, int damage) : Item(name) {
        damageAmount = damage;
    }
    void use(Character* target) override;
};