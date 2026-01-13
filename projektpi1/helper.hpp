#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include <iostream>
#pragma once
#include <cmath>
#include <sstream>
#include <iomanip>

// tu wszystkie funkcje i klasy

sf::Color clothesPalette[24] = {
    sf::Color(38,38,38),
    sf::Color(111, 21, 110),
    sf::Color(72, 21, 111),
    sf::Color(21, 65, 111),
    sf::Color(21, 111, 101),
    sf::Color(27, 111, 21),
    sf::Color(110, 111, 21),
    sf::Color(111, 27, 21),
    
    sf::Color(130, 130, 130),
    sf::Color(159, 9, 157),
    sf::Color(94, 9, 159),
    sf::Color(9, 82, 159),
    sf::Color(9, 159, 142),
    sf::Color(19, 159, 9),
    sf::Color(169, 172, 17),
    sf::Color(153, 24, 15),

    
    sf::Color(196, 196, 196),
    sf::Color(194, 91, 193),
    sf::Color(150, 91, 194),
    sf::Color(91, 141, 194),
    sf::Color(91, 194, 182),
    sf::Color(98, 194, 91),
    sf::Color(193, 194, 91),
    sf::Color(194, 98, 91)
};

sf::Color hairPalette[1] = {
    sf::Color(255, 255, 255)
};

sf::Color skinPalette[2] = {
    sf::Color(255,255,0),
    sf::Color(0, 255, 255)
};

struct spritePalette {
    sf::Color *clothes;
    sf::Color *hair;
    sf::Color *skin;
};  

spritePalette mainPalette = {
    clothesPalette,
    hairPalette,
    skinPalette
};


// charlook(int hatID, int hairID, int faceID, sfcolor topColor, sfcolor pantsColor, sfcolor shoeColor, sfcolor hairColor)
struct charLook {
    int hatID;
    int hairID;
    int faceID;
    sf::Color topColor;
    sf::Color pantsColor;
    sf::Color shoeColor;
    sf::Color hairColor;
};

static void updateViewViewport(const sf::RenderWindow& window, sf::View& view) {
    float winW = static_cast<float>(window.getSize().x);
    float winH = static_cast<float>(window.getSize().y);
    float targetW = mainWin.x;
    float targetH = mainWin.y;

    if (winW <= 0.f || winH <= 0.f) return;

    float scale = std::min(winW / targetW, winH / targetH);
    float viewportW = (targetW * scale) / winW;
    float viewportH = (targetH * scale) / winH;
    float viewportLeft = (1.f - viewportW) / 2.f;
    float viewportTop = (1.f - viewportH) / 2.f;

    view.setViewport(sf::FloatRect(sf::Vector2(viewportLeft, viewportTop), sf::Vector2(viewportW, viewportH)));
}

class canSprite {
public:
    canSprite(const sf::Vector2f& position, sf::Color color)
    : can({ 42.f, 29.f }),
    canBG({ 42.f, 29.f }) {
        canTxt.loadFromFile("assets/img/throwcantrace.png");
        can.setTexture(&canTxt);
        canBGTxt.loadFromFile("assets/img/throwcancolor.png");
        canBG.setTexture(&canBGTxt);
        canBG.setFillColor(color);
    }
    sf::Vector2f getPosition() {
        return can.getPosition();
    }

    sf::FloatRect getGlobalBounds() {
        return can.getGlobalBounds();
    }

    void setPosition(sf::Vector2f pos) {
        can.setPosition(pos);
        canBG.setPosition(pos);
    }
    void move(sf::Vector2f off) {
        can.move(off);
        canBG.move(off);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(can);
        window.draw(canBG);
    }


private:
    sf::RectangleShape can;
    sf::RectangleShape canBG;

    sf::Texture canTxt;
    sf::Texture canBGTxt;
};

class charSprite {
public:
    static constexpr sf::Vector2f PartSize{ 157.f, 354.f };

