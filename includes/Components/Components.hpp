#pragma once

#include <SFML/Graphics.hpp>

namespace shootemup
{
class GameEntityComp : public sf::Transformable
{
public:
    GameEntityComp(sf::Texture& texture, sf::IntRect texture_rect)
    {
        sprite.setTexture(texture);
        sprite.setTextureRect(texture_rect);
    }
    sf::Sprite sprite;
};

}  // namespace shootemup