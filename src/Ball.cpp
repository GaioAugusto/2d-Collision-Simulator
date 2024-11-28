#include "Ball.h"
#include <cmath>

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

void Ball::setVelocity(sf::Vector2f vel) { velocity = vel; }

sf::Vector2f Ball::getVelocity() { return velocity; }

void Ball::update(const sf::RenderWindow& window) {
    this->move(velocity);

    sf::Vector2f pos = this->getPosition();
    float radius = this->getRadius();

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
            BALL_SIZE;
        float radiusSumSquared = radiusSum * radiusSum;

        if (distSquared <= radiusSumSquared) {
          // Balls are colliding
          float distance = sqrt(distSquared);
          sf::Vector2f collisionNormal =
              deltaPos / distance;  // Normalize vector

          float overlap = (radiusSum - distance) / 2.0f;
          ballA.move(-collisionNormal * overlap);
          ballB.move(collisionNormal * overlap);

          sf::Vector2f velocityA = ballA.getVelocity();
          sf::Vector2f velocityB = ballB.getVelocity();

          sf::Vector2f velocityDelta = velocityA - velocityB;
          float dotProduct = velocityDelta.x * collisionNormal.x +
                             velocityDelta.y * collisionNormal.y;

          if (dotProduct > 0) {
            float coefficientOfRestitution = 1.0f;
            float impulseStrength = 2.0f * dotProduct / (2.0f);
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