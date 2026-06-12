//ayeshakiran_seb_i252108
#pragma once
#include "Leaderboard.h"

// Grid is 4 columns x 3 rows = 12 cards total = 6 pairs
const int ROWS = 3;
const int COLS = 4;
const int TOTAL_CARDS = ROWS * COLS;  // 12

class MemoryMatch {
private:
    sf::RenderWindow* window;  // pointer to game window
    sf::Font* font;            // pointer to font

    // ── Card Data ──
    int  cards[TOTAL_CARDS];   // value of each card (1 to 6)
    bool flipped[TOTAL_CARDS]; // true = card is face up
    bool matched[TOTAL_CARDS]; // true = card is permanently matched

    // ── Flip tracking ──
    int firstCard;    // index of first clicked card
    int secondCard;   // index of second clicked card
    int flippedCount; // how many cards are currently flipped (0, 1, or 2)

    // ── Timer to flip unmatched cards back ──
    float waitTimer;  // counts up every frame
    bool  waiting;    // true = waiting to flip cards back

    // ── Turn based multiplayer ──
    int  currentPlayer;  // 1 or 2
    int  score1, score2; // how many pairs each player matched
    char name1[50];
    char name2[50];
    bool gameOver;

    // ── Card positions on screen ──
    float cardX[TOTAL_CARDS];  // x position of each card
    float cardY[TOTAL_CARDS];  // y position of each card
    float cardW;               // card width
    float cardH;               // card height

    // ── One color per card value (1 to 6) ──
    sf::Color cardColors[7];

    // ── UI shapes ──
    sf::RectangleShape topBar;
    sf::RectangleShape restartBtn;
    sf::RectangleShape backBtn;
    sf::RectangleShape lbBtn;

    // ── UI texts ──
    sf::Text titleTxt;
    sf::Text statusTxt;
    sf::Text score1Txt;
    sf::Text score2Txt;
    sf::Text turnTxt;
    sf::Text restartTxt;
    sf::Text backTxt;
    sf::Text lbTxt;

    // ── Private methods ──
    void reset();              // reset everything for new game
    void shuffle();            // randomly shuffle cards
    void drawCards();          // draw all 12 cards
    void handleClick(int x, int y); // handle mouse click on card
    bool allMatched();         // returns true if all pairs found
    void showLeaderboard(Leaderboard* lb);
public:
    MemoryMatch(sf::RenderWindow* w, sf::Font* f);
    ~MemoryMatch();
    int run(Leaderboard* lb);
};