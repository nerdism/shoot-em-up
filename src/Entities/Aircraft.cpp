#include "Entities/Aircraft.hpp"

#include "Commands/Command.hpp"
#include "Entities/Projectile.hpp"
#include "Utility.hpp"

using shootemup::Aircraft;
using shootemup::AircraftData;
using shootemup::CommandQueue;

// Initialize Aircraft Data (hitpoint, damage, etc..)
const std::vector<AircraftData> Aircraft::m_data =
    shootemup::initialize_aircraft_data();

Aircraft::Aircraft(Type type, const TextureHolder& texture_holder,
                   const FontHolder& font_holder)
    : Entity{m_data[static_cast<std::uint32_t>(type)].hitpoints},
      m_sprite{
          texture_holder.get(m_data[static_cast<std::uint32_t>(type)].texture),
          m_data[static_cast<std::uint32_t>(type)].rect},
      m_fire_interval{m_data[static_cast<std::uint32_t>(type)].fireInterval},
      m_type{type},
      m_travelled_distance{0},
      m_direction_index{0},
      m_is_firing{false},
      m_fire_counter{sf::Time::Zero}

{
    m_fire_command.category =
        shootemup::enum_to_int(EntityCategory::SceneAirLayer);
    m_fire_command.action = [&](SceneNode& node, sf::Time delta_time)
    { _create_projectile(node, texture_holder); };

    center_origin(m_sprite);

    std::unique_ptr<TextNode> text_node =
        std::make_unique<TextNode>(font_holder, "");
    m_health_display = text_node.get();
    attach_child(std::move(text_node));

    _update_health_display();
}

void Aircraft::_update_health_display()
{
    m_health_display->setPosition(0.f, 50.f);
    m_health_display->setRotation(-getRotation());
    m_health_display->set_text(std::to_string(get_hitpoints()) + " HP");
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

void Aircraft::_update_current(sf::Time delta_time, CommandQueue& command_queue)
{
    _update_movement_pattern(delta_time);
    Entity::_update_current(delta_time, command_queue);
    _check_projectile_launch(delta_time, command_queue);
    _update_health_display();
}

uint32_t Aircraft::get_category() const
{
    switch (m_type)
    {
        case Type::Eagle:
            return shootemup::enum_to_int(EntityCategory::PlayerAircraft);
        default:
            return shootemup::enum_to_int(EntityCategory::EnemyAircraft);
    }
}

float Aircraft::get_maxspeed()
{
    return m_data[static_cast<uint32_t>(m_type)].speed;
}

void Aircraft::fire()
{
    if (m_fire_counter >= m_fire_interval)
    {
        m_is_firing = true;
    }
}

void Aircraft::_check_projectile_launch(sf::Time delta_time,
                                        CommandQueue& command_queue)
{
    m_fire_counter += delta_time;
    if (m_is_firing && m_fire_counter >= m_fire_interval)
    {
        command_queue.push(m_fire_command);
        m_is_firing = false;
        m_fire_counter = sf::Time::Zero;
    }
}

void Aircraft::_create_projectile(SceneNode& node,
                                  const TextureHolder& texture_holder)
{
    auto projectile = std::make_unique<Projectile>(
        Projectile::Type::AlliedBullet, texture_holder);

    // projectile->set_velocity(sf::Vector2f(0.f, projectile->get_max_speed()));
    projectile->setPosition(get_world_position());

    node.attach_child(std::move(projectile));
}

sf::FloatRect Aircraft::get_bounding_rect() const
{
    // TODO: did not understand this
    return get_world_transform().transformRect(m_sprite.getGlobalBounds());
}
