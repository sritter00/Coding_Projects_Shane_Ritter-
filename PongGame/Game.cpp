
#include "Game.h"
#include <iostream>
#include <fstream>

const int windowWidth = 800;
const int windowHeight = 600;
const float paddleWidth = 10.0f;
const float paddleHeight = 100.0f;
const float ballRadius = 10.0f;
const float ballSpeed = 300.0f;

Game::Game(): 
    window(sf::VideoMode(windowWidth, windowHeight), "Pong"),
      paddle1(sf::Vector2f(paddleWidth, paddleHeight)),
      paddle2(sf::Vector2f(paddleWidth, paddleHeight)),
      ball(ballRadius),
      ballVelocity(200.0f, 100.0f),
      player1Score(0),
      player2Score(0),
      saveScores(false) {
    window.setFramerateLimit(60);

    // Load font
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font file\n";
        std::exit(1);
    }

    // Setup player texts
    player1Text.setFont(font);
    player1Text.setCharacterSize(24);
    player1Text.setPosition(20, 20);

    player2Text.setFont(font);
    player2Text.setCharacterSize(24);
    player2Text.setPosition(windowWidth - 200, 20);

    // Initialize game
    resetGame();
}

void Game::resetGame() {
    

    
    paddle1.setPosition(20, windowHeight / 2 - paddleHeight / 2);
    paddle2.setPosition(windowWidth - 20 - paddleWidth, windowHeight / 2 - paddleHeight / 2);
    ball.setPosition(windowWidth / 2 - ballRadius, windowHeight / 2 - ballRadius);
    ballVelocity = sf::Vector2f(200.0f, 100.0f);
    // Set a fixed initial velocity for the ball
    
   
    
}

void Game::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    // Player 1 controls
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && paddle1.getPosition().y > 0) {
        paddle1.move(0, -5);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && paddle1.getPosition().y + paddleHeight < windowHeight) {
        paddle1.move(0, 5);
    }

    // Player 2 controls in multiplayer mode
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle2.getPosition().y > 0) {
        paddle2.move(0, -5);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddle2.getPosition().y + paddleHeight < windowHeight) {
        paddle2.move(0, 5);
    }
}

void Game::update(const sf::Time DELTA_TIME, int PLAYERS) {
    static sf::Clock collisionClock;

    // Update ball position
    ball.move(ballVelocity * DELTA_TIME.asSeconds());

    // Ball and wall collisions
    if (ball.getPosition().y <= 0 || ball.getPosition().y + 2 * ballRadius >= windowHeight) {
        ballVelocity.y = -ballVelocity.y;
    }

    // Player paddle collisions (with a 0.5-second delay)
    if (collisionClock.getElapsedTime().asSeconds() >= 0.5f) {
        sf::FloatRect paddle1Bounds = paddle1.getGlobalBounds();
        sf::FloatRect paddle2Bounds = paddle2.getGlobalBounds();
        sf::FloatRect ballBounds = ball.getGlobalBounds();

        if (ballBounds.intersects(paddle1Bounds) || ballBounds.intersects(paddle2Bounds)) {
            ballVelocity.x = -ballVelocity.x;

            // Increase ball speed on collision with a paddle
            float speedIncreaseFactor = 1.1f;
            ballVelocity *= speedIncreaseFactor;

            // Restart the collision clock
            collisionClock.restart();
        }
    }

    // Score update
    if (ball.getPosition().x <= 0) {
        player2Score++;
        scoreHistory.push_back(std::make_pair(player1Score, player2Score));
        resetGame();
        
    }
    else if (ball.getPosition().x + 2 * ballRadius >= windowWidth) {
        player1Score++;
        scoreHistory.push_back(std::make_pair(player1Score, player2Score));
        resetGame();
    }

    // Multiplayer AI
    if (PLAYERS == 1) {
        float targetY = ball.getPosition().y - paddle2.getSize().y / 2;
        if (paddle2.getPosition().y < targetY && paddle2.getPosition().y + paddleHeight < windowHeight) {
            paddle2.move(0, 3);
        }
        else if (paddle2.getPosition().y > targetY && paddle2.getPosition().y > 0) {
            paddle2.move(0, -3);
        }
    }
}

void Game::draw() {
    window.clear();

    // Draw paddles and ball
    window.draw(paddle1);
    window.draw(paddle2);
    window.draw(ball);

    // Draw scores
    player1Text.setString("Player 1: " + std::to_string(player1Score));
    player2Text.setString("Player 2: " + std::to_string(player2Score));
    window.draw(player1Text);
    window.draw(player2Text);

    window.display();
}

void Game::run(const int PLAYERS) {
    
    sf::Clock clock;
    if (PLAYERS == 2 || PLAYERS == 1){
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        handleInput();
        update(deltaTime, PLAYERS); 
        draw();
        if (player1Score >= 5 || player2Score >= 5){
            window.close();

        }
    }

 
    std::cout << "Game Over!\n";
    std::cout << "Do you want to save scores? (y/n): ";
    char saveChoice;
    std::cin >> saveChoice;


   
if (saveChoice == 'y' || saveChoice == 'Y') {
        saveScores = true;

        // Save the scores to the scoreHistory vector
        scoreHistory.push_back(std::make_pair(player1Score, player2Score));

        
        saveFileName = "scores_history";
    }

    // Existing code...

    if (saveScores) {
        std::ofstream outFile;
        outFile.open(saveFileName + ".txt");
        scoreHistory.erase(scoreHistory.end());
        if (!outFile.is_open()) {
            std::cerr << "Error opening file for writing\n";
            std::exit(1);
        }
        outFile << "Player 1 final score: " << player1Score << "\n";
        outFile << "Player 2 final score: " << player2Score << "\n";
        // Save scores from the scoreHistory vector
        for (const auto& scores : scoreHistory) {
            outFile << "Player 1: " << scores.first << " - Player 2: " << scores.second << "\n";
        }

        std::cout << "Scores saved to " << saveFileName << "\n";
       
        outFile.close();
    }
    }
    else{
        std::cout << "invalade number of players ending program";
    }
}