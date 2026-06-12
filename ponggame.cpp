//ayeshakiran_seb_i252108
#include "ponggame.h"
#include <windows.h>

Pong::Pong(sf::RenderWindow* w, sf::Font* f) {
    window = w; font = f;
    winScore = 3;

    topBar.setSize(sf::Vector2f(900, 60));
    topBar.setPosition(0, 0);
    topBar.setFillColor(sf::Color(20, 20, 20));

    centerLine.setSize(sf::Vector2f(4, 540));
    centerLine.setPosition(448, 60);
    centerLine.setFillColor(sf::Color(80, 80, 80));

    ball.setSize(sf::Vector2f(14, 14));
    ball.setFillColor(sf::Color::White);

    paddle1.setSize(sf::Vector2f(14, 80));
    paddle1.setFillColor(sf::Color(100, 180, 255));

    paddle2.setSize(sf::Vector2f(14, 80));
    paddle2.setFillColor(sf::Color(255, 120, 120));

    titleTxt.setFont(*font); titleTxt.setString("PONG");
    titleTxt.setCharacterSize(26);
    titleTxt.setFillColor(sf::Color::White);
    titleTxt.setPosition(410, 15);

    scoreTxt1.setFont(*font);
    scoreTxt1.setCharacterSize(28);
    scoreTxt1.setFillColor(sf::Color(100, 180, 255));
    scoreTxt1.setPosition(180, 12);

    scoreTxt2.setFont(*font);
    scoreTxt2.setCharacterSize(28);
    scoreTxt2.setFillColor(sf::Color(255, 120, 120));
    scoreTxt2.setPosition(660, 12);

    p1LabelTxt.setFont(*font); p1LabelTxt.setString("P1: W/S");
    p1LabelTxt.setCharacterSize(14);
    p1LabelTxt.setFillColor(sf::Color(100, 180, 255, 180));
    p1LabelTxt.setPosition(30, 20);

    p2LabelTxt.setFont(*font); p2LabelTxt.setString("P2: UP/DOWN");
    p2LabelTxt.setCharacterSize(14);
    p2LabelTxt.setFillColor(sf::Color(255, 120, 120, 180));
    p2LabelTxt.setPosition(720, 20);

    statusTxt.setFont(*font);
    statusTxt.setCharacterSize(26);
    statusTxt.setPosition(250, 280);

    startTxt.setFont(*font);
    startTxt.setString("PRESS SPACE TO START");
    startTxt.setCharacterSize(20);
    startTxt.setFillColor(sf::Color(200, 200, 200));
    startTxt.setPosition(260, 320);

    restartBtn.setSize(sf::Vector2f(160, 44));
    restartBtn.setPosition(230, 370);
    restartBtn.setFillColor(sf::Color(40, 40, 100));
    restartBtn.setOutlineThickness(2);
    restartBtn.setOutlineColor(sf::Color(150, 150, 255));

    restartTxt.setFont(*font); restartTxt.setString("RESTART");
    restartTxt.setCharacterSize(16);
    restartTxt.setFillColor(sf::Color::White);
    restartTxt.setPosition(261, 381);

    backBtn.setSize(sf::Vector2f(160, 44));
    backBtn.setPosition(510, 370);
    backBtn.setFillColor(sf::Color(80, 30, 30));
    backBtn.setOutlineThickness(2);
    backBtn.setOutlineColor(sf::Color(255, 100, 100));

    backTxt.setFont(*font); backTxt.setString("MAIN MENU");
    backTxt.setCharacterSize(16);
    backTxt.setFillColor(sf::Color::White);
    backTxt.setPosition(530, 381);

    reset();
}

Pong::~Pong() {}
void Pong::update(float dt) {
    if (gameOver || !started) return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && p1Y > 60)  p1Y -= paddleSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && p1Y < 520) p1Y += paddleSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && p2Y > 60)  p2Y -= paddleSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && p2Y < 520) p2Y += paddleSpeed * dt;

    paddle1.setPosition(30, p1Y);
    paddle2.setPosition(856, p2Y);

    ballX += ballSpeedX * dt;
    ballY += ballSpeedY * dt;

    if (ballY <= 60) { ballY = 60;  ballSpeedY = -ballSpeedY; Beep(300, 30); }
    if (ballY >= 586) { ballY = 586; ballSpeedY = -ballSpeedY; Beep(300, 30); }

    if (ballX <= 44 && ballX >= 30 && ballY + 14 >= p1Y && ballY <= p1Y + 80) {
        ballX = 44; ballSpeedX = -ballSpeedX;
        float hit = (ballY + 7) - (p1Y + 40);
        ballSpeedY = hit * 6.0f;
        Beep(400, 40);
    }
    if (ballX + 14 >= 856 && ballX + 14 <= 870 && ballY + 14 >= p2Y && ballY <= p2Y + 80) {
        ballX = 842; ballSpeedX = -ballSpeedX;
        float hit = (ballY + 7) - (p2Y + 40);
        ballSpeedY = hit * 6.0f;
        Beep(400, 40);
    }

    if (ballX < 0) {
        score2++; Beep(200, 200);
        if (score2 >= winScore) {
            gameOver = true; winner = 2;
            Beep(400, 100); Beep(500, 100); Beep(600, 300);
        }
        else { ballX = 443; ballY = 323; ballSpeedX = 280.0f; ballSpeedY = -220.0f; started = false; }
    }
    if (ballX > 900) {
        score1++; Beep(200, 200);
        if (score1 >= winScore) {
            gameOver = true; winner = 1;
            Beep(400, 100); Beep(500, 100); Beep(600, 300);
        }
        else { ballX = 443; ballY = 323; ballSpeedX = -280.0f; ballSpeedY = 220.0f; started = false; }
    }

    ball.setPosition(ballX, ballY);
}

