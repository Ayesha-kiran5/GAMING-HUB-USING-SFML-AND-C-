//ayeshakiran_seb_i252108
#pragma once
#include "Helpers.h"

const int MAX_RECORDS = 100;

struct Record {
    char playerName[50];
    char gameName[50];
    int  score;
};

class Leaderboard {
private:
    Record records[MAX_RECORDS];
    int count;

    sf::RenderWindow* window;
    sf::Font* font;

    sf::RectangleShape topBar;
    sf::RectangleShape backBtn;
    sf::RectangleShape bg;
    sf::RectangleShape rowBg[10];

    sf::Text titleTxt;
    sf::Text backTxt;
    sf::Text noRecordsTxt;
    sf::Text headerRank;
    sf::Text headerName;
    sf::Text headerGame;
    sf::Text headerScore;

    void sortRecords() {
        for (int i = 0; i < count - 1; i++)
            for (int j = 0; j < count - i - 1; j++)
                if (records[j].score < records[j + 1].score) {
                    Record temp = records[j];
                    records[j] = records[j + 1];
                    records[j + 1] = temp;
                }
    }

    void drawRow(int rank, Record& r, float y) {
        char buf[20];

        sf::Text rankTxt;
        rankTxt.setFont(*font);
        rankTxt.setCharacterSize(16);
        intToStr(rank, buf);
        rankTxt.setString(buf);
        rankTxt.setPosition(60, y + 10);
        rankTxt.setFillColor(
            rank == 1 ? sf::Color(255, 215, 0) :
            rank == 2 ? sf::Color(192, 192, 192) :
            rank == 3 ? sf::Color(205, 127, 50) :
            sf::Color(200, 200, 200));
        window->draw(rankTxt);

        sf::Text nameTxt;
        nameTxt.setFont(*font);
        nameTxt.setCharacterSize(16);
        nameTxt.setString(r.playerName);
        nameTxt.setPosition(180, y + 10);
        nameTxt.setFillColor(sf::Color(220, 220, 255));
        window->draw(nameTxt);

        sf::Text gameTxt;
        gameTxt.setFont(*font);
        gameTxt.setCharacterSize(16);
        gameTxt.setString(r.gameName);
        gameTxt.setPosition(450, y + 10);
        gameTxt.setFillColor(sf::Color(150, 220, 150));
        window->draw(gameTxt);

        sf::Text scoreTxt;
        scoreTxt.setFont(*font);
        scoreTxt.setCharacterSize(16);
        intToStr(r.score, buf);
        scoreTxt.setString(buf);
        scoreTxt.setPosition(730, y + 10);
        scoreTxt.setFillColor(sf::Color(255, 180, 100));
        window->draw(scoreTxt);
    }

public:
    Leaderboard(sf::RenderWindow* w, sf::Font* f) {
        window = w;
        font = f;
        count = 0;

        bg.setSize(sf::Vector2f(900, 600));
        bg.setPosition(0, 0);
        bg.setFillColor(sf::Color(10, 10, 25));

        topBar.setSize(sf::Vector2f(900, 60));
        topBar.setPosition(0, 0);
        topBar.setFillColor(sf::Color(20, 20, 50));

        titleTxt.setFont(*font);
        titleTxt.setString("LEADERBOARD");
        titleTxt.setCharacterSize(26);
        titleTxt.setFillColor(sf::Color(220, 180, 255));
        titleTxt.setPosition(320, 15);

        headerRank.setFont(*font);
        headerRank.setString("RANK");
        headerRank.setCharacterSize(16);
        headerRank.setFillColor(sf::Color(180, 180, 255));
        headerRank.setPosition(50, 75);

        headerName.setFont(*font);
        headerName.setString("PLAYER");
        headerName.setCharacterSize(16);
        headerName.setFillColor(sf::Color(180, 180, 255));
        headerName.setPosition(180, 75);

        headerGame.setFont(*font);
        headerGame.setString("GAME");
        headerGame.setCharacterSize(16);
        headerGame.setFillColor(sf::Color(180, 180, 255));
        headerGame.setPosition(450, 75);

        headerScore.setFont(*font);
        headerScore.setString("SCORE");
        headerScore.setCharacterSize(16);
        headerScore.setFillColor(sf::Color(180, 180, 255));
        headerScore.setPosition(720, 75);

        for (int i = 0; i < 10; i++) {
            rowBg[i].setSize(sf::Vector2f(860, 38));
            rowBg[i].setPosition(20, 100 + i * 44);
            rowBg[i].setFillColor(i % 2 == 0
                ? sf::Color(25, 25, 55)
                : sf::Color(20, 20, 45));
            rowBg[i].setOutlineThickness(1);
            rowBg[i].setOutlineColor(sf::Color(60, 60, 100));
        }


        backBtn.setSize(sf::Vector2f(180, 44));
        backBtn.setPosition(360, 545);
        backBtn.setFillColor(sf::Color(60, 30, 100));
        backBtn.setOutlineThickness(2);
        backBtn.setOutlineColor(sf::Color(180, 100, 255));

        backTxt.setFont(*font);
        backTxt.setString("BACK TO MENU");
        backTxt.setCharacterSize(16);
        backTxt.setFillColor(sf::Color::White);
        backTxt.setPosition(383, 556);

        loadFromFile();
    }

