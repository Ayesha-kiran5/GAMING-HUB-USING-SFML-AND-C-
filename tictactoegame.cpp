//ayeshakiran_seb_i252108
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "tictactoe.h"
TicTacToe::TicTacToe(sf::RenderWindow* w, sf::Font* f) {
    window = w;
    font = f;

    topBar.setSize(sf::Vector2f(900, 60));
    topBar.setPosition(0, 0);
    topBar.setFillColor(sf::Color(20, 20, 50));

    titleTxt.setFont(*font);
    titleTxt.setString("TIC TAC TOE");
    titleTxt.setCharacterSize(26);
    titleTxt.setFillColor(sf::Color(220, 220, 255));
    titleTxt.setPosition(340, 15);

    int startX = 225, startY = 80, cellSize = 130;

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++) {
            cells[r][c].setSize(sf::Vector2f(cellSize - 2, cellSize - 2));
            cells[r][c].setPosition(startX + c * cellSize + 1, startY + r * cellSize + 1);
            cells[r][c].setFillColor(sf::Color(25, 25, 60));
        }

    gridLines[0].setSize(sf::Vector2f(4, 390));
    gridLines[0].setPosition(startX + cellSize, startY);
    gridLines[1].setSize(sf::Vector2f(4, 390));
    gridLines[1].setPosition(startX + cellSize * 2, startY);
    gridLines[2].setSize(sf::Vector2f(390, 4));
    gridLines[2].setPosition(startX, startY + cellSize);
    gridLines[3].setSize(sf::Vector2f(390, 4));
    gridLines[3].setPosition(startX, startY + cellSize * 2);

    for (int i = 0; i < 4; i++)
        gridLines[i].setFillColor(sf::Color(180, 180, 220));

    statusTxt.setFont(*font);
    statusTxt.setCharacterSize(20);
    statusTxt.setPosition(280, 500);

    restartBtn.setSize(sf::Vector2f(160, 44));
    restartBtn.setPosition(230, 535);
    restartBtn.setFillColor(sf::Color(50, 50, 120));
    restartBtn.setOutlineThickness(2);
    restartBtn.setOutlineColor(sf::Color(150, 150, 255));

    restartTxt.setFont(*font);
    restartTxt.setString("RESTART");
    restartTxt.setCharacterSize(16);
    restartTxt.setFillColor(sf::Color::White);
    restartTxt.setPosition(261, 546);

    backBtn.setSize(sf::Vector2f(160, 44));
    backBtn.setPosition(510, 535);
    backBtn.setFillColor(sf::Color(80, 30, 30));
    backBtn.setOutlineThickness(2);
    backBtn.setOutlineColor(sf::Color(255, 100, 100));

    backTxt.setFont(*font);
    backTxt.setString("MAIN MENU");
    backTxt.setCharacterSize(16);
    backTxt.setFillColor(sf::Color::White);
    backTxt.setPosition(530, 546);

    reset();
}

TicTacToe::~TicTacToe() {}

void TicTacToe::reset() {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[r][c] = 0;
    currentPlayer = 1;
    gameOver = false;
    winner = 0;
    showWinLine = false;
    pulseTime = 0;
}

bool TicTacToe::isFull() {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board[r][c] == 0) return false;
    return true;
}

int TicTacToe::checkWin() {
    for (int r = 0; r < 3; r++)
        if (board[r][0] && board[r][0] == board[r][1] && board[r][1] == board[r][2])
            return board[r][0];
    for (int c = 0; c < 3; c++)
        if (board[0][c] && board[0][c] == board[1][c] && board[1][c] == board[2][c])
            return board[0][c];
    if (board[0][0] && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];
    if (isFull()) return 3;
    return 0;
}

