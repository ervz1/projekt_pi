#include <SFML/Graphics.hpp>
#include <iostream>

enum class GameState { Menu, Game };

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Menu z Przyciskami");
    window.setFramerateLimit(60);

    GameState currentState = GameState::Menu;

    sf::Font font;
    if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) return -1;

    // --- PRZYCISK START ---
    sf::RectangleShape playButton({ 200.f, 60.f });
    playButton.setPosition({ 300.f, 200.f });
    playButton.setFillColor(sf::Color(50, 50, 50));

    sf::Text playText(font, "START", 30);
    playText.setPosition({ 350.f, 210.f });

    // --- PRZYCISK WYJSCIE ---
    sf::RectangleShape exitButton({ 200.f, 60.f });
    exitButton.setPosition({ 300.f, 300.f });
    exitButton.setFillColor(sf::Color(50, 50, 50));

    sf::Text exitText(font, "WYJSCIE", 30);
    exitText.setPosition({ 335.f, 310.f });

    while (window.isOpen()) {
        // Pobierz pozycję myszy względem okna
        sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = sf::Vector2f(static_cast<float>(mousePosI.x), static_cast<float>(mousePosI.y));

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (currentState == GameState::Menu) {
                // Obsługa kliknięć
                if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mouseEvent->button == sf::Mouse::Button::Left) {
                        if (playButton.getGlobalBounds().contains(mousePos)) {
                            currentState = GameState::Game;
                        }
                        if (exitButton.getGlobalBounds().contains(mousePos)) {
                            window.close();
                        }
                    }
                }
            }
        }

        // --- LOGIKA MENU (EFEKT HOVER) ---
        if (currentState == GameState::Menu) {
            // Reakcja na najechanie myszką - START
            if (playButton.getGlobalBounds().contains(mousePos)) {
                playButton.setFillColor(sf::Color(100, 100, 100));
            }
            else {
                playButton.setFillColor(sf::Color(50, 50, 50));
            }

            // Reakcja na najechanie myszką - WYJSCIE
            if (exitButton.getGlobalBounds().contains(mousePos)) {
                exitButton.setFillColor(sf::Color(150, 0, 0)); // Czerwony przy wyjściu
            }
            else {
                exitButton.setFillColor(sf::Color(50, 50, 50));
            }
        }

        // --- RYSOWANIE ---
        window.clear(sf::Color(20, 20, 20));

        if (currentState == GameState::Menu) {
            window.draw(playButton);
            window.draw(playText);
            window.draw(exitButton);
            window.draw(exitText);
        }
        else if (currentState == GameState::Game) {

            // ==========================================
            // TUTAJ ZACZNIJ ROBIĆ SWOJĄ GRĘ
            // Przykład: narysuj coś, co potwierdzi, że gra działa
            // ==========================================
            sf::CircleShape ball(50.f);
            ball.setFillColor(sf::Color::Green);
            ball.setPosition({ 375.f, 275.f });
            window.draw(ball);

            // Powrót do menu za pomocą ESC
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) {
                currentState = GameState::Menu;
            }
        }

        window.display();
    }

    return 0;
}