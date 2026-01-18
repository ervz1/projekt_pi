#include <optional>
#include "LoginLogika.hpp"
#include "helper.hpp"

class LoginPanelSFML {
public:
    LoginPanelSFML(sf::RenderWindow& window, const sf::Font& font);

    void handleEvent(const sf::Event& event);
    void update(float dt);
    void draw();

    bool skonczono() const;
    const std::string& UstawGracza() const;

private:
    sf::RenderWindow& window;

    sf::Texture panelTexture;

    LoginState state = LoginState::EnterLogin;
    bool zalogowano = false;

    PamiecHasel storage;
    std::string Gracz;

    sf::RectangleShape panel;
    sf::Text infoText;
    sf::Text inputText;

    std::string inputBuffer;
    bool maskInput = false;

    Button confirmButton;

    void confirm();
    void updateTexts();
};


LoginPanelSFML::LoginPanelSFML(sf::RenderWindow& win, const sf::Font& font)
    :
     window(win), infoText(font, "", 40), inputText(font, "", 36),confirmButton(
    {228.f, 95.f},
    {286.f, 390.f},
    sf::Color(96,178,37),
    sf::Color(109,204,42),
    "assets/img/button.png",
    "Dalej",
    "assets/fonts/KiwiSoda.ttf",
    40
)
{
    //if (bgTexture.loadFromFile(
    //"assets/img/brickbg.png"))
    //{
    //    bgSprite.emplace(bgTexture);

    //    sf::Vector2u texSize = bgTexture.getSize();
    //    bgSprite->setScale(
    //        {800.f / texSize.x,
    //        600.f / texSize.y}
    //    );
    //}

    panelTexture.loadFromFile("assets/img/loginbg.png");
    panel.setSize({785.f, 497.f});
    //panel.setFillColor(sf::Color(30,30,30,220));
    //panel.setOutlineThickness(3.f);
    //panel.setOutlineColor(sf::Color::White);
    //panel.setOrigin(panel.getSize() / 2.f);
    panel.setTexture(&panelTexture);
    panel.setPosition({15.f, 71.f});
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition({130.f, 170.f});
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition({ 130.f, 260.f});
    updateTexts();
}


void LoginPanelSFML::handleEvent(const sf::Event& event) {
    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (confirmButton.isMouseOver(mouse))
        confirmButton.hover();
    else
        confirmButton.unhover();
    if (const auto* te = event.getIf<sf::Event::TextEntered>()) {
        if (te->unicode == '\r' || te->unicode == '\n')
        return;
    if (te->unicode == 8) {
        if (!inputBuffer.empty())
            inputBuffer.pop_back();
    }
    else if (te->unicode >= 32 && te->unicode < 127) {
        inputBuffer.push_back(static_cast<char>(te->unicode));
    }
    inputText.setString(maskInput ? std::string(inputBuffer.size(), '*') : inputBuffer);
    }



    if (const auto* kp = event.getIf<sf::Event::KeyPressed>()) {
    if (kp->code == sf::Keyboard::Key::Enter) {
        confirm();
    }
    else if (kp->code == sf::Keyboard::Key::Escape) {
        if (state != LoginState::EnterLogin) {
            state = LoginState::EnterLogin;
            inputBuffer.clear();
            updateTexts();
        }
    }
    }

    if (const auto* mp = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mp->button == sf::Mouse::Button::Left) {
            sf::Vector2f mouse = window.mapPixelToCoords(
                {mp->position.x, mp->position.y}
            );

            if (confirmButton.isMouseOver(mouse))
                confirm();
        }
    }
}

void LoginPanelSFML::confirm() {

if (state == LoginState::EnterLogin) {
    if (inputBuffer.empty()) {
        return;
    }

    Gracz = inputBuffer;
    inputBuffer.clear();

    state = storage.userExists(Gracz) ? LoginState::PodajHaslo : LoginState::StworzPaslo;
    updateTexts();
    return;
}

if (state == LoginState::PodajHaslo) {
    if (storage.checkPassword(Gracz, inputBuffer)) {
        zalogowano = true;
        state = LoginState::PrzejdzDalej;
    } else {
        infoText.setString("Bledne haslo. Sprobuj ponownie.");
    }

    inputBuffer.clear();
    inputText.setString("");
    return;
}

if (state == LoginState::StworzPaslo) {
    storage.stworzUzytkownika(Gracz, inputBuffer);
    inputBuffer.clear();
    state = LoginState::PodajHaslo;
    updateTexts();
    return;
}

}

void LoginPanelSFML::updateTexts() {

    inputBuffer.clear();
    inputText.setString("");

    if (state == LoginState::EnterLogin) {
        infoText.setString("Podaj login:");
        maskInput = false;
    }
    else if (state == LoginState::PodajHaslo) {
        infoText.setString("Witaj " + Gracz + ", podaj haslo");
        maskInput = true;
    }
    else {
        infoText.setString("Ustaw haslo dla " + Gracz);
        maskInput = true;
    }
}

void LoginPanelSFML::draw() {
    
    /*window.setView(window.getDefaultView());*/
    window.draw(panel);
    window.draw(infoText);
    window.draw(inputText);
    confirmButton.draw(window);
}
bool LoginPanelSFML::skonczono() const { return zalogowano; }
const std::string& LoginPanelSFML::UstawGracza() const { return Gracz; }


// test solo
// int main() {
//     sf::RenderWindow window(sf::VideoMode({800, 600}), "Login test");
//     sf::Font font;
//     font.openFromFile("assets/fonts/KiwiSoda.ttf");

//     LoginPanelSFML login(window, font);

//     while (window.isOpen()) {
//         while (auto ev = window.pollEvent()) {
//             if (ev->is<sf::Event::Closed>())
//                 window.close();

//             login.handleEvent(*ev);
//         }

//         window.clear();
        
//         login.draw();

//         window.display();

//         if (login.isFinished())
//             window.close();
//     }

//     return 0;
// }
