#include "Game/World.hpp"

#include "Game/SpriteNode.hpp"

using shootemup::CommandQueue;
using shootemup::World;

World::World(sf::RenderWindow& window)
    : m_window{window},
      m_world_view{window.getDefaultView()},
      m_world_bounds{0, 0, m_world_view.getSize().x, 2000.f},
      m_spawn_position{m_world_view.getSize().x / 2.f,
                       m_world_bounds.height - m_world_view.getSize().y / 2.f},
      m_player_aircraft{nullptr},
      m_scroll_speed{-50.f}
{
    _load_textures();
    _build_scene();

    m_world_view.setCenter(m_spawn_position);
}

void World::_load_textures()
{
    m_texture_holder.load_compiled_resource(
        TextureId::Airplane_Eagle, "resources/images/gameplay/Eagle.png");
    m_texture_holder.load_compiled_resource(
        TextureId::Airplane_Raptor, "resources/images/gameplay/Raptor.png");
    m_texture_holder.load_compiled_resource(
        TextureId::Desert, "resources/images/gameplay/Desert.png");
}

void World::_build_scene()
{
    // Attach layer to the scene graph
    for (std::size_t i = 0; i < m_scene_layers.size(); ++i)
    {
        SceneNode::Ptr node = std::make_unique<SceneNode>();
        m_scene_layers[i] = node.get();

        m_scene_graph.attach_child(std::move(node));
    }

    sf::Texture& texture = m_texture_holder.get(TextureId::Desert);
    const sf::IntRect texture_rect(m_world_bounds);
    texture.setRepeated(true);

    std::unique_ptr<SpriteNode> background_sprite =
        std::make_unique<SpriteNode>(texture, texture_rect);

    background_sprite->setPosition(m_world_bounds.left, m_world_bounds.top);

    const auto background_index =
        static_cast<uint32_t>(World::SceneLayer::Background);

    m_scene_layers[background_index]->attach_child(
        std::move(background_sprite));

    std::unique_ptr<Aircraft> leader =
        std::make_unique<Aircraft>(Aircraft::Type::Eagle, m_texture_holder);
    m_player_aircraft = leader.get();
    m_player_aircraft->setPosition(m_spawn_position);
    m_player_aircraft->set_velocity(40.f, m_scroll_speed);

    const auto air_index = static_cast<uint32_t>(World::SceneLayer::Air);

    m_scene_layers[air_index]->attach_child(std::move(leader));

    std::unique_ptr<Aircraft> left_escort =
        std::make_unique<Aircraft>(Aircraft::Type::Raptor, m_texture_holder);
    left_escort->setPosition(-80.f, 50.f);
    m_player_aircraft->attach_child(std::move(left_escort));

    std::unique_ptr<Aircraft> right_escort =
        std::make_unique<Aircraft>(Aircraft::Type::Raptor, m_texture_holder);
    right_escort->setPosition(80.f, 50.f);
    m_player_aircraft->attach_child(std::move(right_escort));
}

void World::draw()
{
    m_window.setView(m_world_view);
    m_window.draw(m_scene_graph);
}

void World::update(sf::Time delta_time)
{
    while (!m_command_queue.empty())
    {
        m_scene_graph.on_command(m_command_queue.front(), delta_time);
        m_command_queue.pop();
    }

    m_world_view.move(0.f, m_scroll_speed * delta_time.asSeconds());
    m_scene_graph.update(delta_time);
}

CommandQueue& World::get_command_queue()
{
    return m_command_queue;
}