    charSprite(const sf::Vector2f& position,
        charLook look = { 0, 0, 0,
                         sf::Color(0,0,0),
                         sf::Color(0,0,0),
                         sf::Color(0,0,0),
                         sf::Color(0,0,0) })
    {
        initPart(shoes.part, shoes.tex);
        initPart(pants.part, pants.tex);
        initPart(shirt.part, shirt.tex);
        initPart(fingers.part, fingers.tex);
        initPart(handBG.part, handBG.tex);
        initPart(handFG.part, handFG.tex);
        initPart(head.part, head.tex);
        initPart(hair.part, hair.tex);
        initPart(face.part, face.tex);
        initPart(hat.part, hat.tex);

        if (look.hairID > 0) {
            std::stringstream ss;
            ss << "assets/img/sprites/hair/hair" <<  look.hairID << ".png";
            hasHair = loadAndSetup(hair, ss.str());
            if (hasHair) hair.part.setFillColor(look.hairColor);
        }

        if (look.faceID > 0) {
            std::stringstream ss;
            ss << "assets/img/sprites/face/face" <<  look.faceID << ".png";
            hasFace = loadAndSetup(face, ss.str());
        }

        if (look.hatID > 0) {
            std::stringstream ss;
            ss << "assets/img/sprites/hat/hat" << look.hatID << ".png";
            hasHat = loadAndSetup(hat, ss.str());
        }

        loadAndSetup(shoes, "assets/img/sprites/shoes.png");
        shoes.part.setFillColor(look.shoeColor);

        loadAndSetup(pants, "assets/img/sprites/pants.png");
        pants.part.setFillColor(look.pantsColor);

        loadAndSetup(shirt, "assets/img/sprites/shirt.png");
        shirt.part.setFillColor(look.topColor);

        loadAndSetup(fingers, "assets/img/sprites/fingers.png");
        loadAndSetup(handBG, "assets/img/sprites/handbg.png");
        loadAndSetup(handFG, "assets/img/sprites/handfg.png");
        loadAndSetup(head, "assets/img/sprites/head.png");

        setPos(position.x, position.y);
    }

    // -1 - facing left, 1 - facing right

    int facing = 1;

    void draw(sf::RenderWindow& window) {
        window.draw(shoes.part);
        window.draw(pants.part);
        window.draw(handBG.part);
        window.draw(shirt.part);
        window.draw(fingers.part);
        window.draw(handFG.part);
        window.draw(head.part);
        if (hasFace) window.draw(face.part);
        if (hasHair) window.draw(hair.part);
        if (hasHat) window.draw(hat.part);
    }

    void setPos(float x, float y) {
        const sf::Vector2f pos{ x, y };
        shoes.part.setPosition(pos);
        pants.part.setPosition(pos);
        shirt.part.setPosition(pos);
        fingers.part.setPosition(pos);
        handBG.part.setPosition(pos);
        handFG.part.setPosition(pos);
        head.part.setPosition(pos);
        hair.part.setPosition(pos);
        face.part.setPosition(pos);
        hat.part.setPosition(pos);
    }

    // flip horizontally; optional dir: 1 = right, -1 = left
    void flip(int dir = 0) {
        facing = dir ? dir : -facing;
        sf::Vector2f direction = { static_cast<float>(facing), 1.f };
        shoes.part.setScale(direction);
        pants.part.setScale(direction);
        shirt.part.setScale(direction);
        fingers.part.setScale(direction);
        handBG.part.setScale(direction);
        handFG.part.setScale(direction);
        head.part.setScale(direction);
        hair.part.setScale(direction);
        face.part.setScale(direction);
        hat.part.setScale(direction);
    }

