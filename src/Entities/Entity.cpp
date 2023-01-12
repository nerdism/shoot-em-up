
#include "Entities/Entity.hpp"

using shootemup::Entity;

void Entity::set_velocity(sf::Vector2f velocity) { m_velocity = velocity; }
void Entity::set_velocity(float x_velocity, float y_velocity)
{
    m_velocity = sf::Vector2f(x_velocity, y_velocity);
}

sf::Vector2f Entity::get_velocity() const { return m_velocity; }

void Entity::_update_current(sf::Time delta_time)
{
    move(m_velocity * delta_time.asSeconds());
}
