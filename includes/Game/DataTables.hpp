#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include <functional>
#include <vector>

#include "ResourceManager/ResourceManager.hpp"

namespace shootemup
{

class Aircraft;

struct Direction
{
    Direction(float angle, float distance)
        : angle(angle),
          distance(distance)
    {
    }

    float angle;
    float distance;
};

struct AircraftData
{
    int hitpoints;
    float speed;
    TextureId texture;
    sf::Time fireInterval;
    std::vector<Direction> directions;
};

struct ProjectileData
{
    int damage;
    float speed;
    TextureId texture;
};

/*
struct PickupData
{
    std::function<void(Aircraft&)> action;
    TextureId texture;
};
*/

std::vector<AircraftData> initialize_aircraft_data();
std::vector<ProjectileData> initialize_projectile_data();
// std::vector<PickupData> initialize_pickup_data();

}  // namespace shootemup