#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>
#include <entt/entt.hpp>
#include <functional>

#include "Game/SceneNode.hpp"

namespace shootemup
{

class SceneNode;

class Command
{
public:
    std::function<void(entt::registry&, sf::Time)> action;
};

}  // namespace shootemup
