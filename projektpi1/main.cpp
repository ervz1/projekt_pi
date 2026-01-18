#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include "globals.hpp"
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
#include "helper.hpp"
#include <cmath> 
#include <vector>
#include "LoginStruktura.hpp"

// 1 - hair, 2 - skin, 3 - shirt, 4 - pants, 5 - shoes
int activeColorMode = 0;

sf::Vector2f mainWin = { 800.0f, 600.0f };
void updateViewViewport(const sf::RenderWindow&, sf::View&);

enum class GameState { Menu, Game, GameMenu, CustomizeMenu, LoginScreen, GameOver};

std::string buttText = "assets/img/button.png";
sf::Texture logoText("assets/img/logo.png");
sf::Texture gameBG;
sf::Texture menuBG;
sf::Texture mirrorText;
sf::Texture chooseBGSText;
sf::Texture custShirtText;
sf::Texture custPantsText;
sf::Texture custShoesText;
sf::Texture custClothesBGText("assets/img/clothesBG.png");
sf::Texture colorSelectBGText("assets/img/colorSelectBG.png");
sf::RectangleShape logicalBackground(mainWin);
sf::Font font;
sf::RectangleShape mirror;
sf::RectangleShape chooseBGS;
std::string fontS = "assets/fonts/KiwiSoda.ttf";

sf::RectangleShape logo({645, 239});
Button playButton({ 228.f, 95.f }, { 273.f, 250.f }, sf::Color(96, 178, 37), sf::Color(109, 204, 42), buttText, "START", fontS, 32);
Button customButton({ 228.f, 95.f }, { 273.f, 360.f }, sf::Color(186, 175, 15), sf::Color(237, 224, 33), buttText, "POSTAC", fontS, 32);
Button exitButton({ 228.f, 95.f }, { 273.f, 470.f }, sf::Color(178, 37, 37), sf::Color(204, 42, 42), buttText, "WYJSCIE", fontS, 32);

sf::Vector2f enemyBasePos = sf::Vector2f({ 50.0, 215.0 });
sf::Vector2f playerBasePos = sf::Vector2f({ 750.0, 215.0 });

charLook playerChar = loadCharacterFromFile();
charSprite playerSP(playerBasePos, playerChar);

chooseDisp customHairDisp({490.f, 90.f}, 0, 0);
chooseDisp customHatDisp({ 308.f, 6.f }, 1, 0);
chooseDisp customFaceDisp({ 300.f, 162.f }, 2, 0);

std::string arrR = "assets/img/arrRight.png";
std::string arrL = "assets/img/arrLeft.png";
std::string colSelPath = "assets/img/colorSelect.png";
std::string colSelBPath = "assets/img/colorSelectBlank.png";

Button customHairRight({ 45.f, 39.f }, {722.f, 154.f}, sf::Color(230, 230, 230), sf::Color::White, arrR);
Button customHairLeft({ 46.f, 40.f }, {480.f, 151.f}, sf::Color(230, 230, 230), sf::Color::White, arrL);
Button customHairColor({72.f, 67.f}, {686, 207}, sf::Color(200, 200, 200), sf::Color::White, colSelPath);

Button customHatRight({ 45.f, 39.f }, {540.f, 60.f}, sf::Color(230, 230, 230), sf::Color::White, arrR);
Button customHatLeft({ 46.f, 40.f }, {298.f, 57.f}, sf::Color(230, 230, 230), sf::Color::White, arrL);

Button customFaceRight({ 45.f, 39.f }, {544.f, 277.f}, sf::Color(230, 230, 230), sf::Color::White, arrR);
Button customFaceLeft({ 46.f, 40.f }, {302.f, 274.f}, sf::Color(230, 230, 230), sf::Color::White, arrL);
Button customSkinColor({ 72.f, 67.f }, { 510, 330 }, sf::Color(200, 200, 200), sf::Color::White, colSelPath);

Button customShirtColorButt({ 72.f, 67.f }, { 646, 496 }, sf::Color(200, 200, 200), sf::Color::White, colSelPath);
Button customPantsColorButt({ 72.f, 67.f }, { 470, 496 }, sf::Color(200, 200, 200), sf::Color::White, colSelPath);
Button customShoesColorButt({ 72.f, 67.f }, { 282, 496 }, sf::Color(200, 200, 200), sf::Color::White, colSelPath);

sf::RectangleShape customClothesBG({474, 122});
sf::RectangleShape customShoesColor({150, 52});
sf::RectangleShape customPantsColor({140, 63});
sf::RectangleShape customShirtColor({ 106, 86 });

sf::RectangleShape colorSelectBG({799, 422});
colorSelectScreen clothesColorSelect(clothesPalette, 0, 24);

Button diceLook({ 57.f, 49.f }, { 148, 41 }, sf::Color(230, 230, 230), sf::Color::White, "assets/img/dice.png");




std::random_device rd;
std::mt19937 gen(rd());

charLook enemyChar = randomChar();
charSprite enemySP(enemyBasePos, enemyChar);

std::vector <sf::Color> chooseColorScreen[24];

struct GameStart {
    sf::Vector2f velocity = { 0.f, 0.f };

    float up = 0.0f;
    float left = 0.0f;

