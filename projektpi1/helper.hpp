#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include <iostream>
#pragma once
#include <cmath>
// tu wszystkie funkcje i klasy
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

struct charLook {
    int hatID;
    int hairID;
    int faceID;
    sf::Color topColor;
    sf::Color pantsColor;
    sf::Color shoeColor;
    sf::Color hairColor;
};

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
            hasHair = loadAndSetup(hair, std::format("assets/img/sprites/hair/hair{}.png", look.hairID));
            if (hasHair) hair.part.setFillColor(look.hairColor);
        }

        if (look.faceID > 0) {
            hasFace = loadAndSetup(face, std::format("assets/img/sprites/face/face{}.png", look.faceID));
        }

        if (look.hatID > 0) {
            hasHat = loadAndSetup(hat, std::format("assets/img/sprites/hat/hat{}.png", look.hatID));
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