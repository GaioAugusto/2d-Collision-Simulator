#ifndef Button_h
#define Button_h

#include <SFML/Graphics.hpp>
#define BUTTON_HEIGHT 50
#define BUTTON_WIDTH 50

class Button : public sf::RectangleShape {
 public:
  // Constructor
  Button(int posX, int posY, sf::Color color);
};

#endif