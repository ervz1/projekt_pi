#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include <iostream>
#pragma once
#include <cmath>
#include <sstream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <fstream>

// tu wszystkie funkcje i klasy

inline sf::Color clothesPalette[] = {
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

inline sf::Color hairPalette[] = {
    sf::Color(113, 69, 30),
    sf::Color(223, 196, 98),
    sf::Color(194, 93, 31),
    sf::Color(54, 31, 17) 
};

inline sf::Color skinPalette[] = {
    sf::Color(231,190,128),
    sf::Color(231, 178, 128),
    sf::Color(178,112,50),
    sf::Color(101,53,6)
};

struct spritePalette {
    sf::Color* clothes;
    sf::Color* hair;
    sf::Color* skin;
};  

inline spritePalette mainPalette = {
    clothesPalette,
    hairPalette,
    skinPalette
};


// hair, hat, face
inline std::string paths[] = {
    "assets/img/sprites/hair/",
    "assets/img/sprites/hat/",
    "assets/img/sprites/face/"
};



// charlook(int hatID, int hairID, int faceID, sfcolor topColor, sfcolor pantsColor, sfcolor shoeColor, sfcolor hairColor, sfcolor skinColor)
struct charLook {
    int hatID;
    int hairID;
    int faceID;
    sf::Color topColor;
    sf::Color pantsColor;
    sf::Color shoeColor;
    sf::Color hairColor;
    sf::Color skinColor;
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

class middleCanSprite{
public:
    middleCanSprite(const sf::Vector2f& position)
        : can({ 44.f, 74.f }),
        canBG({ 44.f, 74.f }), 
        canNoise({ 44.f, 74.f }) {
        canTxt.loadFromFile("assets/img/cans/canbase.png");
        can.setTexture(&canTxt);
        canBGTxt.loadFromFile("assets/img/cans/can1.png");
        canBG.setTexture(&canBGTxt);
        canNoiseTxt.loadFromFile("assets/img/cans/cannoise.png");
        canNoise.setTexture(&canNoiseTxt);

        can.setOrigin({ 22.f, 74.f});
        canBG.setOrigin({ 22.f, 74.f });
        canNoise.setOrigin({ 22.f, 74.f });
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
        canNoise.setPosition(pos);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(can);
        window.draw(canBG);
    }
    
    void rotateRight() {
            can.rotate(sf::degrees(90));
            canBG.rotate(sf::degrees(90));
            canNoise.rotate(sf::degrees(90));  
    }

    void rotateLeft() {
            can.rotate(sf::degrees(-90));
            canBG.rotate(sf::degrees(-90));
            canNoise.rotate(sf::degrees(-90));
    }

    void standUp() {
        can.setRotation(sf::degrees(0));
        canBG.setRotation(sf::degrees(0));
        canNoise.setRotation(sf::degrees(0));
    }


private:
    sf::RectangleShape can;
    sf::RectangleShape canBG;
    sf::RectangleShape canNoise;

    sf::Texture canTxt;
    sf::Texture canBGTxt;
    sf::Texture canNoiseTxt;
};

class charSprite {
public:
    static constexpr sf::Vector2f PartSize{ 157.f, 354.f };

    charSprite(const sf::Vector2f& position,
        charLook look = { 
            0, 0, 0,
            sf::Color::White,
            sf::Color::White,
            sf::Color::White,
            sf::Color::White,
            sf::Color::White
        })
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
        setSkinColor(look.skinColor);
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
        shoes.part.setFillColor(newLook.shoeColor);
        pants.part.setFillColor(newLook.pantsColor);
        shirt.part.setFillColor(newLook.topColor);
        setSkinColor(newLook.skinColor);
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
            //std::cout << path << std::endl;
            return true;
        }

        return false;
    }
    void setSkinColor(sf::Color color) {
        fingers.part.setFillColor(color);
        handBG.part.setFillColor(color);
        handFG.part.setFillColor(color);
        head.part.setFillColor(color);
    }
};

