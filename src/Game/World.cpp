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

World::World(sf::RenderWindow& window, TextureHolder& texture_holder,
             FontHolder& font_holder)
    : m_window{window},
      m_world_view{window.getDefaultView()},
      m_texture_holder{texture_holder},
      m_font_holder{font_holder}
{
    _build_scene();
    m_world_view.setCenter(0, 0);

    // Create player aircraft
    auto player = m_registry.create();
    m_registry.emplace<SpriteComponent>(
        player, m_texture_holder.get(TextureId::Entities),
        sf::IntRect(0, 0, 48, 64));
    SceneNodeComponent player_scene_node;
    m_registry.emplace<tag::AirLayerEntity>(player);
    m_registry.emplace<tag::Aircraft>(player);
    m_registry.emplace<tag::PlayerAircraft>(player);

    auto air_layer_scene_node_entity =
        m_registry.view<tag::AirLayerScenenNode>()[0];

    SceneNodeComponent& air_node =
        m_registry.get<SceneNodeComponent>(air_layer_scene_node_entity);

    air_node.children.push_back(player);

    player_scene_node.parent = air_layer_scene_node_entity;

    auto health_text_entity = m_registry.create();

    m_registry.emplace<TextComponent>(health_text_entity,
                                      m_font_holder.get(FontId::Main), "xx Hp");

    SceneNodeComponent health_text_scene_node;

    health_text_scene_node.parent = player;

    player_scene_node.children.push_back(health_text_entity);

    m_registry.emplace<SceneNodeComponent>(health_text_entity,
                                           health_text_scene_node);
    m_registry.emplace<SceneNodeComponent>(player, player_scene_node);
}

void World::draw()
{
    m_window.setView(m_world_view);
    std::function<void(entt::entity, sf::RenderStates)> draw_nodes =
        [&](entt::entity entity, sf::RenderStates render_states)
    {
        if (m_registry.all_of<SpriteComponent>(entity))
        {
            auto game_entity = m_registry.get<SpriteComponent>(entity);

            render_states.transform *= game_entity.getTransform();

            m_window.draw(game_entity.sprite, render_states);
        }
        else if (m_registry.all_of<TextComponent>(entity))
        {
            auto text_entity = m_registry.get<TextComponent>(entity);

            render_states.transform *= text_entity.getTransform();

            m_window.draw(text_entity.text, render_states);
        }

        auto scene_node = m_registry.get<SceneNodeComponent>(entity);

        for (auto child_entity : scene_node.children)
        {
            draw_nodes(child_entity, render_states);
        }
    };

    auto root_scene_node_entity = m_registry.view<tag::RootSceneNode>()[0];
    sf::RenderStates render_states = sf::RenderStates::Default;

    draw_nodes(root_scene_node_entity, render_states);
    // auto& game_entity = view.get<GameEntityComp>(entity);
    // render_states.transform *= game_entity.getTransform();
    // m_window.draw(game_entity.sprite, render_states);
}

void World::update(sf::Time delta_time)
{
    while (!m_command_queue.empty())
    {
        const Command& command = m_command_queue.front();
        command.action(m_registry, delta_time);
        m_command_queue.pop();
    }
}

void World::_build_scene()
{
    // Create root scene node
    auto root_scene_node_entity = m_registry.create();
    m_registry.emplace<SceneNodeComponent>(root_scene_node_entity);
    m_registry.emplace<tag::RootSceneNode>(root_scene_node_entity);

    // Create backgroun scene node
    auto background_layer_scene_node_entity = m_registry.create();
    m_registry.emplace<SceneNodeComponent>(background_layer_scene_node_entity);
    SceneNodeComponent& background_node =
        m_registry.get<SceneNodeComponent>(background_layer_scene_node_entity);
    background_node.parent = root_scene_node_entity;

    // Mark this node so that later attach node to it easier instead of begining
    // from root node
    m_registry.emplace<tag::BackgroundLayerScenenNode>(
        background_layer_scene_node_entity);

    // Create air scene node
    auto air_layer_scene_node_entity = m_registry.create();
    m_registry.emplace<SceneNodeComponent>(air_layer_scene_node_entity);
    SceneNodeComponent& air_node =
        m_registry.get<SceneNodeComponent>(air_layer_scene_node_entity);
    air_node.parent = root_scene_node_entity;

    // Mark this node so that later attach node to it easier instead of begining
    // from root node
    m_registry.emplace<tag::AirLayerScenenNode>(air_layer_scene_node_entity);

    SceneNodeComponent& root_node =
        m_registry.get<SceneNodeComponent>(root_scene_node_entity);
    root_node.children.push_back(background_layer_scene_node_entity);
    root_node.children.push_back(air_layer_scene_node_entity);
}

CommandQueue& World::get_command_queue()
{
    return m_command_queue;
}