    bool isCharging = false;
    bool isFlying = false;

    float maxCharge = 800.0f;

    float bot_ball_x = 100.f;
    float ball_x = 658.f;
    float ball_y = 400.f;

    bool turn = false;

    bool hasHit = false;
    bool hitEvent = false;

    sf::Vector2f initialVelocity;

    int myDrink = 0;
    int enemyDrink = 0;
    bool isSpaceActive = false;

    float graczX = 750.f;
    float graczY = 415.f;
    float botX   = 50.f;
    float botY   = 415.f;

    bool graczBiegnie = false;
    bool botBiegnie   = false;


    bool B_byl_wcisniety = false;
    bool gracz_podniosl  = false;

    bool graczWraca = false;
    bool botWraca   = false;

    float graczHomeX = 750.f;
    float botHomeX   = 50.f;

    float botRunSpeed = 1.f;
    bool graczPije = false;
    bool botPije   = false;

    float botDrinkAcc = 0.f;

    bool spaceHeld = false; 
    int scorePlayer = 0;
    int scoreBot = 0;
    int round = 1;          // zamiast level jak wolisz

    bool graczFacingRight = true;
};

void logic(GameState &currentState, GameStart &game, canSprite &ball, middleCanSprite &can, float ramp_up, canSprite &ball2, float gravity,
    float dt, sf::Sound &sound, fillPiwa &visBar, int &level, sf::Text &levelDisplay, fillPiwa& visEnemyBar);

void odbicie(canSprite &ball, float pozycja_x, GameStart &game, float dt, middleCanSprite&can, sf::Sound &sound);

void rzutBot(middleCanSprite &can, canSprite &ball2, float gravity, GameStart &game, int& level);

void rzutGracz(GameStart &game, float ramp_up);

void bounce(canSprite &ball, middleCanSprite&can, GameStart &game, sf::Sound &sound);

void groundReset(canSprite &ball, GameStart &game, float ball_x);

void drawGame(GameState currentState, Button &playButton, sf::RenderWindow &window, Button &exitButton, canSprite &ball, middleCanSprite &can, canSprite &ball2, GameStart &game, sf::Text &aim, sf::Text &move, sf::Text &drink, ramkaPiwa &drinkBar, fillPiwa &visBar, sf::Text &levelDisplay, ramkaPiwa& enemyBar, fillPiwa& visEnemyBar, sf::Text scoreText, sf::Text roundText);

void drawBars(GameStart &game, canSprite &ball, sf::RenderWindow &window);

void drawPowerbar(GameStart &game, canSprite &ball, sf::RenderWindow &window, float direction_up, float direction_left);

void handleMenu(const std::optional<sf::Event> &event, Button &playButton, sf::Vector2f &mousePos, GameState &currentState, Button &exitButton, sf::RenderWindow &window);

void eventLoop(const std::optional<sf::Event> &event, sf::RenderWindow &window, sf::View &view, GameState &currentState, Button &playButton, sf::Vector2f &mousePos, Button &exitButton);

void drinkCounter(GameStart& game, fillPiwa &visBar);

void drinkCounterEnemy(GameStart& game, fillPiwa &visEnemyBar);

