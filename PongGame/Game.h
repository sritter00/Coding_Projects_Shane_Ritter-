#pragma once
#include <SFML/Graphics.hpp>

class Game {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text player1Text;
    sf::Text player2Text;
    
    sf::RectangleShape paddle1;
    sf::RectangleShape paddle2;
    sf::CircleShape ball;
    std::vector<std::pair<int, int>> scoreHistory;
    sf::Vector2f ballVelocity;

    int player1Score;
    int player2Score;

    bool saveScores;
    std::string saveFileName;
    /// @brief resets the game
    void resetGame();
    /// @brief handles the input of the players
    void handleInput();
    /// @brief updates the window to display what is going on
    /// @param DELTA_TIME the time sense the window was opened
    /// @param PLAYERS the number of players
    void update(const sf::Time DELTA_TIME, const int PLAYERS);
    /// @brief draws the paddles and balls
    void draw();

public:
    /// @brief sets up the window using variables inside game.cpp
    Game();
    /// @brief runs the game pong
    /// @param PLAYERS the number of players for the game pong
    void run(const int PLAYERS);
};
