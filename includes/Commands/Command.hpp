#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "Game/SceneNode.hpp"

namespace shootemup
{

namespace EntityCategory
{
enum
{
    None = 0,
    Scene = 1,
    PlayerAircraft = 1 << 1,
    AlliedAircraft = 1 << 2,
    EnemyAircraft = 1 << 3,

};
}

class SceneNode;

class Command
{
public:
    std::function<void(SceneNode&, sf::Time)> action;
    uint32_t category;
};

}  // namespace shootemup
