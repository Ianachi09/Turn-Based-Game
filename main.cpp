#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

#include "characters.h"
#include "items.h"

class Game {
private:
    Player* player;
    bool isRunning;

public:
    Game() {
        srand(time(0));
        player = new Player("Warrior");
        isRunning = true;
    }

    ~Game() {
        delete player;
    }

    Enemy spawnRandomEnemy() {
        int randomNum = rand() % 3; // Generates 0, 1, or 2

        switch (randomNum) {
            case 0: 
                return Enemy("Wild Slime", 40, 5);
            case 1: 
                return Enemy("Goblin Scout", 60, 10);
            case 2: 
                return Enemy("Angry Wolf", 80, 15);
            default: 
                return Enemy("MissingNo", 10, 1); // Just in case!
        }
    }

    void battle() {
        Enemy currentEnemy = spawnRandomEnemy();
        std::cout << "=================================\n";
        std::cout << "A " << currentEnemy.name << " appears!\n";
        std::cout << "=================================\n";
        
        while (player->getHealth() > 0 && currentEnemy.getHealth() > 0) {
            std::cout << std::endl;
            std::cout << player->name << " \t" << currentEnemy.name << std::endl;
            std::cout << "Health: " << player->getHealth() << " \t" << "Health: " << currentEnemy.getHealth() << std::endl;
            std::cout << "[1] Attack\n";
            std::cout << "[2] Item\n";
            std::cout << "Choose an action: ";

            int choice;
            std::cin >> choice;

            if (std::cin.fail()) { 
                std::cin.clear();  // Clear the panic state 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Throw away the bad input (data other than integers, what cin is asking for)
                std::cout << "Invalid choice. Please try again.\n";
                continue;
            } 


            switch (choice) {
                case 1:
                    system("clear");
                    player->attackTarget(&currentEnemy);
                    break;
                
                case 2:
                    std::cout << "You reached into your bag. . .\n";
                    if (player->inventory.empty()){
                        std::cout << "But there is nothing inside.\n";
                        std::cout << std::endl;
                        std::cout << "=================================\n";
                        continue;              
                    }

                    std::cout << "=================================\n";
                    std::cout << "            Inventory            \n";
                    std::cout << "=================================\n";
                    std::cout << std::endl;
                    for (size_t i=0; i < player->inventory.size();  i++) {
                        std::cout << "[" << i+1 << "] " << player->inventory[i]->name << std::endl;
                    }
                    std::cout << "[0] Cancel\n";
                    std::cout << "Choose an item: ";

                    int itemChoice;
                    std::cin >> itemChoice;

                    if (std::cin.fail()) { 
                        std::cin.clear();  // Clear the panic state 
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Throw away the bad input (data other than integers, what cin is asking for)
                        std::cout << "Invalid choice. Please try again.\n";
                        continue;
                    } 

                    if (itemChoice == 0) {
                        continue;
                    } else if (itemChoice > 0 && itemChoice <= player->inventory.size()) {
                        Item* selectedItem = player->inventory[itemChoice -1];
                        
                        system("clear");
                        if (selectedItem->name == "Grenade") {
                            selectedItem->use(&currentEnemy);
                        } else {
                            selectedItem->use(player);
                        }

                        player->inventory.erase(player->inventory.begin() + (itemChoice -1));
                    } 
                    break;
            }

            if (currentEnemy.getHealth() > 0) {
                std::cout << std::endl;
                currentEnemy.attackTarget(player);
                std::cout << std::endl;
                std::cout << "=================================\n";
            }
        }

        if (player->getHealth() > 0) {
            std::cout << "\nYou won the battle!\n";
            std::cout << std::endl;
            std::cout << "=================================\n";
        } else {
            std::cout << "\nYou blacked out. . .\n";
            isRunning = false;
        }
    }

    void run() {
        std::cout << "=================================\n";
        std::cout << "        Welcome to the Game      \n";
        std::cout << "=================================\n";
        while (isRunning) {
            std::cout << "[1] Play\n";
            std::cout << "[2] Exit Game\n";
            std::cout << "Choice: ";

            int choice;
            std::cin >> choice;

            if (std::cin.fail()) { 
                std::cin.clear();  // Clear the panic state 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Throw away the bad input (data other than integers, what cin is asking for)
                std::cout << "Invalid choice. Please try again.\n";
                continue;
            }


            switch (choice) {
                case 1:
                    system("clear");
                    battle();
                    break;
                case 2:
                    std::cout << "\nExiting game. . .";
                    isRunning = false;
                    break;          
            }

        }
    }
};



int main() {
    Game session;
    session.run();
    return 0;
}