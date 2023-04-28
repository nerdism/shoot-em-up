#include "Game/Player.hpp"

#include <entt/entt.hpp>
#include <iostream>

#include "Components/Components.hpp"
#include "Components/Tags.hpp"
#include "Entities/Aircraft.hpp"
#include "Game/SceneNode.hpp"
#include "SFML/Graphics.hpp"
#include "Utility.hpp"

using shootemup::Aircraft;
using shootemup::Player;
using shootemup::SpriteComponent;

class AircraftMover
{
public:
    AircraftMover(float x_velocity, float y_velocity)
        : m_velocity{x_velocity, y_velocity}
    {
    }

    void operator()(Aircraft& aircraft, sf::Time /*delta_time*/) const
    {
        aircraft.accelerate(m_velocity);
    }

private:
    sf::Vector2f m_velocity;
};

Player::Player()
{
    m_key_bindings[sf::Keyboard::A] = Action::MoveLeft;
    m_key_bindings[sf::Keyboard::D] = Action::MoveRight;
    m_key_bindings[sf::Keyboard::W] = Action::MoveUp;
    m_key_bindings[sf::Keyboard::S] = Action::MoveDown;
    m_key_bindings[sf::Keyboard::Space] = Action::ShootBullet;
    m_key_bindings[sf::Keyboard::F] = Action::LaunchMissile;

    const float player_speed = 200.f;

    m_action_bindings[Action::MoveLeft].action =
        [](entt::registry& registry, sf::Time delta_time)
    {
        auto view = registry.view<tag::PlayerAircraft>();
        for (auto entity : view)
        {
            SpriteComponent& game_entity =
                registry.get<SpriteComponent>(entity);
            game_entity.move(-1.f, 0.f);
        }
    };

    m_action_bindings[Action::MoveRight].action =
        [](entt::registry& registry, sf::Time delta_time)
    {
        auto view = registry.view<tag::PlayerAircraft>();
        for (auto entity : view)
        {
            SpriteComponent& game_entity =
                registry.get<SpriteComponent>(entity);
            game_entity.move(1.f, 0.f);
        }
    };
    m_action_bindings[Action::MoveUp].action =
        [](entt::registry& registry, sf::Time delta_time)
    {
        auto view = registry.view<tag::PlayerAircraft>();
        for (auto entity : view)
        {
            SpriteComponent& game_entity =
                registry.get<SpriteComponent>(entity);
            game_entity.move(0.f, -1.f);
        }
    };
    m_action_bindings[Action::MoveDown].action =
        [](entt::registry& registry, sf::Time delta_time)
    {
        auto view = registry.view<tag::PlayerAircraft>();
        for (auto entity : view)
        {
            SpriteComponent& game_entity =
                registry.get<SpriteComponent>(entity);
            game_entity.move(0.f, 1.f);
        }
    };

    // m_action_bindings[Action::ShootBullet].action = derived_action<Aircraft>(
    //     [](Aircraft& aircraft, sf::Time /*delta_time*/) { aircraft.fire();
    //     });
}

void Player::handle_event(const sf::Event& event, CommandQueue& commands)
{
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::P)
    {
        // Command output;
        // output.action = [](SceneNode& s, sf::Time) {
        //     std::cout << s.getPosition().x << ", " << s.getPosition().y
        //               << std::endl;
        // };
        // commands.push(output);
    }
}

void Player::handle_realtime_input(CommandQueue& commands)
{
    const float player_speed = 30.f;

    for (auto key_binding : m_key_bindings)
    {
        if (sf::Keyboard::isKeyPressed(key_binding.first) &&
            _is_realtime_action(key_binding.second))
        {
            commands.push(m_action_bindings[key_binding.second]);
        }
    }
}

sf::Keyboard::Key Player::get_assigned_key(Action action) const
{
    for (auto key_binding : m_key_bindings)
    {
        if (key_binding.second == action)
        {
            return key_binding.first;
        }
    }
    return sf::Keyboard::Unknown;
}

void Player::assign_key(Action action, sf::Keyboard::Key key)
{
    // Remove all keys that already map to action
    for (auto itr = m_key_bindings.begin(); itr != m_key_bindings.end();)
    {
        if (itr->second == action)
        {
            m_key_bindings.erase(itr++);
        }
        else
        {
            ++itr;
        }
    }
    m_key_bindings[key] = action;
}

bool Player::_is_realtime_action(Action action)
{
    switch (action)
    {
        case Action::MoveLeft:
        case Action::MoveRight:
        case Action::MoveUp:
        case Action::MoveDown:
        case Action::ShootBullet:
            return true;

        default:
            return false;
    }
}
