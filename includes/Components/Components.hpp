#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include <vector>

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

class SceneNodeComp
{
public:
    entt::entity parent;
    std::vector<entt::entity> children;
};

}  // namespace shootemup
