/*
Question for demonstration Pass Types
Pass by value vs pass by reference

You’re writing a health system for a game. The function takeDamage() should reduce a player’s health. 
But only one of these versions works.

Implement both of the following:

    void takeDamageValue(int health, int damage) // value

    void takeDamageReference(int& health, int damage) // reference

In main(), test both and print the resulting health.

Reflect: Why does one work and the other not?
*/

#include <iostream>

// TODO: implement takeDamageValue

// TODO: implement takeDamageReference

int main() {
    int playerHealth = 100;
    // TODO: call takeDamageValue with a damage of 30
    std::cout << "Health (value): " << playerHealth << std::endl; // Predict the output before running your program
    // TODO: call takeDamageReference with a damage of 30
    std::cout << "Health (reference): " << playerHealth << std::endl; // Predict the output before running your program
    return 0;
}