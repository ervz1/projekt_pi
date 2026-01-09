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

class Button {
public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const sf::Color& hoverColor, const std::string& textString, const sf::Font& font, unsigned int charSize, const std::string& texture = "")
        : shape(size), text(font, textString, charSize), baseColor(color), hoverColor(hoverColor){
        shape.setPosition(position);
        if (!texture.empty() && b_texture.loadFromFile(texture)) {
            // setTexture expects a pointer to a texture that remains valid
            shape.setTexture(&b_texture);
            shape.setFillColor(color);
        }
        else {
            // fallback to a fill color when there's no texture or loading fails
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
            //sf::Color::Color(255,0,0),
            //sf::Color::Color(237, 214, 34),
            sf::Color::Color(0,150,0),
            sf::Color::Color(237, 214, 34),
            sf::Color::Color(255,0,0)
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
            rect.setFillColor(sf::Color::Color(128, 128, 128));
            float yPos = (height + spacing);
            rect.setPosition(sf::Vector2f(0.f, yPos));
            m_rects.push_back(rect);
        //}
    }
};