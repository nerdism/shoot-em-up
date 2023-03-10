#pragma once

#include <SFML/Graphics.hpp>

#include "Game/SceneNode.hpp"

namespace shootemup
{
class Entity : public SceneNode
{
public:
    void set_velocity(sf::Vector2f velocity);

    void set_velocity(float x_velocity, float y_velocity);

    sf::Vector2f get_velocity() const;

    void accelerate(sf::Vector2f velocity);

protected:
    void _update_current(sf::Time delta_time) override;

private:
    sf::Vector2f m_velocity;
};

}  // namespace shootemup
