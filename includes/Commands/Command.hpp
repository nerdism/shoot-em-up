#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>
#include <functional>

#include "Game/SceneNode.hpp"

namespace shootemup
{

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
