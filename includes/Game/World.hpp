#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "Entities/Aircraft.hpp"
#include "Game/SceneNode.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Commands/Command.hpp"
#include "Commands/CommandQueue.hpp"

namespace shootemup
{
class World
{
public:
    World(const World& world) = delete;
    World& operator=(const World& world) = delete;

    World(sf::RenderWindow& window);

    CommandQueue& get_command_queue();

    void update(sf::Time delta_time);

    void draw();

private:
    void _load_textures();
    void _build_scene();

    enum class SceneLayer
    {
        Background,
        Air,
        LayerCount
    };

    sf::RenderWindow& m_window;
    sf::View m_world_view;

    TextureHolder m_texture_holder;
    SceneNode m_scene_graph;
    std::array<SceneNode*, static_cast<uint32_t>(SceneLayer::LayerCount)>
        m_scene_layers;

    sf::FloatRect m_world_bounds;
    sf::Vector2f m_spawn_position;
    float m_scroll_speed;
    Aircraft* m_player_aircraft;
    CommandQueue m_command_queue;

};
}  // namespace shootemup
