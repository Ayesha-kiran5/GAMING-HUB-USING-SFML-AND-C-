//ayeshakiran_seb_i252108
#include <SFML/Graphics.hpp>
#include "ponggame.h"
#include"tictactoe.h"
#include"leaderboard.h"
#include"Helpers.h"
#include"memorycard.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(900, 600), "Gaming Hub");
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("ARLRDBD.TTF");

    Leaderboard lb(&window, &font);

    // ── Background ──
    sf::RectangleShape bgRect(sf::Vector2f(900, 600));
    bgRect.setFillColor(sf::Color(10, 10, 25));

    // ── Neon Grid ──
    const int GRID_SPACING = 40;
    sf::VertexArray grid(sf::Lines);

    for (int x = 0; x <= 900; x += GRID_SPACING) {
        grid.append(sf::Vertex(sf::Vector2f(x, 0), sf::Color(120, 40, 255, 30)));
       grid.append(sf::Vertex(sf::Vector2f(x, 600), sf::Color(120, 40, 255, 30)));
    }
    
    for (int y = 0; y <= 600; y += GRID_SPACING) {
        grid.append(sf::Vertex(sf::Vector2f(0, y), sf::Color(120, 40, 255, 30)));
        grid.append(sf::Vertex(sf::Vector2f(900, y), sf::Color(120, 40, 255, 30)));
    }

    // ── Side panels ──
    sf::RectangleShape leftPanel(sf::Vector2f(220, 600));
    leftPanel.setFillColor(sf::Color(10, 5, 30, 180));

    sf::RectangleShape rightPanel(sf::Vector2f(220, 600));
    rightPanel.setPosition(680, 0);
    rightPanel.setFillColor(sf::Color(10, 5, 30, 180));

    // ── Title ──
    sf::RectangleShape titleBar(sf::Vector2f(500, 70));
    titleBar.setPosition(200, 40);
    titleBar.setFillColor(sf::Color(60, 20, 120, 180));
    titleBar.setOutlineThickness(2);
    titleBar.setOutlineColor(sf::Color(180, 100, 255));

    sf::Text title("GAMING HUB", font, 38);
    title.setPosition(290, 52);
    title.setFillColor(sf::Color(220, 150, 255));

    sf::Text subtitle("SELECT A GAME", font, 14);
    subtitle.setPosition(368, 130);
    subtitle.setFillColor(sf::Color(150, 120, 200));

    // ── Buttons ──
    const int BTN_COUNT = 4;

    sf::Color btnColors[] = {
        sf::Color(80,40,160),
        sf::Color(40,120,80),
        sf::Color(120,60,20),
        sf::Color(20,80,160)
    };

    sf::Color btnHover[] = {
        sf::Color(120,70,220),
        sf::Color(60,180,110),
        sf::Color(180,90,40),
        sf::Color(40,120,220)
    };

    const char* labels[] = { "TIC TAC TOE","PONG","MEMORYCARD","LEADERBOARD" };

    sf::RectangleShape buttons[BTN_COUNT];
    sf::RectangleShape btnGlow[BTN_COUNT];
    sf::Text btnLabel[BTN_COUNT];

    for (int i = 0; i < BTN_COUNT; i++) {

        buttons[i].setSize(sf::Vector2f(300, 55));
        buttons[i].setPosition(300, 160 + i * 88);
        buttons[i].setFillColor(btnColors[i]);
        buttons[i].setOutlineThickness(2);
        buttons[i].setOutlineColor(sf::Color(180, 100, 255, 120));

        btnGlow[i].setSize(sf::Vector2f(314, 69));
        btnGlow[i].setPosition(293, 153 + i * 88);
        btnGlow[i].setFillColor(sf::Color::Transparent);
        btnGlow[i].setOutlineThickness(3);

        btnLabel[i].setFont(font);
        btnLabel[i].setString(labels[i]);
        btnLabel[i].setCharacterSize(20);
        btnLabel[i].setFillColor(sf::Color::White);
        btnLabel[i].setPosition(360, 174 + i * 88);
    }

    sf::Text footer("PRESS ESC TO EXIT", font, 12);
    footer.setPosition(358, 570);
    footer.setFillColor(sf::Color(100, 80, 150));

    float time = 0;
    int screen = 0;

    while (window.isOpen()) {

        if (screen == 0) {

            sf::Event event;
            sf::Vector2i mp = sf::Mouse::getPosition(window);

            while (window.pollEvent(event)) {

                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::KeyPressed)
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();

                if (event.type == sf::Event::MouseButtonPressed) {

                    for (int i = 0; i < BTN_COUNT; i++) {
                        if (buttons[i].getGlobalBounds().contains(
                            (float)event.mouseButton.x,
                            (float)event.mouseButton.y))
                            screen = i + 1;
                    }
                }
            }

            time += 0.02f;
             
            // ── Draw Menu ──
            window.clear();
            window.draw(bgRect);
            window.draw(grid);
            window.draw(leftPanel);
            window.draw(rightPanel);

            window.draw(titleBar);
            window.draw(title);
            window.draw(subtitle);

            for (int i = 0; i < BTN_COUNT; i++) {
                window.draw(btnGlow[i]);
                window.draw(buttons[i]);
                window.draw(btnLabel[i]);
            }

            window.draw(footer);
            window.display();
        }

        else if (screen == 1) {
            TicTacToe ttt(&window, &font);
            ttt.run(&lb);
            screen = 0;
        }

        else if (screen == 2) {
            Pong pong(&window, &font);
            pong.run(&lb);
            screen = 0;
        }

        else if (screen == 3) {
            MemoryMatch mm(&window, &font);
            mm.run(&lb);
            screen = 0;
        }

        else if (screen == 4) {
            lb.run();
            screen = 0;
        }
    }

    return 0;
}