    void changeLook(charLook newLook){
        if (newLook.hairID > 0) {
            std::stringstream ss;
            ss << "assets/img/sprites/hair/hair" << newLook.hairID << ".png";
            hasHair = loadAndSetup(hair, ss.str());
            if (hasHair) hair.part.setFillColor(newLook.hairColor);
            else std::cout << "ERROR WHILE LOADING HAIR";
        }
        else {
            hasHair = false;
        }

        if (newLook.faceID > 0) {
            std::stringstream ss;
            ss << "assets/img/sprites/face/face" << newLook.faceID << ".png";
            hasFace = loadAndSetup(face, ss.str());
            if (!hasFace) std::cout << "ERROR WHILE LOADING FACE";
        }
        else {
            hasFace = false;
        }

        if (newLook.hatID > 0) {
            std::stringstream ss;
            ss << "assets/img/sprites/hat/hat" << newLook.hatID << ".png";
            hasHat = loadAndSetup(hat, ss.str());
            if (!hasHat) std::cout << "ERROR WHILE LOADING HAT";
        }
        else {
            hasHat = false;
        }

        loadAndSetup(shoes, "assets/img/sprites/shoes.png");
        shoes.part.setFillColor(newLook.shoeColor);

        loadAndSetup(pants, "assets/img/sprites/pants.png");
        pants.part.setFillColor(newLook.pantsColor);

        loadAndSetup(shirt, "assets/img/sprites/shirt.png");
        shirt.part.setFillColor(newLook.topColor);

        loadAndSetup(fingers, "assets/img/sprites/fingers.png");
        loadAndSetup(handBG, "assets/img/sprites/handbg.png");
        loadAndSetup(handFG, "assets/img/sprites/handfg.png");
        loadAndSetup(head, "assets/img/sprites/head.png");
    }

private:
    struct Part {
        sf::RectangleShape part{ PartSize };
        sf::Texture tex;
    };

    Part shoes;
    Part pants;
    Part shirt;
    Part fingers;
    Part handBG;
    Part handFG;
    Part head;
    Part hair;
    Part face;
    Part hat;

    bool hasHair{ false };
    bool hasFace{ false };
    bool hasHat{ false };

    void initPart(sf::RectangleShape& shape, const sf::Texture&) {
        shape.setSize(PartSize);
        shape.setOrigin({ PartSize.x / 2.f, PartSize.y / 2.f });
    }
    bool loadAndSetup(Part& p, const std::string& path) {
        if (p.tex.loadFromFile(path)) {
            p.part.setTexture(&p.tex);
            std::cout << path << std::endl;
            return true;
        }

        return false;
    }
};


class Button {
public:
    Button(const sf::Vector2f& size, 
        const sf::Vector2f& position, 
        const sf::Color& color, 
        const sf::Color& hoverColor, 
        const std::string& textString, 
        const sf::Font& font, 
        unsigned int charSize, 
        const std::string& texture = "")
        : shape(size), text(font, textString, charSize), baseColor(color), hoverColor(hoverColor) {

        shape.setPosition(position);
        if (!texture.empty() && b_texture.loadFromFile(texture)) {
            shape.setTexture(&b_texture);
            shape.setFillColor(color);
        }
        else {
            shape.setFillColor(color);
        }
        text.setPosition(sf::Vector2f(position.x + size.x / 2.0f - text.getLocalBounds().size.x / 2.0f, position.y + size.y / 2.0f - text.getLocalBounds().size.y / 2.0f - 5.0f));
    }
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }
    bool isMouseOver(const sf::Vector2f& mousePos) {
        return shape.getGlobalBounds().contains(mousePos);
    }
    void hover() {
        shape.setFillColor(hoverColor);
    }
    void unhover() {
        shape.setFillColor(baseColor);
    }
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Texture b_texture;
    sf::Color baseColor;
    sf::Color hoverColor;
};




class QTEbar : public sf::Drawable, public sf::Transformable{

private:
    std::vector<sf::RectangleShape> m_rects;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        for (const auto& rect : m_rects) {
            target.draw(rect, states);
        }
    }
