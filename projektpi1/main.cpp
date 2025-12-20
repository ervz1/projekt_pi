#include <SFML/Graphics.hpp>
#include <iostream>
#include "globals.hpp"
#include "helper.hpp"

sf::Vector2f mainWin = { 800.0f, 600.0f };

enum class GameState { Menu, Game, GameMenu };

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Flanki");
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect({0.f, 0.f}, mainWin));
    view.setCenter(sf::Vector2(mainWin.x / 2.f, mainWin.y / 2.f));
    updateViewViewport(window, view);
    window.setView(view);

    GameState currentState = GameState::Menu;

    sf::Font font;
    if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) return -1;

	Button playButton({ 200.f, 60.f }, { 300.f, 200.f }, sf::Color(50, 50, 50), "START", font, 30);
	Button exitButton({ 200.f, 60.f }, { 300.f, 300.f }, sf::Color(50, 50, 50), "WyJSCIE", font, 30);

    sf::RectangleShape logicalBackground(mainWin);
    logicalBackground.setPosition({ 0.f, 0.f });
    logicalBackground.setFillColor(sf::Color(0, 0, 255));


    while (window.isOpen()) {
        sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mousePosI, view);
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                updateViewViewport(window, view);
                view.setSize(mainWin);
                view.setCenter({ mainWin.x / 2.f, mainWin.y / 2.f });
                window.setView(view);
            }

            if (currentState == GameState::Menu) {
                if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mouseEvent->button == sf::Mouse::Button::Left) {
                        if (playButton.isMouseOver(mousePos)) {
                            currentState = GameState::Game;
                        }
                        if (exitButton.isMouseOver(mousePos)) {
                            window.close();
                        }
                    }
                }
            }
        }

        if (currentState == GameState::Menu) {
            if (playButton.isMouseOver(mousePos)) {
                playButton.setFillColor(sf::Color(100, 100, 100));
            }
            else {
                playButton.setFillColor(sf::Color(50, 50, 50));
            }

            if (exitButton.isMouseOver(mousePos)) {
                exitButton.setFillColor(sf::Color(150, 0, 0));
            }
            else {
                exitButton.setFillColor(sf::Color(50, 50, 50));
            }
        }

        window.clear(sf::Color::Black);
        window.setView(view);
        window.draw(logicalBackground);
        if (currentState == GameState::Menu) {
			playButton.draw(window);
			exitButton.draw(window);
        }
        else if (currentState == GameState::Game) {
            sf::CircleShape ball(50.f);
            ball.setFillColor(sf::Color::Green);
            ball.setPosition({ 375.f, 275.f });
            window.draw(ball);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) {
                currentState = GameState::Menu;
            }
        }

        window.display();
    }

    return 0;
}