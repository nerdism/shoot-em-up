#include "Game/World.hpp"

#include "Game/SpriteNode.hpp"

using shootemup::CommandQueue;
using shootemup::World;

World::World(sf::RenderWindow& window, FontHolder& font_holder)
    : m_window{window},
      m_world_view{window.getDefaultView()},
      m_world_bounds{0, 0, m_world_view.getSize().x, 2000.f},
      m_spawn_position{m_world_view.getSize().x / 2.f,
                       m_world_bounds.height - m_world_view.getSize().y / 2.f},
      m_player_aircraft{nullptr},
      m_scroll_speed{-50.f},
      m_font_holder{font_holder}
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
        TextureId::Airplane_Avenger, "resources/images/gameplay/Avenger.png");
    m_texture_holder.load_compiled_resource(
        TextureId::Bullet, "resources/images/gameplay/Bullet.png");
    m_texture_holder.load_compiled_resource(
        TextureId::Missile, "resources/images/gameplay/Missile.png");
    m_texture_holder.load_compiled_resource(
        TextureId::Desert, "resources/images/gameplay/Desert.png");
}

void World::_build_scene()
{
    // Attach layer to the scene graph
    for (std::size_t i = 0; i < m_scene_layers.size(); ++i)
    {
        SceneNode::Ptr node;

        if (i == m_scene_layers.size() - 1)
        {
            node = std::make_unique<SceneNode>(EntityCategory::SceneAirLayer);
        }
        else
        {
            node = std::make_unique<SceneNode>();
        }

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

    std::unique_ptr<Aircraft> leader = std::make_unique<Aircraft>(
        Aircraft::Type::Eagle, m_texture_holder, m_font_holder);
    m_player_aircraft = leader.get();
    m_player_aircraft->setPosition(m_spawn_position);
    m_player_aircraft->set_velocity(0.f, m_scroll_speed);

    const auto air_index = static_cast<uint32_t>(World::SceneLayer::Air);

    m_scene_layers[air_index]->attach_child(std::move(leader));

    /*
    std::unique_ptr<Aircraft> left_escort =
        std::make_unique<Aircraft>(Aircraft::Type::Raptor, m_texture_holder);
    left_escort->setPosition(-80.f, 50.f);
    m_player_aircraft->attach_child(std::move(left_escort));

    std::unique_ptr<Aircraft> right_escort =
        std::make_unique<Aircraft>(Aircraft::Type::Raptor, m_texture_holder);
    right_escort->setPosition(80.f, 50.f);
    m_player_aircraft->attach_child(std::move(right_escort));
    */
    _add_enemies();
}

void World::draw()
{
    m_window.setView(m_world_view);
    m_window.draw(m_scene_graph);
}

void World::update(sf::Time delta_time)
{
    m_world_view.move(0.f, m_scroll_speed * delta_time.asSeconds());
    m_player_aircraft->set_velocity(0.f, 0.f);
    while (!m_command_queue.empty())
    {
        m_scene_graph.on_command(m_command_queue.front(), delta_time);
        m_command_queue.pop();
    }

    sf::Vector2f velocity = m_player_aircraft->get_velocity();

    if (velocity.x != 0.f && velocity.y != 0.f)
    {
        m_player_aircraft->set_velocity(velocity / std::sqrt(2.f));
    }

    m_player_aircraft->accelerate(sf::Vector2f(0.f, m_scroll_speed));

    sf::FloatRect view_bounds(
        m_world_view.getCenter() - m_world_view.getSize() / 2.f,
        m_world_view.getSize());
    const float border_distance = 40.f;

    sf::Vector2f position = m_player_aircraft->getPosition();
    position.x = std::max(position.x, view_bounds.left + border_distance);
    position.x = std::min(
        position.x, view_bounds.left + view_bounds.width - border_distance);
    position.y = std::max(position.y, view_bounds.top + border_distance);
    position.y = std::min(
        position.y, view_bounds.top + view_bounds.height - border_distance);

    m_player_aircraft->setPosition(position);

    m_scene_graph.update(delta_time, m_command_queue);

    _spawn_enemies();
}

CommandQueue& World::get_command_queue()
{
    return m_command_queue;
}

sf::FloatRect World::_get_view_bounds() const
{
    return sf::FloatRect(
        m_world_view.getCenter() - m_world_view.getSize() / 2.f,
        m_world_view.getSize());
}

sf::FloatRect World::_get_battlefield_bounds() const
{
    // Return view bounds + some area at top, where enemies spawn
    sf::FloatRect bounds = _get_view_bounds();
    bounds.top -= 100.f;
    bounds.height += 100.f;

    return bounds;
}

void World::_spawn_enemies()
{
    while (!m_enemy_spawn_points.empty() &&
           m_enemy_spawn_points.back().y > _get_battlefield_bounds().top)
    {
        std::unique_ptr<Aircraft> enemy = std::make_unique<Aircraft>(
            m_enemy_spawn_points.back().type, m_texture_holder, m_font_holder);

        enemy->setPosition(m_enemy_spawn_points.back().x,
                           m_enemy_spawn_points.back().y);
        enemy->setRotation(180);

        const auto air_index = static_cast<uint32_t>(World::SceneLayer::Air);

        m_scene_layers[air_index]->attach_child(std::move(enemy));

        m_enemy_spawn_points.pop_back();
    }
}

void World::_add_enemies()
{
    _add_enemy(Aircraft::Type::Raptor, 0.f, 300.f);
    _add_enemy(Aircraft::Type::Avenger, -100.f, 500.f);
    _add_enemy(Aircraft::Type::Avenger, 100.f, 800.f);
    _add_enemy(Aircraft::Type::Raptor, -70.f, 1000.f);
    _add_enemy(Aircraft::Type::Avenger, -100.f, 1200.f);
    _add_enemy(Aircraft::Type::Avenger, 200.f, 1500.f);
    _add_enemy(Aircraft::Type::Raptor, 0.f, 1800.f);

    std::sort(m_enemy_spawn_points.begin(), m_enemy_spawn_points.end(),
              [](SpawnPoint lhs, SpawnPoint rhs) { return lhs.y < rhs.y; });
}

void World::_add_enemy(Aircraft::Type type, float x, float y)
{
    m_enemy_spawn_points.emplace_back(type, m_spawn_position.x + x,
                                      m_spawn_position.y - y);
}
