#pragma once

#include <SFML/Graphics.hpp>

#include "Entities/Entity.hpp"
#include "Game/DataTables.hpp"
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

    void _update_movement_pattern(sf::Time delta_time);

    float get_maxspeed();

    void fire();

private:
    void _update_health_display();

    Type m_type;
    sf::Sprite m_sprite;
    TextNode* m_health_display;
    float m_travelled_distance;
    std::size_t m_direction_index;

    static const std::vector<AircraftData> m_data;
};

}  // namespace shootemup