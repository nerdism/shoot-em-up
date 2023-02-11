#include "Entities/Entity.hpp"

using shootemup::Entity;

Entity::Entity(std::uint32_t hitpoints)
    : m_hitpoints{hitpoints}
{
}

void Entity::set_velocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}
void Entity::set_velocity(float x_velocity, float y_velocity)
{
    m_velocity = sf::Vector2f(x_velocity, y_velocity);
}

sf::Vector2f Entity::get_velocity() const
{
    return m_velocity;
}

void Entity::_update_current(sf::Time delta_time)
{
    move(m_velocity * delta_time.asSeconds());
}

void Entity::accelerate(sf::Vector2f velocity)
{
    set_velocity(get_velocity() + velocity);
}

void Entity::repair(std::uint32_t points)
{
    assert(m_hitpoints > 0);
    m_hitpoints += points;
}

void Entity::damage(std::uint32_t points)
{
    assert(m_hitpoints > 0);
    m_hitpoints -= points;
}

void Entity::destroy()
{
    m_hitpoints = 0;
}

std::uint32_t Entity::get_hitpoints()
{
    return m_hitpoints;
}

bool Entity::is_destroyed()
{
    return m_hitpoints <= 0;
}
