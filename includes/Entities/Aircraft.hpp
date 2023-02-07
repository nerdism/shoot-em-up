#pragma once

#include <SFML/Graphics.hpp>

#include "Entities/Entity.hpp"
#include "Game/TextNode.hpp"
#include "ResourceManager/ResourceManager.hpp"

namespace shootemup
{
class Aircraft : public Entity
{
public:
    enum class Type
    {
        Eagle,
        Raptor,
        Avenger,
        TypeCount
    };

    explicit Aircraft(Type type, const TextureHolder& texture_holder,
                      const FontHolder& font_holder);

    void _draw_current(sf::RenderTarget& target,
                       sf::RenderStates states) const override;

    uint32_t get_category() const override;

    void _update_current(sf::Time delta_time) override;

private:
    Type m_type;
    sf::Sprite m_sprite;
    TextNode* m_health_display;
};

}  // namespace shootemup