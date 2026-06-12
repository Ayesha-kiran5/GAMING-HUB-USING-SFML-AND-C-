//ayeshakiran_seb_i252108
#include <SFML/Graphics.hpp>
#include "memorycard.h"
#include <windows.h>

MemoryMatch::MemoryMatch(sf::RenderWindow* w, sf::Font* f) {
    window = w;
    font = f;

    cardW = 140.0f;
    cardH = 140.0f;

    float startX = 90.0f;
    float startY = 80.0f;
    float padX = 20.0f;
    float padY = 20.0f;

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            int idx = r * COLS + c;
            cardX[idx] = startX + c * (cardW + padX);
            cardY[idx] = startY + r * (cardH + padY);
        }
    }

    cardColors[1] = sf::Color(180, 60, 60);
    cardColors[2] = sf::Color(60, 140, 200);
    cardColors[3] = sf::Color(60, 180, 80);
    cardColors[4] = sf::Color(200, 160, 40);
    cardColors[5] = sf::Color(160, 60, 200);
    cardColors[6] = sf::Color(200, 100, 40);

    // ── Top bar ──
    topBar.setSize(sf::Vector2f(900, 60));
    topBar.setPosition(0, 0);
    topBar.setFillColor(sf::Color(20, 10, 40));

    // ── Title — centered ──
    titleTxt.setFont(*font);
    titleTxt.setString("MEMORY MATCH");
    titleTxt.setCharacterSize(24);
    titleTxt.setFillColor(sf::Color(200, 150, 255));
    titleTxt.setPosition(330, 15);  // centered in top bar

    // ── Player 1 score — top left ──
    score1Txt.setFont(*font);
    score1Txt.setCharacterSize(16);
    score1Txt.setFillColor(sf::Color(150, 100, 255));
    score1Txt.setPosition(20, 22);  // top left

    // ── Player 2 score — top right ──
    score2Txt.setFont(*font);
    score2Txt.setCharacterSize(16);
    score2Txt.setFillColor(sf::Color(255, 120, 120));
    score2Txt.setPosition(730, 22);  // top right

    // ── Turn indicator — center of top bar ──
    turnTxt.setFont(*font);
    turnTxt.setCharacterSize(15);
    turnTxt.setFillColor(sf::Color(220, 180, 255));
    turnTxt.setPosition(330, 42);  

    // ── Restart button — BOTTOM CENTER ──
    restartBtn.setSize(sf::Vector2f(160, 36));
    restartBtn.setPosition(370, 557);
    restartBtn.setFillColor(sf::Color(40, 20, 80));
    restartBtn.setOutlineThickness(2);
    restartBtn.setOutlineColor(sf::Color(150, 100, 255));

    restartTxt.setFont(*font);
    restartTxt.setString("RESTART");
    restartTxt.setCharacterSize(15);
    restartTxt.setFillColor(sf::Color::White);
    restartTxt.setPosition(411, 563);

    // ── Back button — BOTTOM RIGHT ──
    backBtn.setSize(sf::Vector2f(160, 36));
    backBtn.setPosition(730, 557);
    backBtn.setFillColor(sf::Color(80, 10, 20));
    backBtn.setOutlineThickness(2);
    backBtn.setOutlineColor(sf::Color(255, 60, 80));

    backTxt.setFont(*font);
    backTxt.setString("MAIN MENU");
    backTxt.setCharacterSize(15);
    backTxt.setFillColor(sf::Color::White);
    backTxt.setPosition(744, 563);

    myCopy("Player 1", name1);
    myCopy("Player 2", name2);
    currentPlayer = 1;
    score1 = 0; score2 = 0;
    gameOver = false;

    reset();
}

MemoryMatch::~MemoryMatch() {}

