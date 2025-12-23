#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include "globals.hpp"
#include "helper.hpp"
#include <SFML/Audio.hpp>

sf::Vector2f mainWin = { 800.0f, 600.0f };

enum class GameState { Menu, Game, GameMenu };

struct GameStart {
    sf::Vector2f velocity = { 0.f, 0.f };
    float up = 0.0f;
    float left = 0.0f;
    bool isCharging = false;
    bool isFlying = false;
    float maxCharge = 800.0f;
    float ball_x = 700.f;
    float ball_y = 300.f;
};

int main() {
    GameStart game;
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Flanki");
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect({ 0.f, 0.f }, mainWin));
    view.setCenter(sf::Vector2f(mainWin.x / 2.f, mainWin.y / 2.f));
    updateViewViewport(window, view);
    window.setView(view);

    GameState currentState = GameState::Menu;

    sf::Font font;
    if (!font.openFromFile("../assets/fonts/DejaVuSans.ttf")) return -1;

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../assets/music/clank.mp3")) return -1;
    sf::Sound sound(buffer);

    sf::Clock keyTimer;
    Button playButton({ 200.f, 60.f }, { 300.f, 200.f }, sf::Color(50, 50, 50), "START", font, 30);
    Button exitButton({ 200.f, 60.f }, { 300.f, 300.f }, sf::Color(50, 50, 50), "WYJSCIE", font, 30);

    sf::RectangleShape logicalBackground(mainWin);
    logicalBackground.setPosition({ 0.f, 0.f });
    logicalBackground.setFillColor(sf::Color(0, 0, 255));

    sf::CircleShape can(15.f);
    can.setFillColor(sf::Color::Yellow);
    can.setPosition({ 400.f, 300.f });

    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::Black);
    ball.setPosition({ game.ball_x, game.ball_y });

    float gravity = 980.f;
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
        if (currentState == GameState::Game)
        {
            //reset
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) {
                currentState = GameState::Menu;
                game = GameStart();
                ball.setPosition({ game.ball_x, game.ball_y });
                can.setFillColor(sf::Color::Yellow);
            }
            //charge
            if (!game.isFlying)
            {
                bool chargingUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up);
                bool chargingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left);

                if (chargingUp || chargingLeft) {
                    game.isCharging = true;
                    //charging until max
                    if (chargingUp) game.up += 250.f * dt * 2;
                    if (chargingLeft) game.left += 250.f * dt * 2;


                    //if charged to max
                    //cap at max
                    /*if (game.up > game.maxCharge) game.up = game.maxCharge;
                    if (game.left > game.maxCharge) game.left = game.maxCharge;*/


                    // reset bar
                    if (game.up > game.maxCharge) game.up = 0.0f;
                    if (game.left > game.maxCharge) game.left = 0.0f;
                }
                //throw
                else if (game.isCharging) {
                    game.isCharging = false;
                    game.isFlying = true;
                    game.velocity = sf::Vector2f(-game.left, -game.up);
                    game.up = 0.0f;
                    game.left = 0.0f;
                }
            }
            else
            {
                //add gravity to y axis of velocity
                game.velocity.y += gravity * dt;

                //move based on velocity
                ball.move(game.velocity * dt);


                //Reset after ground
                if (ball.getPosition().y > 600.f) {
                    game.isFlying = false;
                    game.velocity = { 0.f, 0.f };
                    ball.setPosition({ game.ball_x, game.ball_y });
                }

                //Collision
                if (ball.getGlobalBounds().findIntersection(can.getGlobalBounds()))
                {
                    //Bounce
                    game.velocity.x = -game.velocity.x * 1.0f;
                    game.velocity.y = -game.velocity.y * 1.0f;
                    can.setFillColor(sf::Color::Magenta);
                    if (sound.getStatus() != sf::Sound::Status::Playing)
                    {
                        sound.play();
                    }
                }
            }
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
            window.draw(can);

            if (!game.isFlying && (game.up > 0.0f || game.left > 0.0f)) {
                if (game.up > 0.0f) {
                    sf::RectangleShape powerBar(sf::Vector2f(10.f, -game.up / 10.f));
                    powerBar.setFillColor(sf::Color::Red);
                    powerBar.setPosition(ball.getPosition() );
                    window.draw(powerBar);
                }
                if (game.left > 0.0f) {
                    sf::RectangleShape powerBar(sf::Vector2f(-game.left / 10.f, 10.f));
                    powerBar.setFillColor(sf::Color::Red);
                    powerBar.setPosition(ball.getPosition() );
                    window.draw(powerBar);
                }




            }
        }
        window.display();
    }
}