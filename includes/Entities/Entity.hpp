#pragma once

#include <SFML/Graphics.hpp>

#include "Game/SceneNode.hpp"

namespace shootemup
{
class Entity : public SceneNode
{
public:
    Entity(std::uint32_t hitpoints);

    void set_velocity(sf::Vector2f velocity);

    void set_velocity(float x_velocity, float y_velocity);

    sf::Vector2f get_velocity() const;

    void accelerate(sf::Vector2f velocity);

    void repair(std::uint32_t points);
    void damage(std::uint32_t points);
    void destroy();
    std::uint32_t get_hitpoints();
    bool is_destroyed() const override;

protected:
    void _update_current(sf::Time delta_time,
                         CommandQueue& command_queue) override;

private:
    sf::Vector2f m_velocity;
    std::uint32_t m_hitpoints;
};

}  // namespace shootemup