public:
    QTEbar(float width, float height, float spacing) {
        const sf::Color colors[] = {
            sf::Color(0,150,0),
            sf::Color(237, 214, 34),
            sf::Color(255,0,0)
        };

        for (int i = 0; i < 3; i++) {
            sf::RectangleShape rect(sf::Vector2f(width, height));
            rect.setFillColor(colors[i]);
            float yPos = (height + spacing) * static_cast<float>(i);
            rect.setPosition(sf::Vector2f(0.f, yPos));
            m_rects.push_back(rect);
        }
    }
};


class greyBar : public sf::Drawable, public sf::Transformable {

private:
    std::vector<sf::RectangleShape> m_rects;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        for (const auto& rect : m_rects) {
            target.draw(rect, states);
        }
    }
public:
    greyBar(float width, float height, float spacing) {
        
        

        //for (int i = 0; i < 3; i++) {
            sf::RectangleShape rect(sf::Vector2f(width, height));
            rect.setFillColor(sf::Color(128, 128, 128));
            float yPos = (height + spacing);
            rect.setPosition(sf::Vector2f(0.f, yPos));
            m_rects.push_back(rect);
        //}
    }
};


charLook randomChar() {
    int clothesLen = sizeof(mainPalette.clothes) / sizeof(mainPalette.clothes[0]);
    int hairLen = sizeof(mainPalette.hair) / sizeof(mainPalette.hair[0]);
    int skinLen = sizeof(mainPalette.skin) / sizeof(mainPalette.skin[0]);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis4(0, 3);
    std::uniform_int_distribution<> dis5(0, 10);
    std::uniform_int_distribution<> dis6(0, 4);
    std::uniform_int_distribution<> dis7(0, 255);
    std::uniform_int_distribution<> skinInt(0, skinLen-1);
    std::uniform_int_distribution<> hairInt(0, hairLen-1);
    std::uniform_int_distribution<> clothesInt(0, clothesLen-1);
    int hat = dis4(gen);
    int hair = dis5(gen);
    int face = dis6(gen);
    sf::Color shirtColor = mainPalette.clothes[clothesInt(gen)];
    sf::Color pantsColor = mainPalette.clothes[clothesInt(gen)];
    sf::Color shoesColor = mainPalette.clothes[clothesInt(gen)];

    int hairColorInt = clothesInt(gen);
    std::cout << "randHairColor: " << hairColorInt << std::endl;
    // tutaj jezeli wylosowalo clothesColor wiekszy niz 15. to daje go, ale jezeli kolor jest za ciemny czy za jasny (posegrowane w arrayu) to daje normalny ludzki kolor. wylosowanie jakiegokolwiek dziwnego koloru ma szanse 1/3, jakikolwiek normalny - 2/3 (w teorii.........)
    sf::Color hairColor = hairColorInt >= 15 ? mainPalette.clothes[hairColorInt] : mainPalette.hair[hairInt(gen)];

    sf::Color skinColor = mainPalette.skin[skinInt(gen)];

    charLook charCharacter = { hat, hair, face, shirtColor, pantsColor, shoesColor, hairColor};

    std::cout << "hatID: " << hat << std::endl << 
        " hairID: " << hair << std::endl << 
        " faceID: " << face << std::endl << 
        " shirtColor: " << (int)shirtColor.r << " " << (int)shirtColor.g << " " << (int)shirtColor.b << std::endl <<
        " pantsColor: " << (int)pantsColor.r << " " << (int)pantsColor.g << " " << (int)pantsColor.b << std::endl <<
        " shoesColor " << (int)shoesColor.r << " " << (int)shoesColor.g << " " << (int)shoesColor.b << std::endl <<
        " hairColor: " << (int)hairColor.r << " " << (int)hairColor.g << " " << (int)hairColor.b << std::endl <<
        " skinColor: " << (int)skinColor.r << " " << (int)skinColor.g << " " << (int)skinColor.b << std::endl; 
    return charCharacter;
}


// hair color to kolor normalny, a clothes popierdolony, 