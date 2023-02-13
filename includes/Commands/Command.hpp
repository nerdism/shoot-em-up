#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>
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
    Pickup = 1 << 4,
    AlliedProjectile = 1 << 5,
    EnemyProjectile = 1 << 6,
    Aircraft = PlayerAircraft | AlliedAircraft | EnemyAircraft,
    Projectile = AlliedProjectile | EnemyProjectile

};
}

class SceneNode;

class Command
{
public:
    std::function<void(SceneNode&, sf::Time)> action;
    uint32_t category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derived_action(Function fn)
{
    return [=](SceneNode& node, sf::Time delta_time)
    {
        assert(dynamic_cast<GameObject*>(&node) != nullptr);

        fn(static_cast<GameObject&>(node), delta_time);
    };
}

}  // namespace shootemup
