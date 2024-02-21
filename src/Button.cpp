#include <SFML/Graphics.hpp>
#include "Button.h"
#define BUTTON_HEIGHT 50
#define BUTTON_WIDTH 50


// Constructor
Button::Button(int posX, int posY, sf::Color color) {
    this->setSize(sf::Vector2f(BUTTON_WIDTH,
                                BUTTON_HEIGHT));  // Set the size of the button
    this->setPosition(posX, posY);
    this->setFillColor(color);
}