// id: 0 - hair, 1 - hat, 2 - face
class chooseDisp {
public:
    int partID;
    sf::Color skinColor;
    sf::Color hairColor;
    chooseDisp(
        const sf::Vector2f& pos,
        const int ID,
        const int pID,
        const sf::Color = sf::Color::White
    ) : part({ 157.f, 354.f }), partID{pID} {
        switch (ID)
        {
        case 0:
            partType = "hair";
            path = paths[ID];
            maxPID = 10;
            break;
        case 1:
            partType = "hat";
            path = paths[ID];
            maxPID = 3;
            break;
        case 2:
            partType = "face";
            path = paths[ID];
            maxPID = 4;
            addFace = true;
            faceText.loadFromFile("assets/img/sprites/head.png");
            face.setPosition(pos);
            face.setSize({ 157.f, 354.f });
            face.setTexture(&faceText);
            face.setScale({ 2.f, 2.f });
            break;
        default:
            break;
        }
        part.setPosition(pos);
        if (partID) {
            textPath << path << partType << "1.png";
            //std::cout << textPath.str() << std::endl;
            text.loadFromFile(textPath.str());
            part.setTexture(&text);
        }
        part.setScale({2.f, 2.f});
    };
    void draw(sf::RenderWindow& window) {
        if (addFace) {
            window.draw(face);
        }
        if (partID) window.draw(part);
    };
    void setPos(sf::Vector2f pos) {
        part.setPosition(pos);
    };
    void setPartID(int pIDl = -1) {
        if (pIDl != -1) {
            partID = pIDl;
        }
        if (partID != 0) {
            textPath.str(std::string());
            textPath << path << partType << partID << ".png";
            text.loadFromFile(textPath.str());
            part.setTexture(&text);
        }
    };
    void pIDstep(int dir) {
        dir = std::clamp(dir, -1, 1);
        if (partID + dir > maxPID) partID = 0;
        else if (partID + dir < 0) partID = maxPID;
        else partID = partID + dir;
        setPartID();
    }
    void setColor(sf::Color color) {
        if (addFace) {
            skinColor = color;
            face.setFillColor(color);
        }
        else if (partType == "hair") {
            hairColor = color;
            part.setFillColor(color);
        }
    }

private:
    sf::RectangleShape part;
    sf::Texture text;
    std::stringstream textPath;
    std::string path;
    std::string partType;
    bool addFace;
    sf::RectangleShape face;
    sf::Texture faceText;
    int maxPID;
};

//size, pos, color, hovColor, text, font, charSize, texture
class Button {
public:
    Button(const sf::Vector2f& size, 
        const sf::Vector2f& position, 
        const sf::Color& color, 
        const sf::Color& hoverColor, 
        const std::string& texture,
        const std::string& textString = "",
        const std::string& font = "",
        unsigned int charSize = 0)
        : shape(size), baseColor(color), text(fontF, textString, charSize), hoverColor(hoverColor), textureStr(texture){

        if (!textString.empty()) {
            if (fontF.openFromFile(font)) {
                text.setString(textString);
                text.setCharacterSize(charSize);
                text.setFont(fontF);
                fontF.setSmooth(false);
                hasText = true;
            }
        }

        shape.setPosition(position);
        if (!textureStr.empty() && b_texture.loadFromFile(textureStr)) {
            shape.setTexture(&b_texture);
            shape.setFillColor(color);
        }
        if (hasText) text.setPosition(sf::Vector2f(position.x + size.x / 2.0f - text.getLocalBounds().size.x / 2.0f, position.y + size.y / 2.0f - text.getLocalBounds().size.y / 2.0f - 13.0f));
    }

    Button(const Button& other)
        : shape(other.shape),
        baseColor(other.baseColor),
        hoverColor(other.hoverColor),
        textureStr(other.textureStr),
        b_texture(other.b_texture), 
        fontF(other.fontF),         
        text(other.text),
        hasText(other.hasText)
    {
        if (!textureStr.empty()) {
            shape.setTexture(&b_texture);
        }
        if (hasText) {
            text.setFont(fontF);
        }
    }

    sf::Color getColor() const {
        return baseColor;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        if (hasText) window.draw(text);
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
    std::string textureStr;
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font fontF;
    sf::Texture b_texture;
    sf::Color baseColor;
    sf::Color hoverColor;
    bool hasText{false};
};

inline charLook randomChar() {
    constexpr int clothesLen = static_cast<int>(sizeof(clothesPalette) / sizeof(clothesPalette[0]));
    constexpr int hairLen = static_cast<int>(sizeof(hairPalette) / sizeof(hairPalette[0]));
    constexpr int skinLen = static_cast<int>(sizeof(skinPalette) / sizeof(skinPalette[0]));

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
    //std::cout << "randHairColor: " << hairColorInt << std::endl;
    // tutaj jezeli wylosowalo clothesColor wiekszy niz 15. to daje go, ale jezeli kolor jest za ciemny czy za jasny (posegrowane w arrayu) to daje normalny ludzki kolor. wylosowanie jakiegokolwiek dziwnego koloru ma szanse 1/3, jakikolwiek normalny - 2/3 (w teorii.........)
    sf::Color hairColor = (hairColorInt >= 15 ? mainPalette.clothes[hairColorInt] : mainPalette.hair[hairInt(gen)]);

    sf::Color skinColor = mainPalette.skin[skinInt(gen)];

    charLook charCharacter = { hat, hair, face, shirtColor, pantsColor, shoesColor, hairColor, skinColor};

    //std::cout << "hatID: " << hat << std::endl << 
    //    " hairID: " << hair << std::endl << 
    //    " faceID: " << face << std::endl << 
    //    " shirtColor: " << (int)shirtColor.r << " " << (int)shirtColor.g << " " << (int)shirtColor.b << std::endl <<
    //    " pantsColor: " << (int)pantsColor.r << " " << (int)pantsColor.g << " " << (int)pantsColor.b << std::endl <<
    //    " shoesColor " << (int)shoesColor.r << " " << (int)shoesColor.g << " " << (int)shoesColor.b << std::endl <<
    //    " hairColor: " << (int)hairColor.r << " " << (int)hairColor.g << " " << (int)hairColor.b << std::endl <<
    //    " skinColor: " << (int)skinColor.r << " " << (int)skinColor.g << " " << (int)skinColor.b << std::endl; 
    return charCharacter;
}

class colorSelectScreen {
public:
    colorSelectScreen() {}

