// #ifndef BUTTON_H
// #define BUTTON_H

// #include <SFML/Graphics.hpp>
// #include "RoundedRectangleShape.h"

// class Button {
// public:
//     Button(float posX, float posY, float width, float height, sf::Color color,
//            const std::string& label, sf::Font& font);

//     void draw(sf::RenderWindow& window);
//     bool isMouseOver(sf::RenderWindow& window);

// private:
//     RoundedRectangleShape shape;
//     sf::Text text;
// };

// #endif

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(float posX, float posY, float width, float height, sf::Color color,
           const std::string& label, sf::Font& font);

    void draw(sf::RenderWindow& window);
    bool isMouseOver(sf::RenderWindow& window);

private:
    sf::RectangleShape shape; // Simple rectangle shape
    sf::Text text;            // Button label
};

#endif
