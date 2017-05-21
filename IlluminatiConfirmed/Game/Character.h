#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "constants.h"

class Character
{
private:

    float currentFrame;
    int frames;

    sf::Texture texture;
    sf::Sprite sprite;



    std::vector<sf::Rect<int>> frontRects;
    std::vector<sf::Rect<int>> backRects;
    std::vector<sf::Rect<int>> leftRects;
    std::vector<sf::Rect<int>> rightRects;

public:
        int tileWidth, tileHeight;
        float x, y, vx, vy, speed;
    //Character();
    Character(const std::string& file, int frames, int width, int height);
    void move(Direction dir, float deltaTime);
    void draw(sf::RenderWindow &window);
    void setCoordinates(int newX, int newY) { x = newX; y = newY; sprite.setPosition(x,y);}

    float getX() { return x; };
    float getY() { return y; };
};