void TicTacToe::checkWinner() {
    winner = checkWin();
    if (winner != 0) {
        gameOver = true;
        if (winner == 3) { 
            Beep(310, 150); 
        Beep(250, 150); }
        else { Beep(400, 100); 
        Beep(500, 100); Beep(600, 200); }
        if (winner != 3) findWinLine();
    }
}
void TicTacToe::findWinLine() {
    int startX = 225, startY = 80, cs = 130, mid = cs / 2;
    for (int r = 0; r < 3; r++) {
        if (board[r][0] && board[r][0] == board[r][1] && board[r][1] == board[r][2]) {
            winLine.setSize(sf::Vector2f(375, 6));
            winLine.setOrigin(0, 3);
            winLine.setPosition(startX + 5, startY + r * cs + mid);
            winLine.setRotation(0);
            winLine.setFillColor(sf::Color(255, 220, 50));
            showWinLine = true; return;
        }
    }
    for (int c = 0; c < 3; c++) {
        if (board[0][c] && board[0][c] == board[1][c] && board[1][c] == board[2][c]) {
            winLine.setSize(sf::Vector2f(375, 6));
            winLine.setOrigin(0, 3);
            winLine.setPosition(startX + c * cs + mid, startY + 5);
            winLine.setRotation(90);
            winLine.setFillColor(sf::Color(255, 220, 50));
            showWinLine = true; return;
        }
    }
    if (board[0][0] && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        winLine.setSize(sf::Vector2f(535, 6));
        winLine.setOrigin(0, 3);
        winLine.setPosition(startX + 5, startY + 5);
        winLine.setRotation(45);
        winLine.setFillColor(sf::Color(255, 220, 50));
        showWinLine = true; return;
    }
    if (board[0][2] && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        winLine.setSize(sf::Vector2f(535, 6));
        winLine.setOrigin(0, 3);
        winLine.setPosition(startX + 385, startY + 5);
        winLine.setRotation(135);
        winLine.setFillColor(sf::Color(255, 220, 50));
        showWinLine = true; return;
    }
}
//void showLeaderboard(Leaderboard* lb);
void TicTacToe::handleClick(int x, int y) {
    if (restartBtn.getGlobalBounds().contains(x, y)) { Beep(350, 60); reset(); return; }
    if (gameOver) return;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (cells[r][c].getGlobalBounds().contains(x, y) && board[r][c] == 0) {
                board[r][c] = currentPlayer;
                Beep(400, 80);
                checkWinner();
                if (!gameOver)
                    currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
}

void TicTacToe::draw() {
    window->clear(sf::Color(18, 18, 45));

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            window->draw(cells[r][c]);

    for (int i = 0; i < 4; i++)
        window->draw(gridLines[i]);

    int startX = 225, startY = 80, cs = 130;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board[r][c] == 0) continue;
            float cx = startX + c * cs + cs / 2;
            float cy = startY + r * cs + cs / 2;
            if (board[r][c] == 1) {
                sf::RectangleShape l1(sf::Vector2f(80, 8));
                l1.setOrigin(40, 4); l1.setPosition(cx, cy);
                l1.setRotation(45); l1.setFillColor(sf::Color(100, 180, 255));
                sf::RectangleShape l2(sf::Vector2f(80, 8));
                l2.setOrigin(40, 4); l2.setPosition(cx, cy);
                l2.setRotation(-45); l2.setFillColor(sf::Color(100, 180, 255));
                window->draw(l1); window->draw(l2);
            }
            else {
                sf::CircleShape ring(40);
                ring.setOrigin(40, 40); ring.setPosition(cx, cy);
                ring.setFillColor(sf::Color::Transparent);
                ring.setOutlineThickness(10);
                ring.setOutlineColor(sf::Color(255, 120, 120));
                window->draw(ring);
            }
        }
    }

    if (showWinLine) window->draw(winLine);
    window->draw(topBar);
    window->draw(titleTxt);

    sf::Vector2i mp = sf::Mouse::getPosition(*window);
    if (!gameOver) {
        statusTxt.setString(currentPlayer == 1 ? "PLAYER 1 TURN ( X )" : "PLAYER 2 TURN ( O )");
        statusTxt.setFillColor(currentPlayer == 1 ? sf::Color(100, 180, 255) : sf::Color(255, 120, 120));
    }
    else {
        if (winner == 3) { statusTxt.setString("ITS A DRAW!"); statusTxt.setFillColor(sf::Color(220, 200, 100)); }
        else { statusTxt.setString(winner == 1 ? "PLAYER 1 WINS! ( X )" : "PLAYER 2 WINS! ( O )"); statusTxt.setFillColor(sf::Color(100, 255, 150)); }
    }
    window->draw(statusTxt);

    restartBtn.setFillColor(restartBtn.getGlobalBounds().contains(mp.x, mp.y) ? sf::Color(80, 80, 180) : sf::Color(50, 50, 120));
    backBtn.setFillColor(backBtn.getGlobalBounds().contains(mp.x, mp.y) ? sf::Color(130, 50, 50) : sf::Color(80, 30, 30));
    window->draw(restartBtn); window->draw(restartTxt);
    window->draw(backBtn);    window->draw(backTxt);
    window->display();
}

int TicTacToe::run(Leaderboard* lb) {
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) window->close();
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape) return 0;
            if (event.type == sf::Event::MouseButtonPressed) {
                if (backBtn.getGlobalBounds().contains(
                    event.mouseButton.x, event.mouseButton.y)) {
                    // Save score if game was won
                    if (gameOver && winner != 3 && lb != nullptr) {
                        char name[50] = "Player";
                        getName(window, font, name);
                        lb->addRecord(name, "TIC TAC TOE", winner);
                    }
                    Beep(250, 80); return 0;
                }
                handleClick(event.mouseButton.x, event.mouseButton.y);
            }
        }
        draw();
    }
    return 0;
}