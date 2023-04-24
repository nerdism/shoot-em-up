#include "Game/World.hpp"

#include <entt/entt.hpp>
#include <iostream>
#include <set>

#include "Components/Components.hpp"
#include "Components/Tags.hpp"
#include "Game/SpriteNode.hpp"
#include "Utility.hpp"

using shootemup::CommandQueue;
using shootemup::SceneNode;
using shootemup::World;

entt::registry registry;

World::World(sf::RenderWindow& window, TextureHolder& texture_holder,
             FontHolder& font_holder)
    : m_window{window},
      m_world_view{window.getDefaultView()},
      m_texture_holder{texture_holder},
      m_font_holder{font_holder}
{
    // m_world_view.setCenter(m_spawn_position);
    auto player = registry.create();
    registry.emplace<GameEntityComp>(player,
                                     m_texture_holder.get(TextureId::Entities),
                                     sf::IntRect(0, 0, 48, 64));
    registry.emplace<tag::AirLayerEntity>(player);
    registry.emplace<tag::Aircraft>(player);
    registry.emplace<tag::PlayerAircraft>(player);

    m_world_view.setCenter(0, 0);
}

void World::draw()
{
    m_window.setView(m_world_view);

    sf::RenderStates render_states = sf::RenderStates::Default;

    auto view = registry.view<GameEntityComp>();

    for (auto entity : view)
    {
        auto& game_entity = view.get<GameEntityComp>(entity);
        render_states.transform *= game_entity.getTransform();
        m_window.draw(game_entity.sprite, render_states);
    }
}

void World::update(sf::Time delta_time)
{
    while (!m_command_queue.empty())
    {
        const Command& command = m_command_queue.front();
        command.action(registry, delta_time);
        m_command_queue.pop();
    }
}

CommandQueue& World::get_command_queue()
{
    return m_command_queue;
}