int main()
{   

    GameStart game;
    playerSP.flip(-1), game.graczFacingRight = false;
    logo.setTexture(&logoText);
    logo.setOrigin(logo.getGeometricCenter());
    logo.setPosition(logo.getGeometricCenter() + sf::Vector2f(87.f, 17.f));
    

    customHairDisp.setPartID(playerChar.hairID);
    customHatDisp.setPartID(playerChar.hatID);
    customFaceDisp.setPartID(playerChar.faceID);
    customHairDisp.setColor(playerChar.hairColor);
    customFaceDisp.setColor(playerChar.skinColor);
    customShoesColor.setFillColor(playerChar.shoeColor);
    customPantsColor.setFillColor(playerChar.pantsColor);
    customShirtColor.setFillColor(playerChar.topColor);


    //  Rozmiar okna, resize
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Flanki");
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect({ 0.f, 0.f }, mainWin));
    view.setCenter(sf::Vector2f(mainWin.x / 2.f, mainWin.y / 2.f));
    updateViewViewport(window, view);
    window.setView(view);
    // menu logowania:
        
    // fonty
    sf::Font font;
    if (!font.openFromFile("assets/fonts/KiwiSoda.ttf")) return -1;

    sf::Font textFont;
    if (!textFont.openFromFile("assets/fonts/KOMIKAX_.ttf")) return -1;

    LoginPanelSFML login(window, font);
    std::string loggedUser;

    GameState currentState = GameState::LoginScreen;

    // stan gry (menu czy gra)
    // GameState currentState = GameState::Menu;

    // Assety

    // puszka piwa i jej wypełnienie:
    sf::Texture barFillTex;
    sf::Texture barOutlineTex;

    if (!barFillTex.loadFromFile("assets/img/bar/barfill.png")) return -1;
    if (!barOutlineTex.loadFromFile("assets/img/bar/baroutline.png")) return -1;

    
    // dzwiek
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("assets/music/clank.mp3")) return -1;
    
    // Przyciski 
    sf::Clock keyTimer;
    // Button playButton({ 254.f, 104.f }, { 273.f, 260.f }, sf::Color(96, 178, 37), sf::Color(109, 204, 42), "START", font, 30, buttText);
    // Button customButton({254.f, 104.f}, { 273.f, 400.f }, sf::Color(100, 100, 100), sf::Color(150, 150, 150), "CUSTOM", font, 30, buttText);
    // Button exitButton({ 254.f, 104.f }, { 273.f, 540.f }, sf::Color(178, 37, 37), sf::Color(204, 42, 42), "WYJSCIE", font, 30, buttText);


    // Tło
    //if (!mainMenuBG.loadFromFile("assets/img/mainmenu.png")) return -1;
    if (!gameBG.loadFromFile("assets/img/gamebg.png")) return -1;
    if (!menuBG.loadFromFile("assets/img/brickbg.png")) return -1;
    if (!mirrorText.loadFromFile("assets/img/mirror.png")) return -1;
    if (!chooseBGSText.loadFromFile("assets/img/chooseBGS.png")) return -1;
    if (!custShirtText.loadFromFile("assets/img/customShirt.png")) return -1;
    if (!custPantsText.loadFromFile("assets/img/customPants.png")) return -1;
    if (!custShoesText.loadFromFile("assets/img/customShoes.png")) return -1;

    logicalBackground.setPosition({ 0.f, 0.f });
    logicalBackground.setTexture(&menuBG);

    mirror.setTexture(&mirrorText);
    mirror.setSize({275.f, 421.f});
    mirror.setPosition({39.f, 95.f});
    chooseBGS.setTexture(&chooseBGSText);
    chooseBGS.setSize({408.f, 360.f});
    chooseBGS.setPosition({ 328.f, 6.f });

    customClothesBG.setTexture(&custClothesBGText);
    customClothesBG.setPosition({322, 400});

    customShirtColor.setTexture(&custShirtText);
    customShirtColor.setPosition({665, 421});

    customPantsColor.setTexture(&custPantsText);
    customPantsColor.setPosition({496, 441});

    customShoesColor.setTexture(&custShoesText);
    customShoesColor.setPosition({321, 451});

    colorSelectBG.setTexture(&colorSelectBGText);
    colorSelectBG.setPosition({ 0, 106 });

    // Obiekty - puszki
    /*sf::CircleShape can(15.f);
    can.setFillColor(sf::Color::Yellow);
    can.setPosition({ 400.f, 550.f });*/

    middleCanSprite can({ 400.f, 500.f + 74.f });
    can.setPosition({ 400.f, 500.f + 74.f });

    canSprite ball({game.ball_x, game.ball_y}, sf::Color::Blue);
    ball.setPosition({ game.ball_x, game.ball_y });
    canSprite ball2({ game.bot_ball_x, game.ball_y}, sf::Color::Red);
    ball2.setPosition({ game.bot_ball_x, game.ball_y });


    //powerBar barLeft({});

    sf::Sound sound(buffer);

    // Punkty
    sf::Text scoreText(font, "", 18);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({20.f, 20.f});

    sf::Text roundText(font, "", 30);
    roundText.setFillColor(sf::Color::White);
    roundText.setOutlineColor(sf::Color::Black);
    roundText.setOutlineThickness(2.0f);
    roundText.setPosition({220.f, 500.f});
    
    
    sf::Text aim(textFont, "Celowanie - Strzalki(Gora/Lewo) \n Klikanie Spacji po trafieniu uzupelnia pasek \nJak trafi przeciwnik to klikanie spacji by biec\n A przy puszcze kliknac 'b' zeby podniesc");
    aim.setCharacterSize(15);
    aim.setStyle(sf::Text::Bold);
    aim.setFillColor(sf::Color::White);
    aim.setOutlineColor(sf::Color::Black);
    aim.setPosition({ 200, 50});
    aim.setOutlineThickness(2.0f);

    sf::Text drink(textFont, "");
    drink.setCharacterSize(15);
    drink.setStyle(sf::Text::Bold);
    drink.setFillColor(sf::Color::Red);
    drink.setPosition({ 400, 80});

    sf::Text move(textFont, "");
    move.setCharacterSize(15);
    move.setStyle(sf::Text::Bold);
    move.setFillColor(sf::Color::Red);
    move.setPosition({ 400, 110 });

    // piwo gracza
    ramkaPiwa drinkBar(barOutlineTex);
    drinkBar.setPosition({684, 220});
    
    fillPiwa visBar(barFillTex, 75);
    visBar.setPosition({690, 220});

    // piwo enemy
    ramkaPiwa enemyBar(barOutlineTex);
    enemyBar.setPosition({4, 220});

    fillPiwa visEnemyBar(barFillTex, 30);
    visEnemyBar.setPosition({10, 220});

    int level = 1;
    //char levelChar = '1';
    sf::Text levelDisplay(font, std::to_string(level));
    levelDisplay.setCharacterSize(0);
    levelDisplay.setStyle(sf::Text::Bold);
    levelDisplay.setFillColor(sf::Color::Red);
    levelDisplay.setPosition({ 300, 110 });

    // fizyka i czas
    float gravity = 980.f;
    sf::Clock clock;
    float totalTime = 0;


