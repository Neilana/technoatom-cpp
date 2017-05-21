#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "constants.h"

class Character
{
private:
    float x, y, vx, vy, speed;
    float currentFrame;
    int frames;

    sf::Texture texture;
    sf::Sprite sprite;

    int tileWidth, tileHeight;

    std::vector<sf::Rect<int>> frontRects;
    std::vector<sf::Rect<int>> backRects;
    std::vector<sf::Rect<int>> leftRects;
    std::vector<sf::Rect<int>> rightRects;

public:
    //Character();
    Character(const std::string& file, int frames, int width, int height);
    void move(Direction dir, float deltaTime);
    void draw(sf::RenderWindow &window);
};
