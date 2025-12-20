#include <SFML/Graphics.hpp>
#include <iostream>

enum class GameState { Menu, Game, GameMenu };

class Button {
public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const std::string& textString, const sf::Font& font, unsigned int charSize)
        : shape(size), text(font, textString, charSize) {
        shape.setPosition(position);
        shape.setFillColor(color);
        text.setPosition(sf::Vector2f(position.x + size.x/2.0f - text.getLocalBounds().size.x/2.0f, position.y + size.y / 2.0f - text.getLocalBounds().size.y / 2.0f - 5.0f));
    }
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }
    bool isMouseOver(const sf::Vector2f& mousePos) {
        return shape.getGlobalBounds().contains(mousePos);
    }
    void setFillColor(const sf::Color& color) {
        shape.setFillColor(color);
    }
private:
    sf::RectangleShape shape;
    sf::Text text;
};

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Flanki");
    window.setFramerateLimit(60);

    GameState currentState = GameState::Menu;

    sf::Font font;
    if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) return -1;

	Button playButton({ 200.f, 60.f }, { 300.f, 200.f }, sf::Color(50, 50, 50), "START", font, 30);
	Button exitButton({ 200.f, 60.f }, { 300.f, 300.f }, sf::Color(50, 50, 50), "WyJSCIE", font, 30);

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

        // --- LOGIKA MENU (EFEKT HOVER) ---
        if (currentState == GameState::Menu) {
            // Reakcja na najechanie myszką - START
            if (playButton.isMouseOver(mousePos)) {
                playButton.setFillColor(sf::Color(100, 100, 100));
            }
            else {
                playButton.setFillColor(sf::Color(50, 50, 50));
            }

            // Reakcja na najechanie myszką - WYJSCIE
            if (exitButton.isMouseOver(mousePos)) {
                exitButton.setFillColor(sf::Color(150, 0, 0)); // Czerwony przy wyjściu
            }
            else {
                exitButton.setFillColor(sf::Color(50, 50, 50));
            }
        }

        // --- RYSOWANIE ---
        window.clear(sf::Color(0, 0, 255));

        if (currentState == GameState::Menu) {
			playButton.draw(window);
			exitButton.draw(window);
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