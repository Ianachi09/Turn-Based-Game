#include "items.h"
#include "characters.h" 

// --- THE LOGIC ---

void Potion::use(Character* target) {
    target->heal(healAmount);
    std::cout << "\nUsed " << name << "! Restored " << healAmount << " HP.\n";
}

void Bomb::use(Character* target) {
    target->takeDamage(damageAmount); 
    std::cout << "\nUsed " << name << "! Dealt " << damageAmount << " damage.\n";
}