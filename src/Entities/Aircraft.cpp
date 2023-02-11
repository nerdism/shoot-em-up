#include "Entities/AirCraft.hpp"

#include "Commands/Command.hpp"
#include "Utility.hpp"

using shootemup::Aircraft;
using shootemup::AircraftData;

// Initialize Aircraft Data (hitpoint, damage, etc..)
const std::vector<AircraftData> Aircraft::m_data =
    shootemup::initialize_aircraft_data();

void Aircraft::_update_health_display()
{
    m_health_display->setPosition(0.f, 50.f);
    m_health_display->setRotation(-getRotation());
    m_health_display->set_text(std::to_string(get_hitpoints()) + " HP");
}
Aircraft::Aircraft(Type type, const TextureHolder& texture_holder,
                   const FontHolder& font_holder)
    : Entity{m_data[static_cast<std::uint32_t>(type)].hitpoints},
      m_sprite{
          texture_holder.get(m_data[static_cast<std::uint32_t>(type)].texture)},
      m_type{type},
      m_travelled_distance{0},
      m_direction_index{0}

{
    const sf::FloatRect rect = m_sprite.getLocalBounds();
    m_sprite.setOrigin(rect.width / 2.f, rect.height / 2.f);
    std::unique_ptr<TextNode> text_node =
        std::make_unique<TextNode>(font_holder, "");
    m_health_display = text_node.get();
    attach_child(std::move(text_node));

    _update_health_display();
}

void Aircraft::_update_movement_pattern(sf::Time delta_time)
{
    const std::vector<Direction>& directions =
        m_data[static_cast<uint32_t>(m_type)].directions;
    if (!directions.empty())
    {
        // Moved long enough in current direction: Change direction
        if (m_travelled_distance > directions[m_direction_index].distance)
        {
            m_direction_index = (m_direction_index + 1) % directions.size();
            m_travelled_distance = 0.f;
        }

        // Compute velocity from direction
        const float radians =
            to_radian(directions[m_direction_index].angle + 90.f);
        const float vx = get_maxspeed() * std::cos(radians);
        const float vy = get_maxspeed() * std::sin(radians);

        set_velocity(vx, vy);

        m_travelled_distance += get_maxspeed() * delta_time.asSeconds();
    }
}

void Aircraft::_draw_current(sf::RenderTarget& target,
                             sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

void Aircraft::_update_current(sf::Time delta_time)
{
    _update_movement_pattern(delta_time);
    Entity::_update_current(delta_time);
    _update_health_display();
}

uint32_t Aircraft::get_category() const
{
    switch (m_type)
    {
        case Type::Eagle:
            return EntityCategory::PlayerAircraft;

        default:
            return EntityCategory::EnemyAircraft;
    }
}

float Aircraft::get_maxspeed()
{
    return m_data[static_cast<uint32_t>(m_type)].speed;
}