//void Pong::showLeaderboard(Leaderboard* lb) ;
void Pong::reset() {
    ballX = 443; ballY = 323;
    ballSpeedX = 280.0f; ballSpeedY = 220.0f;
    p1Y = 300; p2Y = 300;
    paddleSpeed = 380.0f;
    score1 = 0; score2 = 0;
    gameOver = false; started = false; winner = 0;
    paddle1.setPosition(30, p1Y);
    paddle2.setPosition(856, p2Y);
    ball.setPosition(ballX, ballY);
}

//
//    if (ballY <= 60) { ballY = 60;  ballSpeedY = -ballSpeedY; Beep(300, 30); }
//    if (ballY >= 586) { ballY = 586; ballSpeedY = -ballSpeedY; Beep(300, 30); }
//
//    if (ballX <= 44 && ballX >= 30 && ballY + 14 >= p1Y && ballY <= p1Y + 80) {
//        ballX = 44; ballSpeedX = -ballSpeedX;
//        float hit = (ballY + 7) - (p1Y + 40);
//        ballSpeedY = hit * 6.0f;
//        Beep(400, 40);
//   (ballY + 7) - (p2Y + 40);
//        ballSpeedY = hit * 6.0f;
//        Beep(400, 40);+++++++++++++++
//}

void Pong::draw() {
    window->clear(sf::Color(0, 10, 14));
    window->draw(centerLine);
    window->draw(paddle1); window->draw(paddle2);
    window->draw(ball);
    window->draw(topBar);
    window->draw(titleTxt);
    window->draw(p1LabelTxt);
    window->draw(p2LabelTxt);

    char numBuf[20];
    char scoreBuf[20];
    intToStr(score1, numBuf);
    strCombine("P1: ", numBuf, scoreBuf);
    scoreTxt1.setString(scoreBuf);

    intToStr(score2, numBuf);
    strCombine("P2: ", numBuf, scoreBuf);
    scoreTxt2.setString(scoreBuf);

    window->draw(scoreTxt1);
    window->draw(scoreTxt2);

    if (!started && !gameOver) window->draw(startTxt);

    if (gameOver) {
        statusTxt.setString(winner == 1 ? "PLAYER 1 WINS!" : "PLAYER 2 WINS!");
        statusTxt.setFillColor(winner == 1 ? sf::Color(100, 180, 255) : sf::Color(255, 120, 120));
        window->draw(statusTxt);

        sf::Vector2i mp = sf::Mouse::getPosition(*window);
        restartBtn.setFillColor(restartBtn.getGlobalBounds().contains(mp.x, mp.y) ? sf::Color(70, 70, 160) : sf::Color(40, 40, 100));
        backBtn.setFillColor(backBtn.getGlobalBounds().contains(mp.x, mp.y) ? sf::Color(130, 50, 50) : sf::Color(80, 30, 30));
        window->draw(restartBtn); window->draw(restartTxt);
        window->draw(backBtn);    window->draw(backTxt);
    }
    window->display();
}

int Pong::run(Leaderboard* lb) {
    sf::Clock clock;
    while (window->isOpen()) {
        float dt = clock.restart().asSeconds();
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
 window->close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space && !gameOver)
                    started = true;
                if (event.key.code == sf::Keyboard::Escape) return 0;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (restartBtn.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y)) {
                    Beep(350, 60); reset();
                }
                if (backBtn.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y)) {
                    if (gameOver && lb != nullptr) {
                        char name[50] = "Player";
                        getName(window, font, name);
                        int winnerScore = (winner == 1) ? score1 : score2;
                        lb->addRecord(name, "PONG", winnerScore);
                    }
                    Beep(250, 80); 
                    return 0;
                }
            }
        }
        update(dt);
        draw();
    }
    return 0;
}