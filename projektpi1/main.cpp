#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include "globals.hpp"
#include "helper.hpp"

sf::Vector2f mainWin = { 800.0f, 600.0f };

enum class GameState { Menu, Game, GameMenu };

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Flanki");
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect({0.f, 0.f}, mainWin));
    view.setCenter(sf::Vector2f(mainWin.x / 2.f, mainWin.y / 2.f));
    updateViewViewport(window, view);
    window.setView(view);

    GameState currentState = GameState::Menu;

    sf::Font font;
    if (!font.openFromFile("assets/fonts/DejaVuSans.ttf")) return -1;

	Button playButton({ 200.f, 60.f }, { 300.f, 200.f }, sf::Color(50, 50, 50), "START", font, 30);
	Button exitButton({ 200.f, 60.f }, { 300.f, 300.f }, sf::Color(50, 50, 50), "WYJSCIE", font, 30);

    sf::RectangleShape logicalBackground(mainWin);
    logicalBackground.setPosition({ 0.f, 0.f });
    logicalBackground.setFillColor(sf::Color(0, 0, 255));

    sf::CircleShape ball(50.f);
    ball.setFillColor(sf::Color::Black);
    ball.setPosition({375.f, 275.f});

    float speed = 200.f;
    sf::Clock clock;

    while (window.isOpen()) {
    float dt = clock.restart().asSeconds();

    sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePosI, view);

    // EVENT LOOP
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            updateViewViewport(window, view);
            view.setSize(mainWin);
            view.setCenter({ mainWin.x / 2.f, mainWin.y / 2.f });
            window.setView(view);
        }

        if (currentState == GameState::Menu) {
            if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseEvent->button == sf::Mouse::Button::Left) {
                    if (playButton.isMouseOver(mousePos))
                        currentState = GameState::Game;

                    if (exitButton.isMouseOver(mousePos))
                        window.close();
                }
            }
        }
    }

    // LOGIKA
    if (currentState == GameState::Game) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
            ball.move({0.f, -speed * dt});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
            ball.move({0.f, speed * dt});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
            ball.move({-speed * dt, 0.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
            ball.move({speed * dt, 0.f});

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
            currentState = GameState::Menu;
    }

    // DRAW
    window.clear(sf::Color::Black);
    window.setView(view);
    window.draw(logicalBackground);

    if (currentState == GameState::Menu) {
        playButton.draw(window);
        exitButton.draw(window);
    }
    else if (currentState == GameState::Game) {
        window.draw(ball);
    }

    window.display();
}
}