    ~Leaderboard() {}

    void addRecord(const char* name, const char* game, int score) {
        if (count >= MAX_RECORDS) return;
        myCopy(name, records[count].playerName);
        myCopy(game, records[count].gameName);
        records[count].score = score;
        count++;
        sortRecords();
        saveToFile();
    }

    void saveToFile() {
        std::ofstream file("leaderboard.txt");
        if (!file.is_open()) return;
        for (int i = 0; i < count; i++) {
            int j = 0;
            while (records[i].playerName[j] != '\0')
                file << records[i].playerName[j++];
            file << ',';
            j = 0;
            while (records[i].gameName[j] != '\0')
                file << records[i].gameName[j++];
            file << ',';
            char buf[20];
            intToStr(records[i].score, buf);
            j = 0;
            while (buf[j] != '\0') file << buf[j++];
            file << '\n';
        }
        file.close();
    }

    void loadFromFile() {
        count = 0;
        std::ifstream file("leaderboard.txt");
        if (!file.is_open()) return;

        char line[150];
        while (file.getline(line, 150) && count < MAX_RECORDS) {
            char name[50], game[50], scoreStr[20];
            int li = 0, ni = 0, gi = 0, si = 0, field = 0;

            while (line[li] != '\0') {
                if (line[li] == ',') { field++; }
                else {
                    if (field == 0 && ni < 49) name[ni++] = line[li];
                    if (field == 1 && gi < 49) game[gi++] = line[li];
                    if (field == 2 && si < 19) scoreStr[si++] = line[li];
                }
                li++;
            }
            name[ni] = '\0'; game[gi] = '\0'; scoreStr[si] = '\0';

            int score = 0;
            for (int k = 0; scoreStr[k] != '\0'; k++)
                score = score * 10 + (scoreStr[k] - '0');

            myCopy(name, records[count].playerName);
            myCopy(game, records[count].gameName);
            records[count].score = score;
            count++;
        }
        file.close();
        sortRecords();
    }

    int run() {
        while (window->isOpen()) {
            sf::Event event;
            sf::Vector2i mp = sf::Mouse::getPosition(*window);

            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape) return 0;
                if (event.type == sf::Event::MouseButtonPressed)
                    if (backBtn.getGlobalBounds().contains(
                        (float)event.mouseButton.x,
                        (float)event.mouseButton.y)) return 0;
            }

            backBtn.setFillColor(backBtn.getGlobalBounds().contains(mp.x, mp.y)
                ? sf::Color(100, 50, 160) : sf::Color(60, 30, 100));

            window->clear(sf::Color(10, 10, 25));
            window->draw(bg);
            window->draw(topBar);
            window->draw(titleTxt);
            window->draw(headerRank);
            window->draw(headerName);
            window->draw(headerGame);
            window->draw(headerScore);

            if (count == 0) {
                window->draw(noRecordsTxt);
            }
            else {
                int show = count < 10 ? count : 10;
                for (int i = 0; i < show; i++) {
                    window->draw(rowBg[i]);
                    drawRow(i + 1, records[i], 100 + i * 44);
                }
            }

            window->draw(backBtn);
            window->draw(backTxt);
            window->display();
        }
        return 0;
    }
};