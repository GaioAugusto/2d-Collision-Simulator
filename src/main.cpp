#include "Ball.h"
#include "Button.h"
#define NUM_OF_BALLS 4


int main() {
    std::srand(std::time(0));  // Seed the random number generator

    sf::RenderWindow window(sf::VideoMode(HEIGHT, WIDTH), "SFML Application");  // Window for the program
    Ball ball1(50);             // Create a Ball object with diameter 50
    ball1.setRandomPosition();  // Set a random position within bounds

    std::vector<Ball> balls;  // Declare the vector of balls

    Button buttonIncreaseV(25, 25, sf::Color::Red);
    Button buttonDecreaseV(75, 25, sf::Color::Blue);
    Button buttonIncreaseNumOfBalls(WIDTH - 125, 25, sf::Color::Yellow);
    Button buttonDecreaseNumOfBalls(WIDTH - 75, 25, sf::Color::Green);

  // Loop to populate the vector with the Ball Objects
    for (int counter = 0; counter < NUM_OF_BALLS; counter++) {
        Ball newBall(BALL_SIZE);
        newBall.setRandomPosition();
        balls.push_back(newBall);
    }


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        // Deal with button
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                auto mousePos = sf::Mouse::getPosition(window);
                if (buttonIncreaseV.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                // Button was clicked, perform the action
                    for (int counter = 0; counter < NUM_OF_BALLS; counter++) {
                        balls[counter].increaseBallVelocity();
                    }
                }
                else if (buttonDecreaseV.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    for (int counter = 0; counter < NUM_OF_BALLS; counter++) {
                        balls[counter].decreaseBallVelocity();
                    }
                }
                else if (buttonIncreaseNumOfBalls.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    Ball newBall(BALL_SIZE);
                    newBall.setRandomPosition();
                    newBall.setVelocity(balls[0].getVelocity());
                    balls.push_back(newBall);
                }
                else if (buttonDecreaseNumOfBalls.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    balls.pop_back();
                }
            }
        }
    }
    // Deal with the balls
    window.clear();
    for (int counter = 0; counter < balls.size(); counter++) {
        balls[counter].update(window);
        balls[counter].checkCollisionWithOtherBalls(counter, balls);
        window.draw(balls[counter]);
    }
    window.draw(buttonIncreaseV);
    window.draw(buttonDecreaseV);
    window.draw(buttonIncreaseNumOfBalls);
    window.draw(buttonDecreaseNumOfBalls);
    window.display();
  }

  return 0;
}