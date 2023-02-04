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
    TexturesId texture;
    sf::Time fireInterval;
    std::vector<Direction> directions;
};

struct ProjectileData
{
    int damage;
    float speed;
    TexturesId texture;
};

struct PickupData
{
    std::function<void(Aircraft&)> action;
    TexturesId texture;
};

std::vector<AircraftData> initializeAircraftData();
std::vector<ProjectileData> initializeProjectileData();
std::vector<PickupData> initializePickupData();

}  // namespace shootemup