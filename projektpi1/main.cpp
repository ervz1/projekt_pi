#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include "globals.hpp"
#include "helper.hpp"
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>

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
    bool turn = false;
    bool hasHit = false;
    sf::Vector2f initialVelocity;
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
    if (!font.openFromFile("assets/fonts/DejaVuSans.ttf")) return -1;

    sf::SoundBuffer buffer;
<<<<<<< HEAD
    if (!buffer.loadFromFile("../assets/music/clank.mp3")) return -1;
=======
    if (!buffer.loadFromFile("assets/music/clank.mp3")) return -1;
    
>>>>>>> 9058253 (save przed pullem)
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

    sf::CircleShape ball2(10.f);
    ball2.setFillColor(sf::Color::White);
    ball2.setPosition({  100.0f, game.ball_y });

    float gravity = 980.f;
    sf::Clock clock;
    

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mousePosI, view);
        float ramp_up = 250.f * dt * 2;

<<<<<<< HEAD
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
=======
    sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePosI, view);

    // EVENT LOOP
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();
        
        else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            updateViewViewport(window, view);
            view.setSize(mainWin);
            view.setCenter({ mainWin.x / 2.f, mainWin.y / 2.f });
            window.setView(view);
        }

        else if (currentState == GameState::Menu) {
            if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseEvent->button == sf::Mouse::Button::Left) {
                    if (playButton.isMouseOver(mousePos))
                        currentState = GameState::Game;

                    if (exitButton.isMouseOver(mousePos))
                        window.close();
>>>>>>> 9058253 (save przed pullem)
                }
            }
        }

        // LOGIKA
        if (currentState == GameState::Game)
        {
            //Reset
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) {
                currentState = GameState::Menu;
                game = GameStart();
                ball.setPosition({ game.ball_x, game.ball_y });
                can.setFillColor(sf::Color::Yellow);
            }


            //Charge
            if (!game.isFlying)
            {
                if (!game.turn) {

                    bool chargingUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up);
                    bool chargingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left);

                    if (chargingUp || chargingLeft) {
                        game.isCharging = true;
                        //Charging until max
                        if (chargingUp) game.up += ramp_up;
                        if (chargingLeft) game.left += ramp_up;


                        //If charged to max:
                        
                        //Cap at max
                        /*if (game.up > game.maxCharge) game.up = game.maxCharge;
                        if (game.left > game.maxCharge) game.left = game.maxCharge;*/


                        // Reset bar
                        if (game.up > game.maxCharge) game.up = 0.0f;
                        if (game.left > game.maxCharge) game.left = 0.0f;
                    }
                    //Throw
                    else if (game.isCharging) {
                        game.isCharging = false;
                        game.isFlying = true;
                        game.velocity = sf::Vector2f(-game.left, -game.up);
                        game.initialVelocity = game.velocity;
                        game.hasHit = false;
                        game.up = 0.0f;
                        game.left = 0.0f;
                    }

                }
                else if (game.turn) {
                    std::random_device rd;  
                    std::mt19937 gen(rd()); 
                    std::uniform_real_distribution<> dis(185.0f, 800.0f);
                    std::uniform_real_distribution<> dis2(-130.0f, 130.0f);
                    float random_x = dis(gen);

                    //Flight trajectory math
                    // t = Distance/Vx
                    //Height = (Vy​*t)−(1/2​*Gravity*t^2)
                    //Vy = ((Gravity*Distance) / (2*Vx)) + (Height * Vx / Distance)

                    //Distance ball2 from can
                    
                    //x axis
                    float distance = std::abs(can.getPosition().x - ball2.getPosition().x);

                    //y axis
                    float height = can.getPosition().y - ball2.getPosition().y;

                    //Velocityx * Velocityy = gravity*distance / 2
                    float physicsConstant = (gravity * distance) / 2.0f;

                    //Veloicttyy = gravity * distance /2 / velocityx - ((height * random_x)/ distance) (- because y axis in sfml upside down)
                    float random_y = (physicsConstant / random_x) -  ((height * random_x)/ distance);
                    

                    std::cout << random_x << ' ' << random_y << std::endl;


                    //Margin of error (0 = enemy always hits)
                    //float error = dis2(gen); 
                    float error = 0.0f;
                    game.velocity = sf::Vector2f(random_x, -(error+ random_y));
                    //game.velocity = sf::Vector2f(687.352, -175.465);
                    game.initialVelocity = game.velocity;
                    game.hasHit = false;
                    

                    game.isFlying = true;
                }
            }
            else
            {
                //Add gravity to y axis of velocity
                game.velocity.y += gravity * dt;
                if (!game.turn) {
                    

                    //Move based on velocity
                    ball.move(game.velocity * dt);

                    //Collision
                    if (ball.getGlobalBounds().findIntersection(can.getGlobalBounds()))
                    {
                        //Bounce
                        if (!game.hasHit) {

                            //Adding data, save velocity if hit

                            /*std::fstream hit_data;
                            hit_data.open("../assets/data/hit_x_y.txt", std::ios::out | std::ios::app);
                            hit_data << std::abs(game.initialVelocity.x) << ' ' << std::abs(game.initialVelocity.y) << "\n";
                            hit_data.close();*/
                            

                            game.velocity.x = -game.velocity.x * 1.0f;
                            game.velocity.y = -game.velocity.y * 1.0f;
                            can.setFillColor(sf::Color::Magenta);
                            if (sound.getStatus() != sf::Sound::Status::Playing)
                            {
                                sound.play();

                            }
                            game.hasHit = true;
                        }
                        
                    }

                    //Reset after ground
                    if (ball.getPosition().y > 600.f) {
                        game.isFlying = false;
                        game.velocity = { 0.f, 0.f };
                        ball.setPosition({ game.ball_x, game.ball_y });
                        game.turn = true;
                    }
                   
                }
                else if (game.turn) {
                    

                    //Move based on velocity
                    ball2.move(game.velocity* dt);


                    //Collision
                    if (ball2.getGlobalBounds().findIntersection(can.getGlobalBounds()))
                    {
                        //Bounce

                        if (!game.hasHit) {
                            /*std::fstream hit_data;
                            hit_data.open("../assets/data/hit_x_y.txt", std::ios::out | std::ios::app);
                            hit_data << std::abs(game.initialVelocity.x) << ' ' << std::abs(game.initialVelocity.y) << "\n";
                            hit_data.close();*/

                            game.velocity.x = -game.velocity.x * 1.0f;
                            game.velocity.y = -game.velocity.y * 1.0f;
                            can.setFillColor(sf::Color::Magenta);
                            if (sound.getStatus() != sf::Sound::Status::Playing)
                            {
                                sound.play();

                            }
                            game.hasHit = true;
                        }
                        
                    }

                    //Reset after ground
                    if (ball2.getPosition().y > 600.f) {
                        game.isFlying = false;
                        game.velocity = { 0.f, 0.f };
                        ball2.setPosition({ 100.0f, game.ball_y });
                        game.turn = false;
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
            window.draw(ball2);

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