while (window.isOpen())
{
    // ===== CZAS =====
    float dt = clock.restart().asSeconds();
    totalTime += dt;

    // ===== ANIMACJE UI =====
    float scaleX = 1.f + 0.07f * std::sin(totalTime * 2.f);
    float scaleY = 1.f + 0.07f * std::cos(totalTime * 2.f);
    logo.setScale({ scaleX, scaleY });

    // ===== MYSZ =====
    sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosUI = window.mapPixelToCoords(mousePosI);
    sf::Vector2f mousePos   = window.mapPixelToCoords(mousePosI, view);

    float ramp_up = 250.f * dt * 2.f;

    // ===== EVENTY =====
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (currentState == GameState::LoginScreen)
        {
            login.handleEvent(*event);
        }
        else
        {
            eventLoop(event, window, view, currentState,
                      playButton, mousePosUI, exitButton);
        }
    }

    // ===== LOGIKA =====
    if (currentState == GameState::Game)
    {
        logicalBackground.setTexture(&gameBG);

        logic(currentState, game, ball, can, ramp_up, ball2,
              gravity, dt, sound, visBar,
              level, levelDisplay, visEnemyBar);

        scoreText.setString(
            "Gracz: " + std::to_string(game.scorePlayer) +
            "\tBot: " + std::to_string(game.scoreBot)
        );
        roundText.setString("Runda: " + std::to_string(game.round));
    }
    else
    {
        logicalBackground.setTexture(&menuBG);
    }

    // ===== RYSOWANIE (ZAWSZE) =====
    window.clear(sf::Color::Black);
    window.setView(view);
    window.draw(logicalBackground);

    if (currentState == GameState::LoginScreen)
    {
        login.draw();

        if (login.skonczono())
        {
            loggedUser = login.UstawGracza();
            currentState = GameState::Menu;
        }
    }
    else
    {
        drawGame(currentState, playButton, window, exitButton,
                 ball, can, ball2, game,
                 aim, move, drink,
                 drinkBar, visBar,
                 levelDisplay,
                 enemyBar, visEnemyBar,
                 scoreText, roundText);
    }

    window.display();
}
}
void eventLoop(const std::optional<sf::Event> &event, sf::RenderWindow &window, sf::View &view, GameState &currentState, Button &playButton, sf::Vector2f &mousePos, Button &exitButton){

    // 1.1 zamknięcie
    if (event->is<sf::Event::Closed>())
        window.close();

    // 1.2 resize okna
    else if (const auto *resized = event->getIf<sf::Event::Resized>())
    {
        updateViewViewport(window, view);
        view.setSize(mainWin);
        view.setCenter({mainWin.x / 2.f, mainWin.y / 2.f});
        window.setView(view);
    }
    
    // login panel 1.25
    // loginPanel.handleEvent(event);

    // if (loginPanel.isFinished()) {
    //     currentState = GameState::Menu;
    // }

    // 1.3 menu
    else if (currentState == GameState::Menu || currentState == GameState::CustomizeMenu )
    {   
        handleMenu(event, playButton, mousePos, currentState, exitButton, window);
    }
}

