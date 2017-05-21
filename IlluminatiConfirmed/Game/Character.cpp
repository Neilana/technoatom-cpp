#include "Character.h"

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

Character::Character(const std::string& file, int f, int width, int height)
{
    x = 0;
    y = 0;
    vx = 0;
    vy = 0;
    speed = 0.1;
    currentFrame = 0;
    frames = f;

    texture.loadFromFile(file);

    tileWidth = width;
    tileHeight = height;

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::Rect<int>(0,0,width,height));
    sprite.setPosition(x, y);

    for (int column = 0; column < frames; column++)
    {
        int row = 0;
        frontRects.push_back(Rect<int>(column * tileWidth, tileHeight * row++, tileWidth, tileHeight));
        backRects.push_back(Rect<int>(column * tileWidth, tileHeight * row++, tileWidth, tileHeight));
        rightRects.push_back(Rect<int>(column * tileWidth, tileHeight * row++, tileWidth, tileHeight));
        leftRects.push_back(Rect<int>(column * tileWidth, tileHeight * row++, tileWidth, tileHeight));
    }

}

void Character::move(Direction dir, float deltaTime)
{
    currentFrame += 0.005 * deltaTime;
    if (currentFrame > frames) currentFrame -= frames;
    //   float oldSpeed = speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        //     oldSpeed = speed;
        // speed *= 1.5;
        deltaTime *= 1.6;
    }

    switch (dir)
    {
        case Direction::Up:
        {
            vx = 0;
            vy = -speed;
            sprite.setTextureRect(backRects[int(currentFrame)]);
        }
        break;

        case Direction::Down:
        {
            vx = 0;
            vy = speed;
            sprite.setTextureRect(frontRects[int(currentFrame)]);
        }
        break;

        case Direction::Right:
        {
            vx = speed;
            vy = 0;
            sprite.setTextureRect(rightRects[int(currentFrame)]);
        }
        break;

        case Direction::Left:
        {
            vx = -speed;
            vy = 0;
            sprite.setTextureRect(leftRects[int(currentFrame)]);
        }
        break;
    }

    if ((x + vx * deltaTime > 0) && (x + vx * deltaTime < WINDOW_WIDTH - tileWidth))
        x += vx * deltaTime;
    if ((y + vy * deltaTime > 0) && (y + vy * deltaTime < WINDOW_HEIGHT - tileHeight))
        y += vy * deltaTime;

    //    speed = oldSpeed;
    sprite.setPosition(x, y);
}

void Character::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}
