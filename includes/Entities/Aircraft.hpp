#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "ResourceManager/ResourceManager.hpp"

namespace shootemup
{
class Aircraft : public Entity
{
public:
    enum class Type
    {
        Eagle,
        Raptor
    };

    explicit Aircraft(
        Type type,
        const ResourceHolder<sf::Texture, TextureId>& texture_holder);
    void _draw_current(sf::RenderTarget& target,
                       sf::RenderStates states) const override;

private:
    Type m_type;
    sf::Sprite m_sprite;
};

}  // namespace shootemup