void MemoryMatch::shuffle() {
    for (int i = 0; i < TOTAL_CARDS; i++)
        cards[i] = (i % 6) + 1;
    for (int i = TOTAL_CARDS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}

void MemoryMatch::reset() {
    shuffle();
    for (int i = 0; i < TOTAL_CARDS; i++) {
        flipped[i] = false;
        matched[i] = false;
    }
    firstCard = -1;
    secondCard = -1;
    flippedCount = 0;
    waitTimer = 0;
    waiting = false;
    gameOver = false;
}

bool MemoryMatch::allMatched() {
    for (int i = 0; i < TOTAL_CARDS; i++)
        if (!matched[i]) return false;
    return true;
}

void MemoryMatch::handleClick(int x, int y) {
    if (waiting || gameOver) return;

    for (int i = 0; i < TOTAL_CARDS; i++) {
        if (matched[i] || flipped[i]) continue;

        sf::FloatRect cardRect(cardX[i], cardY[i], cardW, cardH);
        if (cardRect.contains(x, y)) {
            flipped[i] = true;
            Beep(500, 50);

            if (flippedCount == 0) {
                firstCard = i;
                flippedCount = 1;
            }
            else if (flippedCount == 1) {
                secondCard = i;
                flippedCount = 2;

                if (cards[firstCard] == cards[secondCard]) {
                    matched[firstCard] = true;
                    matched[secondCard] = true;
                    flippedCount = 0;
                    firstCard = -1;
                    secondCard = -1;
                    Beep(700, 100);

                    if (currentPlayer == 1) score1++;
                    else                    score2++;

                    if (allMatched()) {
                        gameOver = true;
                        Beep(400, 100); Beep(500, 100); Beep(600, 200);
                    }
                }
                else {
                    waiting = true;
                    waitTimer = 0;
                    Beep(200, 100);
                    currentPlayer = (currentPlayer == 1) ? 2 : 1;
                }
            }
            break;
        }
    }
}

void MemoryMatch::drawCards() {
    for (int i = 0; i < TOTAL_CARDS; i++) {
        sf::RectangleShape card(sf::Vector2f(cardW, cardH));
        card.setPosition(cardX[i], cardY[i]);
        card.setOutlineThickness(3);

        if (matched[i]) {
            card.setFillColor(sf::Color(
                cardColors[cards[i]].r / 2,
                cardColors[cards[i]].g / 2,
                cardColors[cards[i]].b / 2));
            card.setOutlineColor(sf::Color(80, 60, 120));
            window->draw(card);

        }
        else if (flipped[i]) {
            card.setFillColor(cardColors[cards[i]]);
            card.setOutlineColor(sf::Color(255, 220, 255));
            window->draw(card);

            sf::Text numTxt;
            numTxt.setFont(*font);
            char buf[4];
            intToStr(cards[i], buf);
            numTxt.setString(buf);
            numTxt.setCharacterSize(52);
            numTxt.setFillColor(sf::Color::White);
            numTxt.setPosition(cardX[i] + 48, cardY[i] + 38);
            window->draw(numTxt);

        }
        else {
            card.setFillColor(sf::Color(40, 20, 80));
            card.setOutlineColor(sf::Color(120, 80, 200));
            window->draw(card);

            sf::Text qTxt;
            qTxt.setFont(*font);
            qTxt.setString("?");
            qTxt.setCharacterSize(52);
            qTxt.setFillColor(sf::Color(120, 80, 200));
            qTxt.setPosition(cardX[i] + 48, cardY[i] + 38);
            window->draw(qTxt);
        }
    }
}

int MemoryMatch::run(Leaderboard* lb) {
    // Ask Player 1 name
    window->clear(sf::Color(80, 0, 120));
    sf::Text p1Label;
    p1Label.setFont(*font);
    p1Label.setString("PLAYER 1");
    p1Label.setCharacterSize(28);
    p1Label.setFillColor(sf::Color(150, 100, 255));
    p1Label.setPosition(350, 170);
    window->draw(p1Label);
    window->display();
    getName(window, font, name1);

    // Ask Player 2 name
    window->clear(sf::Color(80, 0, 120));
    sf::Text p2Label;
    p2Label.setFont(*font);
    p2Label.setString("PLAYER 2");
    p2Label.setCharacterSize(28);
    p2Label.setFillColor(sf::Color(200, 150, 255));
    p2Label.setPosition(350, 170);
    window->draw(p2Label);
    window->display();
    getName(window, font, name2);

    currentPlayer = 1;
    score1 = 0; score2 = 0;
    reset();

    sf::Clock clock;

    while (window->isOpen()) {
        float dt = clock.restart().asSeconds();

        // Flip back timer
        if (waiting) {
            waitTimer += dt;
            if (waitTimer >= 1.0f) {
                flipped[firstCard] = false;
                flipped[secondCard] = false;
                firstCard = -1;
                secondCard = -1;
                flippedCount = 0;
                waiting = false;
            }
        }

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    return 0;

            if (event.type == sf::Event::MouseButtonPressed) {
                int mx = event.mouseButton.x;
                int my = event.mouseButton.y;

                if (!gameOver)
                    handleClick(mx, my);

                if (gameOver) {
                    if (restartBtn.getGlobalBounds().contains(mx, my)) {
                        currentPlayer = 1;
                        score1 = 0; score2 = 0;
                        reset();
                    }
                    if (lbBtn.getGlobalBounds().contains(mx, my))
                        if (lb != nullptr) lb->run();
                    if (backBtn.getGlobalBounds().contains(mx, my)) {
                        if (lb != nullptr) {
                            lb->addRecord(name1, "MEMORY", score1);
                            lb->addRecord(name2, "MEMORY", score2);
                        }
                        return 0;
                    }
                }
            }
        }

        // ── Draw ──
        window->clear(sf::Color(10, 5, 20));
        window->draw(topBar);
        window->draw(titleTxt);

        // Scores — top left and top right
        char buf[20], combined[60];
        intToStr(score1, buf);
        strCombine("P1: ", buf, combined);
        score1Txt.setString(combined);
        window->draw(score1Txt);

        intToStr(score2, buf);
        strCombine("P2: ", buf, combined);
        score2Txt.setString(combined);
        window->draw(score2Txt);

        // Turn — below title
        if (!gameOver) {
            char turnBuf[60];
            strCombine("TURN: ",
                currentPlayer == 1 ? name1 : name2,
                turnBuf);
            turnTxt.setString(turnBuf);
            window->draw(turnTxt);
        }

        drawCards();

        // Bottom bar
    /*    window->draw(bottomBar);*/

        if (!gameOver) {
            // Status centered at bottom
            statusTxt.setString("FLIP TWO CARDS TO FIND A PAIR!");
            statusTxt.setFillColor(sf::Color(180, 150, 255));
            statusTxt.setPosition(210, 512);
            window->draw(statusTxt);

        }
        else {
            // Winner message — centered
            if (score1 > score2) {
                char winMsg[80];
                strCombine(name1, " WINS!", winMsg);
                statusTxt.setString(winMsg);
                statusTxt.setFillColor(sf::Color(150, 100, 255));
            }
            else if (score2 > score1) {
                char winMsg[80];
                strCombine(name2, " WINS!", winMsg);
                statusTxt.setString(winMsg);
                statusTxt.setFillColor(sf::Color(255, 120, 120));
            }
            else {
                statusTxt.setString("ITS A DRAW!");
                statusTxt.setFillColor(sf::Color(220, 180, 255));
            }
            statusTxt.setPosition(320, 512);
            window->draw(statusTxt);

            // Hover effects
            sf::Vector2i mp = sf::Mouse::getPosition(*window);

            // Leaderboard — bottom left
            lbBtn.setFillColor(lbBtn.getGlobalBounds().contains(mp.x, mp.y)
                ? sf::Color(40, 70, 160) : sf::Color(20, 40, 100));

            // Restart — bottom center
            restartBtn.setFillColor(restartBtn.getGlobalBounds().contains(mp.x, mp.y)
                ? sf::Color(70, 40, 140) : sf::Color(40, 20, 80));

            // Back — bottom right
            backBtn.setFillColor(backBtn.getGlobalBounds().contains(mp.x, mp.y)
                ? sf::Color(140, 20, 40) : sf::Color(80, 10, 20));

            window->draw(lbBtn);      window->draw(lbTxt);
            window->draw(restartBtn); window->draw(restartTxt);
            window->draw(backBtn);    window->draw(backTxt);
        }

        window->display();
    }
    return 0;
}