void handleMenu(const std::optional<sf::Event> &event, Button &playButton, sf::Vector2f &mousePos, GameState &currentState, Button &exitButton, sf::RenderWindow &window)
{
    if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
    {
        if (keyEvent->scancode == sf::Keyboard::Scancode::Escape)
        {
            if (currentState == GameState::CustomizeMenu)
            {
                if (activeColorMode != 0) {
                    activeColorMode = 0;
                }
                else {
                    currentState = GameState::Menu;
                }
            }
        }
    }
    if (playButton.isMouseOver(mousePos)) {
        playButton.hover();
    }
    else {
        playButton.unhover();
    }
    if (exitButton.isMouseOver(mousePos)) {
        exitButton.hover();
    }
    else {
        exitButton.unhover();
    }


    diceLook.isMouseOver(mousePos) ? diceLook.hover() : diceLook.unhover();

    customHairRight.isMouseOver(mousePos) ? customHairRight.hover() : customHairRight.unhover();
    customHairLeft.isMouseOver(mousePos) ? customHairLeft.hover() : customHairLeft.unhover();

    customHatRight.isMouseOver(mousePos) ? customHatRight.hover() : customHatRight.unhover();
    customHatLeft.isMouseOver(mousePos) ? customHatLeft.hover() : customHatLeft.unhover();

    customFaceRight.isMouseOver(mousePos) ? customFaceRight.hover() : customFaceRight.unhover();
    customFaceLeft.isMouseOver(mousePos) ? customFaceLeft.hover() : customFaceLeft.unhover();

    customHairColor.isMouseOver(mousePos) ? customHairColor.hover() : customHairColor.unhover();

    customSkinColor.isMouseOver(mousePos) ? customSkinColor.hover() : customSkinColor.unhover();
    customShirtColorButt.isMouseOver(mousePos) ? customShirtColorButt.hover() : customShirtColorButt.unhover();
    customPantsColorButt.isMouseOver(mousePos) ? customPantsColorButt.hover() : customPantsColorButt.unhover();
    customShoesColorButt.isMouseOver(mousePos) ? customShoesColorButt.hover() : customShoesColorButt.unhover();


    if (activeColorMode != 0) {
        clothesColorSelect.update(mousePos);
    }

    if (customButton.isMouseOver(mousePos)) customButton.hover();
    else customButton.unhover();
    if (const auto *mouseEvent = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseEvent->button == sf::Mouse::Button::Left)
        {
            if (currentState == GameState::Menu) {
                if (playButton.isMouseOver(mousePos))
                {
                    playerSP.flip(-1);
                    currentState = GameState::Game;
                }
                else if (customButton.isMouseOver(mousePos)) {
                    currentState = GameState::CustomizeMenu;
                    logicalBackground.setTexture(&menuBG);
                } else if (exitButton.isMouseOver(mousePos)) window.close();
            }
            if (currentState == GameState::CustomizeMenu) {
                saveCharacterToFile(playerChar);
                if (activeColorMode != 0) {

                    std::optional<sf::Color> pickedColor = clothesColorSelect.getClickedColor(mousePos);

                    if (pickedColor.has_value()) {
                        sf::Color col = pickedColor.value();

                        switch (activeColorMode) {
                            case 1: playerChar.hairColor = col; customHairDisp.setColor(col); break;
                            case 2: playerChar.skinColor = col; customFaceDisp.setColor(col); break;
                            case 3: playerChar.topColor = col; customShirtColor.setFillColor(col); break;
                            case 4: playerChar.pantsColor = col; customPantsColor.setFillColor(col); break;
                            case 5: playerChar.shoeColor = col; customShoesColor.setFillColor(col); break;
                        }

                        playerSP.changeLook(playerChar);
                    }
                }
                else {
                    if (diceLook.isMouseOver(mousePos)) {
                        playerChar = randomChar();
                        customHairDisp.setPartID(playerChar.hairID);
                        customHairDisp.setColor(playerChar.hairColor);
                        customHatDisp.setPartID(playerChar.hatID);
                        customFaceDisp.setPartID(playerChar.faceID);
                        customFaceDisp.setColor(playerChar.skinColor);
                        customShirtColor.setFillColor(playerChar.topColor);
                        customPantsColor.setFillColor(playerChar.pantsColor);
                        customShoesColor.setFillColor(playerChar.shoeColor);
                        playerSP.changeLook(playerChar);
                    };
                    if (customHairRight.isMouseOver(mousePos)) {
                        customHairDisp.pIDstep(1);
                        playerChar.hairID = customHairDisp.partID;
                        playerSP.changeLook(playerChar);
                    };
                    if (customHairLeft.isMouseOver(mousePos)) {
                        customHairDisp.pIDstep(-1);
                        playerChar.hairID = customHairDisp.partID;
                        playerSP.changeLook(playerChar);
                    }

                    if (customHatRight.isMouseOver(mousePos)) {
                        customHatDisp.pIDstep(1);
                        playerChar.hatID = customHatDisp.partID;
                        playerSP.changeLook(playerChar);
                    }
                    if (customHatLeft.isMouseOver(mousePos)) {
                        customHatDisp.pIDstep(-1);
                        playerChar.hatID = customHatDisp.partID;
                        playerSP.changeLook(playerChar);
                    }

                    if (customFaceRight.isMouseOver(mousePos)) {
                        customFaceDisp.pIDstep(1);
                        playerChar.faceID = customFaceDisp.partID;
                        playerSP.changeLook(playerChar);
                    }
                    if (customFaceLeft.isMouseOver(mousePos)) {
                        customFaceDisp.pIDstep(-1);
                        playerChar.faceID = customFaceDisp.partID;
                        playerSP.changeLook(playerChar);
                    }

                    if (customHairColor.isMouseOver(mousePos)) {
                        activeColorMode = 1;

                        std::vector<sf::Color> mixedPalette;
                        for (const auto& color : hairPalette) {
                            mixedPalette.push_back(color);
                        }
                        int clothesSize = sizeof(clothesPalette) / sizeof(clothesPalette[0]);

                        for (int i = 16; i < clothesSize; ++i) {
                            mixedPalette.push_back(clothesPalette[i]);
                        }
                        clothesColorSelect.setup(mixedPalette.data(), mixedPalette.size());
                    }

                    else if (customSkinColor.isMouseOver(mousePos)) {
                        activeColorMode = 2;
                        clothesColorSelect.setup(skinPalette, 4);
                    }

                    else if (customShirtColorButt.isMouseOver(mousePos)) {
                        activeColorMode = 3;
                        clothesColorSelect.setup(clothesPalette, 24);
                    }

                    else if (customPantsColorButt.isMouseOver(mousePos)) {
                        activeColorMode = 4;
                        clothesColorSelect.setup(clothesPalette, 24);
                    }

                    else if (customShoesColorButt.isMouseOver(mousePos)) {
                        activeColorMode = 5;
                        clothesColorSelect.setup(clothesPalette, 24);
                    }
                }
            }
        }
    }
}

