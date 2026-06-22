#include <iostream>

void takeDamageValue(int health, int damage) {
    health -= damage;
}

void takeDamageReference(int& health, int damage) {
    health -= damage;
}

int main() {
    int playerHealth = 100;
    takeDamageValue(playerHealth, 30);
    std::cout << "Health (value): " << playerHealth << std::endl; // Still 100
    takeDamageReference(playerHealth, 30);
    std::cout << "Health (reference): " << playerHealth << std::endl; // 70
    return 0;
}
