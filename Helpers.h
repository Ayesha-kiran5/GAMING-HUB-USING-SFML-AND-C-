//ayeshakiran_seb_i252108
#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

 inline void intToStr(int num, char* buf) {
    if (num == 0) { buf[0] = '0'; buf[1] = '\0'; return; }
    int i = 0, temp = num;
    while (temp > 0) { i++; temp /= 10; }
    buf[i] = '\0';
    while (num > 0) { buf[--i] = '0' + (num % 10); num /= 10; }
}
inline void strCombine(const char* a, const char* b, char* result) {
    int i = 0, j = 0;
    while (a[i] != '\0') { result[i] = a[i]; i++; }
    while (b[j] != '\0') { result[i + j] = b[j]; j++; }
    result[i + j] = '\0';
}

inline void myCopy(const char* src, char* dst) {
    int i = 0;
    while (src[i] != '\0') { dst[i] = src[i]; i++; }
    dst[i] = '\0';
}

inline void getName(sf::RenderWindow* window, sf::Font* font, char* nameOut) {
    sf::RectangleShape overlay(sf::Vector2f(900, 600));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));

    sf::RectangleShape box(sf::Vector2f(420, 160));
    box.setPosition(240, 210);
    box.setFillColor(sf::Color(25, 25, 60));
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color(180, 100, 255));

    sf::RectangleShape inputBox(sf::Vector2f(380, 44));
    inputBox.setPosition(260, 280);
    inputBox.setFillColor(sf::Color(40, 40, 90));
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(sf::Color(120, 80, 200));

    sf::Text prompt;
    prompt.setFont(*font);
    prompt.setString("ENTER YOUR NAME:");
    prompt.setCharacterSize(18);
    prompt.setFillColor(sf::Color(200, 170, 255));
    prompt.setPosition(310, 225);

    sf::Text inputTxt;
    inputTxt.setFont(*font);
    inputTxt.setCharacterSize(20);
    inputTxt.setFillColor(sf::Color::White);
    inputTxt.setPosition(268, 290);

    sf::Text confirmTxt;
    confirmTxt.setFont(*font);
    confirmTxt.setString("PRESS ENTER TO SAVE  |  ESC TO SKIP");
    confirmTxt.setCharacterSize(13);
    confirmTxt.setFillColor(sf::Color(130, 110, 180));
    confirmTxt.setPosition(258, 345);

    char name[50];
    int nameLen = 0;
    name[0] = '\0';

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return) {
                    if (nameLen > 0) myCopy(name, nameOut);
                    else             myCopy("Player", nameOut);
                    return;
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    myCopy("Player", nameOut);
                    return;
                }
                if (event.key.code == sf::Keyboard::BackSpace && nameLen > 0) {
                    nameLen--;
                    name[nameLen] = '\0';
                }
            }
            if (event.type == sf::Event::TextEntered) {
                char c = (char)event.text.unicode;
                if (nameLen < 49 && (
                    (c >= 'A' && c <= 'Z') ||
                    (c >= 'a' && c <= 'z') ||
                    (c >= '0' && c <= '9') ||
                    c == ' ')) {
                    name[nameLen++] = c;
                    name[nameLen] = '\0';
                }
            }
        }
        inputTxt.setString(name);
        window->clear(sf::Color(80, 0, 120));
        window->draw(overlay);
        window->draw(box);
        window->draw(inputBox);
        window->draw(prompt);
        window->draw(inputTxt);
        window->draw(confirmTxt);
        window->display();
    }
}