void logic(GameState &currentState, GameStart &game,
           canSprite &ball, middleCanSprite &can,
           float ramp_up, canSprite &ball2,
           float gravity, float dt, sf::Sound &sound,
           fillPiwa &visBar, int &level, sf::Text &levelDisplay,
           fillPiwa &visEnemyBar) 
{
    if (currentState != GameState::Game) return;
    const int   DRINK_MAX         = 30;
    const float MID_OFFSET        = 60.f;   // żeby nie wchodzili w puszkę
    const float PLAYER_RUN_STEP   = 10.f;   // px na jedno kliknięcie spacji
    const float BOT_SPEED_BASE    = 90.f;   // px/s (bazowo wolniej)
    const float BOT_DRINK_INTERVAL= 0.45f;  // sekundy na 1 "łyk" (wolno)

    const float midX = can.getPosition().x;
    const float midPlayerX = midX + MID_OFFSET;
    const float midBotX    = midX - MID_OFFSET;

    // klik
    const bool spaceDown    = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space);
    const bool spacePressed = spaceDown && !game.spaceHeld;
    game.spaceHeld = spaceDown;
    visBar.removeOffset(); // naprawia bug związany z wychodzeniem piwa 
    visEnemyBar.removeOffset(); // z ramki przy restarcie
    auto resetRound = [&]() {
        const int keepP = game.scorePlayer;
        const int keepB = game.scoreBot;
        const int keepR = game.round;

        game = GameStart();
        game.scorePlayer = keepP;
        game.scoreBot    = keepB;
        game.round       = keepR;
        
        enemySP.changeLook(randomChar());
        float BOTTOM_OFFSET = 8.f;
        visBar.addOffset(); // naprawia bug związany z polozeniem fillu przy restarcie
        visEnemyBar.addOffset();
        visBar.setPosition({690, 220}); // restart poziomu piwa
        visEnemyBar.setPosition({10, 220}); // przy escape
        visBar.setValue(0);
        visEnemyBar.setValue(0);
        ball.setPosition({game.ball_x, game.ball_y});
        ball2.setPosition({game.bot_ball_x, game.ball_y});
        
        playerSP.setPos(game.graczX, game.graczY);
        playerSP.flip(-1);
        enemySP.setPos(game.botX, game.botY);
        enemySP.flip(1);
        can.standUp();
    };

    // ESC: reset do menu
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) {
        if (currentState == GameState::Game) {
            logicalBackground.setTexture(&menuBG);
            currentState = GameState::Menu;
            resetRound();
        }
        return;
    }

    // ===== 1 RZUT / ŁADOWANIE =====
    if (!game.isFlying && !game.graczBiegnie && !game.botBiegnie && !game.graczPije && !game.botPije)
    {
        if (!game.turn) { 

            ball.setPosition({ game.ball_x, game.ball_y });
            
            rzutGracz(game, ramp_up);
        }
        else
        {
            ball2.setPosition({ game.bot_ball_x, game.ball_y });
            rzutBot(can, ball2, gravity, game, level);
        }
    }

    // ===== 2 LOT =====
    if (game.isFlying)
    {
        game.velocity.y += gravity * dt;

        if (!game.turn) odbicie(ball,  game.ball_x,     game, dt, can, sound);
        else            odbicie(ball2, game.bot_ball_x, game, dt, can, sound);

        // event trafienia przychodzi z bounce
        if (game.hitEvent)
        {

            if (!game.turn) {
                game.botBiegnie = true;
                game.botWraca = false;

                game.botRunSpeed = 0.7f + static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 0.5f; // 0.7–1.2

                game.graczPije = true;
                game.botPije = false;
                can.rotateLeft();
            } else {
                game.graczBiegnie = true;
                game.graczWraca = false;

                game.botPije = true;
                game.graczPije = false;
                game.botDrinkAcc = 0.f;
                can.rotateRight();
            }

            game.hitEvent = false; // zużyte
        }
    }

    // ===== 3 RUCH PO TRAFIENIU =====
    // podniesienie puszki:
    if (fabs(game.graczX - can.getPosition().x) < 150) {
        bool B_jest_wcisniety = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::B);
        bool B_zostal_nacisniety = B_jest_wcisniety && !game.B_byl_wcisniety;
        game.B_byl_wcisniety = B_jest_wcisniety;

        if (B_zostal_nacisniety) {
            game.gracz_podniosl = true;
            can.standUp();
        }
    }

    // gracz bieg
    if (game.graczBiegnie && spacePressed)
    {
        const float targetX = game.graczWraca ? game.graczHomeX : midPlayerX;
        const float dir     = (targetX > game.graczX) ? 1.f : -1.f;
        game.graczX += dir * PLAYER_RUN_STEP * 2;
        
        const bool reached =
            (dir > 0.f && game.graczX >= targetX) ||
            (dir < 0.f && game.graczX <= targetX);

    
        if (reached && game.gracz_podniosl) {
            game.gracz_podniosl = false;   
            game.graczX = targetX;


            if (!game.graczWraca) {
                playerSP.flip(1);
                game.graczWraca = true;
                game.gracz_podniosl = true;
                //can.rotate();
            } else {
                playerSP.flip();
                game.graczWraca   = false;
                game.graczBiegnie = false;
                game.botPije      = false;
            }
        }
    }

    // bot bieg
    if (game.botBiegnie)
    {
        const float targetX = game.botWraca ? game.botHomeX : midBotX;
        const float dir     = (targetX > game.botX) ? 1.f : -1.f;

        const float v = BOT_SPEED_BASE * game.botRunSpeed;
        if (game.round < 7) {
            game.botX += dir * v * dt * ((game.round / 10.f) + 1.2);
            //std::cout << (game.round / 10.f) + 1.2 << std::endl;
        }
        else {
            game.botX += dir * v * dt * 2;
        }
        


        const bool reached =
            (dir > 0.f && game.botX >= targetX) ||
            (dir < 0.f && game.botX <= targetX);

        if (reached) {
            game.botX = targetX;

            if (!game.botWraca) 
            {
                game.botWraca = true;
                enemySP.flip();
                //can.rotate2();
                can.standUp();
            }
            else {
                enemySP.flip();
                game.botWraca   = false;
                game.botBiegnie = false;
                game.graczPije  = false;
            }
        }
    }

    // sync spriteów
    playerSP.setPos(game.graczX, game.graczY);
    enemySP.setPos(game.botX,   game.botY);

    // ===== 4 PICIE =====
    if (game.graczPije && spacePressed) {
        drinkCounter(game, visBar);
    }

    if (game.botPije) {
        game.botDrinkAcc += dt;
        if (game.botDrinkAcc >= BOT_DRINK_INTERVAL) {
            drinkCounterEnemy(game, visEnemyBar);
            game.botDrinkAcc -= BOT_DRINK_INTERVAL;
        }
    }

    // ===== 5 PUNKTY =====
    if (game.enemyDrink >= 30) {
        game.scoreBot++;
        currentState = GameState::GameOver;
        // game.round++;
        
        //Jak bot wygra powinien byc koniec gry
        resetRound();
    }
    else if (game.myDrink >= 75) {
        game.scorePlayer++;
        game.round++;
        enemySP.changeLook(randomChar());
        resetRound();
    }
}

