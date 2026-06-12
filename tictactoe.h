//ayeshakiran_seb_i252108
#pragma once
#include "Leaderboard.h"

class TicTacToe {
private:
    sf::RenderWindow* window;
    sf::Font* font;

    int board[3][3];
    int currentPlayer;
    bool gameOver;
    int winner;
    bool showWinLine;
    float pulseTime;

    sf::RectangleShape cells[3][3];
    sf::RectangleShape gridLines[4];
    sf::RectangleShape topBar;
    sf::RectangleShape restartBtn;
    sf::RectangleShape backBtn;
    sf::RectangleShape winLine;

    sf::Text titleTxt;
    sf::Text statusTxt;
    sf::Text restartTxt;
    sf::Text backTxt;

    void reset();
    void checkWinner();
    bool isFull();
    int  checkWin();
    void findWinLine();
    void draw();
    void handleClick(int x, int y);

public:
    TicTacToe(sf::RenderWindow* w, sf::Font* f);
    ~TicTacToe();
    int run(Leaderboard* lb);
}; 
