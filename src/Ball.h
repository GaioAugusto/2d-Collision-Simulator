#ifndef Ball_h
#define Ball_h



#include <stdlib.h>
#include <SFML/Graphics.hpp>
constexpr int BALL_WIDTH = 800;
constexpr int BALL_HEIGHT = 800;
#define VELOCITY 0.1f
#define NUM_OF_POINTS 200
#define BALL_SIZE 50


// Function to get a random color
sf::Color getRandomColor();

class Ball : public sf::CircleShape {
 private:
  sf::Vector2f velocity;      // Velocity of the ball
  sf::FloatRect boundingBox;  // Responsible for dealing with collisions

 public:
  // Constructors
  Ball();

  Ball(float size);

  // Setters and Getters for velocity
  void setVelocity(sf::Vector2f vel);

  sf::Vector2f getVelocity();

  // Update the ball's position based on its velocity
  // Make sure the balls will not go out of the bounds of the window
  void update(const sf::RenderWindow& window);

  // Additional method to set the ball's initial position within bounds
  void setRandomPosition();

    // Check collisions with other balls and deal with it
    void checkCollisionWithOtherBalls(int indexOfBall, std::vector<Ball>& balls);
    // Handle velocity of the ball
    void increaseBallVelocity();
    void decreaseBallVelocity();
};

#endif