void odbicie(canSprite &ball, float pozycja_x, GameStart &game, float dt, middleCanSprite&can, sf::Sound &sound)
{
    ball.move(game.velocity * dt);        // ruch puszki
    bounce(ball, can, game, sound);       // odbicie
    groundReset(ball, game, pozycja_x); // reset po odbiciu

}
std::clock_t start_bot_delay = 0;

void rzutBot(middleCanSprite&can, canSprite &ball2, float gravity, GameStart &game, int &level)
{

    
    if (!start_bot_delay)
        start_bot_delay = clock();

    std::uniform_real_distribution<> dis(185.0f, 800.0f);
    
    float margin;
    float margin_x;
    if (game.round < 7)
    {
        std::uniform_real_distribution<> dis2(-200.0f + (10 * game.round), 200.0f - (10 * game.round));
        std::uniform_real_distribution<> dis3(-125.0f, 125.0f);
        margin = dis2(gen);
        margin_x = dis3(gen);
    }
    else {
        std::uniform_real_distribution<> dis2(-100.0f , 100.0f );
        std::uniform_real_distribution<> dis3(-50.0f, 50.0f);
        margin = dis2(gen);
        margin_x = dis3(gen);
    }

    float random_x = dis(gen);
    
    // Flight trajectory math
    //  t = Distance/Vx
    // Height = (Vy​*t)−(1/2​*Gravity*t^2)
    // Vy = ((Gravity*Distance) / (2*Vx)) + (Height * Vx / Distance)

    // Distance ball2 from can

    // x axis
    float distance = std::abs(can.getPosition().x - ball2.getPosition().x);

    // y axis
    float height = can.getPosition().y - ball2.getPosition().y;

    // Velocityx * Velocityy = gravity*distance / 2
    float physicsConstant = (gravity * distance) / 2.0f;

    // Veloicty = gravity * distance /2 / velocityx - ((height * random_x)/ distance) (- because y axis in sfml upside down)
    float random_y = (physicsConstant / random_x) - ((height * random_x) / distance);

    std::clock_t delay = std::clock() - start_bot_delay;
    if (delay > 1000 - std::max(game.round*50, 600)) {
        //std::cout << random_x << ' ' << random_y << std::endl;

        game.velocity = sf::Vector2f(random_x + margin_x, -(margin + random_y));
    /*    std::cout << "margin" << margin << std::endl;*/
        game.initialVelocity = game.velocity;
        game.hasHit = false;

        game.isFlying = true;
        start_bot_delay = 0;
    }
 
}

void rzutGracz(GameStart &game, float ramp_up)
{

    bool chargingUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up);
    bool chargingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left);

    // Ładowanie do rzutu
    if (chargingUp || chargingLeft)
    {
        game.isCharging = true;
        // Charging until max
        if (chargingUp)
            game.up += ramp_up;
        if (chargingLeft)
            game.left += ramp_up;

        // If charged to max:

        // Cap at max

        /*if (game.up > game.maxCharge) game.up = game.maxCharge;
        if (game.left > game.maxCharge) game.left = game.maxCharge;*/

        // Reset bar
        if (game.up > game.maxCharge)
            game.up = 0.0f;
        if (game.left > game.maxCharge)
            game.left = 0.0f;
    }
    // Rzut
    else if (game.isCharging)
    {
        game.isCharging = false;
        game.isFlying = true;
        game.velocity = sf::Vector2f(-game.left, -game.up);
        game.initialVelocity = game.velocity;
        game.hasHit = false;
        game.up = 0.0f;
        game.left = 0.0f;
    }
}

