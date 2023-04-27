#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "Commands/Command.hpp"
#include "Commands/CommandQueue.hpp"
#include "Components/Components.hpp"
#include "Entities/Aircraft.hpp"
#include "Game/SceneNode.hpp"
#include "ResourceManager/ResourceManager.hpp"

namespace shootemup
{
class World
{
public:
    World(const World& world) = delete;
    World& operator=(const World& world) = delete;

    World(sf::RenderWindow& window, TextureHolder& texture_holder,
          FontHolder& font_holder);

    CommandQueue& get_command_queue();

    void update(sf::Time delta_time);

    void draw();

private:
    void _build_scene();

    entt::registry m_registry;

    sf::RenderWindow& m_window;
    sf::View m_world_view;

    TextureHolder& m_texture_holder;
    FontHolder& m_font_holder;

    CommandQueue m_command_queue;

    sf::Sprite m_player;
};

bool matches_category(SceneNode::Pair& colliders, uint32_t type1,
                      uint32_t type2);
}  // namespace shootemup
