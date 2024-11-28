#include "Button.h"

Button::Button(float posX, float posY, float width, float height, sf::Color color,
               const std::string& label, sf::Font& font) {
    // Setup the rectangle shape
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(posX, posY);
    shape.setFillColor(color);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);

    // Setup the label
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);

    // Center the text in the button
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
    text.setPosition(posX + width / 2.0f, posY + height / 2.0f - 5);
}

void Button::draw(sf::RenderWindow& window) {
    if (isMouseOver(window)) {
        shape.setFillColor(shape.getFillColor() + sf::Color(30, 30, 30));
    }

    window.draw(shape);
    window.draw(text);

    shape.setFillColor(shape.getFillColor() - sf::Color(30, 30, 30));
}

bool Button::isMouseOver(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