void bounce(canSprite &ball, middleCanSprite&can, GameStart &game, sf::Sound &sound)
{
    if (ball.getGlobalBounds().findIntersection(can.getGlobalBounds()) && !game.hasHit)
    {
        //game.velocity.x = -game.velocity.x * 0.1;
        game.velocity.y = -100.f;
        game.velocity.x = - (can.getPosition().x - ball.getPosition().x) * 3;
        

        //can.setFillColor(sf::Color::Magenta);

        game.hasHit   = true;   // blokada na resztę lotu
        game.hitEvent = true;   // JEDNORAZOWY event do logic()
    }
}

void drinkCounter(GameStart& game, fillPiwa& visBar)
{
    constexpr int DRINK_MAX = 75;
    if (game.myDrink >= DRINK_MAX) return;

    game.myDrink++;
    visBar.setValue(game.myDrink);
}
void drinkCounterEnemy(GameStart& game, fillPiwa& visEnemyBar)
{
    constexpr int DRINK_MAX = 30;
    if (game.enemyDrink >= DRINK_MAX) return;

    game.enemyDrink++;
    visEnemyBar.setValue(game.enemyDrink);
}

void groundReset(canSprite &ball, GameStart &game, float ball_x)
{

    std::uniform_real_distribution<> dis3(555.0f, 570.0f);
    float rand = dis3(gen);
    if (ball.getPosition().y > rand)
    {
        if (fabs(ball.getPosition().x - 400.f) > 115) {

            game.isFlying = false;
            game.velocity = { 0.f, 0.f };
            //ball.setPosition({ ball_x, game.ball_y });
        }
        else {
            game.isFlying = false;
            game.velocity = { 0.f, 0.f };
            ball.setPosition({ball_x, game.ball_y});

        }
        
        game.turn = !game.turn; 
    }

}

void drawGame(GameState currentState, Button& playButton, sf::RenderWindow& window,
    Button& exitButton, canSprite& ball, middleCanSprite& can,
    canSprite& ball2, GameStart& game,
    sf::Text& aim, sf::Text& move, sf::Text& drink, ramkaPiwa &drinkBar, fillPiwa &visBar, sf::Text &levelDisplay, ramkaPiwa& enemyBar, fillPiwa& visEnemyBar, sf::Text scoreText, sf::Text roundText)
{
    if (currentState == GameState::Menu)
    {
        window.draw(logo);
        playButton.draw(window);
        customButton.draw(window);
        exitButton.draw(window);
    }
    else if (currentState == GameState::CustomizeMenu) {
        playerSP.setPos(170.f, 300.f);
        if (playerSP.facing == -1) {
            playerSP.flip(1);
        }
        if (activeColorMode != 0) {
            window.draw(colorSelectBG);
            sf::Color bgColor;
            switch (activeColorMode) {
                case 1: 
                    bgColor = playerChar.hairColor;
                    break;
                case 2:
                    bgColor = playerChar.skinColor;
                    break;
                case 3:
                    bgColor = playerChar.topColor;
                    break;
                case 4:
                    bgColor = playerChar.pantsColor;
                    break;
                case 5:
                    bgColor = playerChar.shoeColor;
                    break;
            }
            colorSelectBG.setFillColor(bgColor);
            clothesColorSelect.draw(window);
        }
        else {
            window.draw(mirror);
            window.draw(chooseBGS);
            window.draw(customClothesBG);
            window.draw(customShirtColor);
            window.draw(customPantsColor);
            window.draw(customShoesColor);
            customShirtColorButt.draw(window);
            customPantsColorButt.draw(window);
            customShoesColorButt.draw(window);
            customHatDisp.draw(window);
            customHairDisp.draw(window);
            playerSP.draw(window);
            customFaceDisp.draw(window);
            customHairRight.draw(window);
            customHairLeft.draw(window);
            customHatRight.draw(window);
            customHatLeft.draw(window);
            customFaceRight.draw(window);
            customFaceLeft.draw(window);
            diceLook.draw(window);
            customHairColor.draw(window);
            customSkinColor.draw(window);
        }
    }
    else if (currentState == GameState::Game)
    {
        //window.draw(scoreText);
        window.draw(roundText);

        ball.draw(window);
        can.draw(window);
        ball2.draw(window);
        
        enemySP.draw(window);
        playerSP.draw(window);

        window.draw(aim);
        


        window.draw(visBar);
        window.draw(visEnemyBar);

        window.draw(drinkBar);
        window.draw(enemyBar);

        window.draw(levelDisplay);

        drawBars(game, ball, window);
    }

}

PowerBar powerBar;

void drawBars(GameStart &game, canSprite &ball, sf::RenderWindow &window)
{
    if (!game.isFlying && (game.up > 0.0f || game.left > 0.0f))
    {
        if (game.up > 0.0f) {
            powerBar.draw(window, ball.getPosition(), -90.f, game.up / 10.f, 10.f);
        }
        if (game.left > 0.0f) {
            powerBar.draw(window, ball.getPosition(), 180.f, game.left / 10.f, 10.f);
        }
    }
}
