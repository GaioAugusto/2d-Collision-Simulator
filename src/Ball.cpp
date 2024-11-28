#include "Ball.h"
#include <cmath>

// Function to get a random color
sf::Color getRandomColor() {
  std::vector<sf::Color> colours = {sf::Color::Green, sf::Color::Red,
                                    sf::Color::Blue,  sf::Color::White,
                                    sf::Color::Cyan,  sf::Color::Magenta};
  int randomIndex = std::rand() % colours.size();
  return colours[randomIndex];
}



  // Constructors
Ball::Ball() : sf::CircleShape(BALL_SIZE), velocity(VELOCITY, VELOCITY) {
    this->setFillColor(getRandomColor());
    this->setPointCount(NUM_OF_POINTS);
}

Ball::Ball(float size) : sf::CircleShape(size / 2), velocity(VELOCITY, VELOCITY) {
    this->setFillColor(getRandomColor());
    this->setPointCount(NUM_OF_POINTS);
}

// Setters and Getters for velocity
void Ball::setVelocity(sf::Vector2f vel) { velocity = vel; }

sf::Vector2f Ball::getVelocity() { return velocity; }

// Update the ball's position based on its velocity
// Make sure the balls will not go out of the bounds of the window
// void Ball::update(const sf::RenderWindow& window) {
//     // Move the ball by its current velocity
//     this->move(velocity);

//     // Get the ball's current position
//     sf::Vector2f pos = this->getPosition();

//     // Reverse the velocity if the ball hits the window bounds
//     if (pos.x < 0 || pos.x + 2 * this->getRadius() > window.getSize().x) {
//       velocity.x = -velocity.x;
//     }
//     if (pos.y < 0 || pos.y + 2 * this->getRadius() > window.getSize().y) {
//       velocity.y = -velocity.y;
//     }
// }

// // Additional method to set the ball's initial position within bounds
// void Ball::setRandomPosition() {
//     int maxX = BALL_WIDTH - this->getRadius() * 2;
//     int maxY = BALL_HEIGHT - this->getRadius() * 2;
//     this->setPosition(std::rand() % maxX + this->getRadius(), std::rand() % maxY + this->getRadius());
// }



void Ball::update(const sf::RenderWindow& window) {
    // Move the ball by its current velocity
    this->move(velocity);

    // Get the ball's current position and size
    sf::Vector2f pos = this->getPosition();
    float radius = this->getRadius();

    // Reverse the velocity if the ball hits the window bounds
    if (pos.x <= 0 && velocity.x < 0) {
        velocity.x = -velocity.x;
    }
    if (pos.x + 2 * radius >= window.getSize().x && velocity.x > 0) {
        velocity.x = -velocity.x;
    }
    if (pos.y <= 0 && velocity.y < 0) {
        velocity.y = -velocity.y;
    }
    if (pos.y + 2 * radius >= window.getSize().y && velocity.y > 0) {
        velocity.y = -velocity.y;
    }
}

void Ball::setRandomPosition() {
    float radius = this->getRadius();
    float maxX = 800 - 2 * radius; // Use window width
    float maxY = 600 - 2 * radius; // Use window height
    this->setPosition(std::rand() % static_cast<int>(maxX) + radius,
                      std::rand() % static_cast<int>(maxY) + radius);
}








// Check collisions with other balls and deal with it
void Ball::checkCollisionWithOtherBalls(int indexOfBall, std::vector<Ball>& balls) {
    for (int counter = 0; counter < balls.size(); counter++) {
      if (indexOfBall != counter) {
        Ball& ballA = balls[indexOfBall];
        Ball& ballB = balls[counter];

        sf::Vector2f positionA =
            ballA.getPosition() + sf::Vector2f(BALL_SIZE / 2, BALL_SIZE / 2);
        sf::Vector2f positionB =
            ballB.getPosition() + sf::Vector2f(BALL_SIZE / 2, BALL_SIZE / 2);
        sf::Vector2f deltaPos = positionB - positionA;

        float distSquared = deltaPos.x * deltaPos.x + deltaPos.y * deltaPos.y;
        float radiusSum =
            BALL_SIZE;  // Since BALL_SIZE is diameter, for radius, it's already
                        // the sum of radii for both balls
        float radiusSumSquared = radiusSum * radiusSum;

        if (distSquared <= radiusSumSquared) {
          // Balls are colliding
          float distance = sqrt(distSquared);
          sf::Vector2f collisionNormal =
              deltaPos / distance;  // Normalize vector

          // Separate the balls to prevent sticking. Move each ball away from
          // the collision point by half the overlap
          float overlap = (radiusSum - distance) / 2.0f;
          ballA.move(-collisionNormal * overlap);
          ballB.move(collisionNormal * overlap);

          // Simple elastic collision response for equal masses
          sf::Vector2f velocityA = ballA.getVelocity();
          sf::Vector2f velocityB = ballB.getVelocity();

          sf::Vector2f velocityDelta = velocityA - velocityB;
          float dotProduct = velocityDelta.x * collisionNormal.x +
                             velocityDelta.y * collisionNormal.y;

          // Apply the collision impulse if the balls are moving towards each
          // other
          if (dotProduct > 0) {
            float coefficientOfRestitution = 1.0f;  // Perfectly elastic collision
            float impulseStrength = 2.0f * dotProduct / (2.0f);  // Since both masses are considered equal and 1
            sf::Vector2f impulse = impulseStrength * collisionNormal;

            ballA.setVelocity(velocityA - impulse);
            ballB.setVelocity(velocityB + impulse);
          }
        }
      }
    }
}
void Ball::increaseBallVelocity() {
    velocity.x *= 1.5;
    velocity.y *= 1.5;
}

void Ball::decreaseBallVelocity() {
    velocity.x *= 2.f / 3;
    velocity.y *= 2.f / 3;
}