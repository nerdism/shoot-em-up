#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "Commands/Command.hpp"
#include "Commands/CommandQueue.hpp"
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

    World(sf::RenderWindow& window, FontHolder& font_holder);

    CommandQueue& get_command_queue();

    void update(sf::Time delta_time);

    void draw();

private:
    void _load_textures();
    void _build_scene();
    void _spawn_enemies();
    void _add_enemies();
    void _add_enemy(Aircraft::Type type, float x, float y);

    sf::FloatRect _get_view_bounds() const;
    sf::FloatRect _get_battlefield_bounds() const;

    enum class SceneLayer
    {
        Background,
        Air,
        LayerCount
    };

    struct SpawnPoint
    {
        SpawnPoint(Aircraft::Type type, float x, float y)
            : type(type),
              x(x),
              y(y)
        {
        }

        Aircraft::Type type;
        float x;
        float y;
    };

    sf::RenderWindow& m_window;
    sf::View m_world_view;

    TextureHolder m_texture_holder;
    FontHolder& m_font_holder;
    SceneNode m_scene_graph;
    std::array<SceneNode*, static_cast<uint32_t>(SceneLayer::LayerCount)>
        m_scene_layers;

    sf::FloatRect m_world_bounds;
    sf::Vector2f m_spawn_position;
    float m_scroll_speed;
    Aircraft* m_player_aircraft;
    CommandQueue m_command_queue;

    std::vector<SpawnPoint> m_enemy_spawn_points;
};
}  // namespace shootemup