    colorSelectScreen(sf::Color colArr[], int partID = 0, int colorCount = 0) {
        setup(colArr, colorCount);
    }

    void setup(sf::Color colArr[], int colorCount) {
        buttonArr.clear();
        float startX = 74.f;
        float startY = 187.f;

        for (int i = 0; i < colorCount; ++i) {
            buttonArr.push_back(Button(
                sf::Vector2f(72.f, 67.f),
                sf::Vector2f(startX + (i % 8) * 83.f, startY + (i / 8) * 75.f),
                colArr[i],
                sf::Color(colArr[i].r + 20, colArr[i].g + 20, colArr[i].b + 20),
                "assets/img/colorSelectBlank.png"
            ));
        }
    }

    void draw(sf::RenderWindow& wind) {
        for (Button& button : buttonArr) {
            button.draw(wind);
        }
    }

    void update(sf::Vector2f mousePos) {
        for (Button& button : buttonArr) {
            if (button.isMouseOver(mousePos)) button.hover();
            else button.unhover();
        }
    }

    std::optional<sf::Color> getClickedColor(sf::Vector2f mousePos) {
        for (Button& button : buttonArr) {
            if (button.isMouseOver(mousePos)) {
                return button.getColor();
            }
        }
        return std::nullopt;
    }

private:
    std::vector <Button> buttonArr;
};

class fillPiwa : public sf::Drawable, public sf::Transformable {
private:
    sf::Sprite bar;
    int max;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        target.draw(bar, states);
    }

public:
    float BOTTOM_OFFSET = 8.f;
    void addOffset(){
        BOTTOM_OFFSET = 0;
    };
    void removeOffset(){
        BOTTOM_OFFSET = 8.f;
    };

    fillPiwa(const sf::Texture& tex, int maxValue)
        : bar(tex), max(maxValue)
    {
        auto size = tex.getSize();

        bar.setOrigin({0.f, static_cast<float>(size.y)});

        bar.setTextureRect({
            {0, 0},
            {static_cast<int>(size.x), static_cast<int>(size.y)}
        });
        
    }

    void setValue(int value) {
        value = std::clamp(value, 0, max);

        auto size = bar.getTexture().getSize();

        float ratio = 1.f - static_cast<float>(value) / static_cast<float>(max);
        int h = static_cast<int>(size.y * ratio);

        bar.setTextureRect({
            {0, 0},
            {static_cast<int>(size.x), h}
        });

        bar.setPosition({0.f, static_cast<float>(size.y - h - BOTTOM_OFFSET)
});

    }
};

class ramkaPiwa : public sf::Drawable, public sf::Transformable {
private:
    sf::Sprite frame;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        target.draw(frame, states);
    }

public:
    ramkaPiwa(const sf::Texture& frameTex)
        : frame(frameTex)
    {
        auto size = frameTex.getSize();
        frame.setOrigin({0.f, static_cast<float>(size.y)});
    }
};

inline void saveCharacterToFile(const charLook& character) {
    std::ofstream file("save.txt");
    if (file.is_open()) {
        file << character.hatID << " "
            << character.hairID << " "
            << character.faceID << "\n";

        auto saveColor = [&](sf::Color c) {
            file << (int)c.r << " " << (int)c.g << " " << (int)c.b << "\n";
            };
        saveColor(character.topColor);
        saveColor(character.pantsColor);
        saveColor(character.shoeColor);
        saveColor(character.hairColor);
        saveColor(character.skinColor);

        file.close();
    }
}


class PowerBar {
public:
    PowerBar() {
        texture.loadFromFile("assets/img/powerbar.png");
        bar.setTexture(&texture);
        bar.setFillColor(sf::Color::Red);
    }

    void setRotation(float angle) {
        bar.setRotation(sf::degrees(angle));
        
    }

    void draw(sf::RenderWindow& window, sf::Vector2f position, float rotation, float length, float thickness) {
        bar.setPosition(position);
        bar.setRotation(sf::degrees(rotation));
        bar.setSize(sf::Vector2f(length, thickness));
        window.draw(bar);
    }

private:
    sf::RectangleShape bar;
    sf::Texture texture;
};



inline charLook loadCharacterFromFile() {
    std::ifstream file("save.txt");
    if (!file.is_open()) {
        return randomChar();
    }

    charLook loaded;
    int r, g, b;

    file >> loaded.hatID >> loaded.hairID >> loaded.faceID;

    auto loadColor = [&]() -> sf::Color {
        file >> r >> g >> b;
        return sf::Color(r, g, b);
        };
    loaded.topColor = loadColor();
    loaded.pantsColor = loadColor();
    loaded.shoeColor = loadColor();
    loaded.hairColor = loadColor();
    loaded.skinColor = loadColor();

    file.close();
    return loaded;
}