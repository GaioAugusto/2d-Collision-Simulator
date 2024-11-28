// #include <SFML/Graphics.hpp>
// #include "Ball.h"
// #include "Button.h"
// #define NUM_OF_BALLS 4

// int main() {
//     std::srand(std::time(0));  // Seed the random number generator

//     constexpr int WINDOW_WIDTH = 800;
//     constexpr int WINDOW_HEIGHT = 600;
//     sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_HEIGHT), "2D Collision Simulator");

//     std::vector<Ball> balls;

//     // Load font
//     sf::Font font;
//     if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
//         // Error handling
//         return -1;
//     }

//     // Create buttons with labels
//     Button buttonIncreaseV(25, 25, sf::Color::Red, "Increase Velocity", font);
//     Button buttonDecreaseV(200, 25, sf::Color::Blue, "Decrease Velocity", font);
//     Button buttonIncreaseNumOfBalls(375, 25, sf::Color::Yellow, "Add Ball", font);
//     Button buttonDecreaseNumOfBalls(550, 25, sf::Color::Green, "Remove Ball", font);

//     // Initialize balls
//     for (int counter = 0; counter < NUM_OF_BALLS; counter++) {
//         Ball newBall(BALL_SIZE);
//         newBall.setRandomPosition();
//         balls.push_back(newBall);
//     }

//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed)
//                 window.close();

//             // Handle button clicks
//             if (event.type == sf::Event::MouseButtonPressed) {
//                 if (event.mouseButton.button == sf::Mouse::Left) {
//                     if (buttonIncreaseV.isMouseOver(window)) {
//                         for (auto& ball : balls) {
//                             ball.increaseBallVelocity();
//                         }
//                     } else if (buttonDecreaseV.isMouseOver(window)) {
//                         for (auto& ball : balls) {
//                             ball.decreaseBallVelocity();
//                         }
//                     } else if (buttonIncreaseNumOfBalls.isMouseOver(window)) {
//                         Ball newBall(BALL_SIZE);
//                         newBall.setRandomPosition();
//                         if (!balls.empty())
//                             newBall.setVelocity(balls[0].getVelocity());
//                         balls.push_back(newBall);
//                     } else if (buttonDecreaseNumOfBalls.isMouseOver(window)) {
//                         if (!balls.empty())
//                             balls.pop_back();
//                     }
//                 }
//             }
//         }

//         // Update and draw balls
//         window.clear(sf::Color::Black);
//         for (int counter = 0; counter < balls.size(); counter++) {
//             balls[counter].update(window);
//             balls[counter].checkCollisionWithOtherBalls(counter, balls);
//             window.draw(balls[counter]);
//         }

//         // Draw buttons
//         buttonIncreaseV.draw(window);
//         buttonDecreaseV.draw(window);
//         buttonIncreaseNumOfBalls.draw(window);
//         buttonDecreaseNumOfBalls.draw(window);

//         window.display();
//     }

//     return 0;
// }

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Button.h"
#define NUM_OF_BALLS 4

enum class GameState {
    MENU,
    RUNNING
};


int main() {
    std::srand(std::time(0));  // Seed the random number generator

    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "2D Collision Simulator");

    std::vector<Ball> balls;

    // Load font
    sf::Font font;
    if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        // Error handling
        return -1;
    }

    // Game state
    GameState gameState = GameState::MENU;

    // Create menu start button
    Button startButton(WINDOW_WIDTH / 2 - 75, WINDOW_HEIGHT / 2 - 25, 150, 50,
                       sf::Color::Blue, "Start", font);

    // Create buttons with labels for simulation
    Button buttonIncreaseV(25, 25, 150, 50, sf::Color::Red, "Increase Velocity", font);
    Button buttonDecreaseV(200, 25, 150, 50, sf::Color::Blue, "Decrease Velocity", font);
    Button buttonIncreaseNumOfBalls(375, 25, 150, 50, sf::Color::Yellow, "Add Ball", font);
    Button buttonDecreaseNumOfBalls(550, 25, 150, 50, sf::Color::Green, "Remove Ball", font);

    // Initialize balls
    for (int counter = 0; counter < NUM_OF_BALLS; counter++) {
        Ball newBall(BALL_SIZE);
        newBall.setRandomPosition();
        balls.push_back(newBall);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (gameState == GameState::MENU) {
                // Handle menu interactions
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (startButton.isMouseOver(window)) {
                            gameState = GameState::RUNNING;
                        }
                    }
                }
            } else if (gameState == GameState::RUNNING) {
                // Handle simulation interactions
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (buttonIncreaseV.isMouseOver(window)) {
                            for (auto& ball : balls) {
                                ball.increaseBallVelocity();
                            }
                        } else if (buttonDecreaseV.isMouseOver(window)) {
                            for (auto& ball : balls) {
                                ball.decreaseBallVelocity();
                            }
                        } else if (buttonIncreaseNumOfBalls.isMouseOver(window)) {
                            Ball newBall(BALL_SIZE);
                            newBall.setRandomPosition();
                            if (!balls.empty())
                                newBall.setVelocity(balls[0].getVelocity());
                            balls.push_back(newBall);
                        } else if (buttonDecreaseNumOfBalls.isMouseOver(window)) {
                            if (!balls.empty())
                                balls.pop_back();
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        if (gameState == GameState::MENU) {
            // Draw menu
            startButton.draw(window);
        } else if (gameState == GameState::RUNNING) {
            // Update and draw balls
            for (int counter = 0; counter < balls.size(); counter++) {
                balls[counter].update(window);
                balls[counter].checkCollisionWithOtherBalls(counter, balls);
                window.draw(balls[counter]);
            }

            // Draw buttons
            buttonIncreaseV.draw(window);
            buttonDecreaseV.draw(window);
            buttonIncreaseNumOfBalls.draw(window);
            buttonDecreaseNumOfBalls.draw(window);
        }

        window.display();
    }

    return 0;
}
