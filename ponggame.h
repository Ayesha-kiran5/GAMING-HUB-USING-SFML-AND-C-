//ayeshakiran_seb_i252108
#pragma once
#include "Leaderboard.h"

class Pong {
private:
    sf::RenderWindow* window;
    sf::Font* font;

    sf::RectangleShape ball;
    float ballX, ballY;
    float ballSpeedX, ballSpeedY;

    sf::RectangleShape paddle1;
    sf::RectangleShape paddle2;
    float p1Y, p2Y;
    float paddleSpeed;

    int score1, score2;
    int winScore;

    bool gameOver;
    bool started;
    int winner;

    // Turn based
    int currentPlayer;
    int totalScore1, totalScore2;
    char name1[50];
    char name2[50];
    bool p1Done;

    sf::RectangleShape topBar;
    sf::RectangleShape centerLine;
    sf::RectangleShape restartBtn;
    sf::RectangleShape backBtn;
    sf::RectangleShape lbBtn;

    sf::Text titleTxt;
    sf::Text scoreTxt1;
    sf::Text scoreTxt2;
    sf::Text statusTxt;
    sf::Text restartTxt;
    sf::Text backTxt;
    sf::Text startTxt;
    sf::Text p1LabelTxt;
    sf::Text p2LabelTxt;
    sf::Text lbTxt;
    sf::Text turnTxt;

    void reset();
    void update(float dt);
    void draw();

public:
    Pong(sf::RenderWindow* w, sf::Font* f);
    ~Pong();
    int run(Leaderboard* lb);
};