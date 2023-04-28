#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include <vector>

#include "Utility.hpp"

namespace shootemup
{
class SpriteComponent : public sf::Transformable
{
public:
    SpriteComponent(sf::Texture& texture, sf::IntRect texture_rect)
    {
        sprite.setTexture(texture);
        sprite.setTextureRect(texture_rect);
        shootemup::center_origin(sprite);
    }
    sf::Sprite sprite;
};

class TextComponent : public sf::Transformable
{
public:
    TextComponent(const sf::Font& font, std::string string)
    {
        text.setFont(font);
        text.setString(string);
        text.setCharacterSize(20);
        shootemup::center_origin(text);

        // TODO: Calculate text position from sprite dynamically
        text.setPosition(sf::Vector2f(0, 45));
    }
    sf::Text text;
};

class SceneNodeComponent
{
public:
    entt::entity parent;
    std::vector<entt::entity> children;
};

class HealthComponent
{
public:
    HealthComponent(std::uint32_t hitpoint)
    {
        this->hitpoint = hitpoint;
    }
    std::uint32_t hitpoint;
};

}  // namespace shootemup
