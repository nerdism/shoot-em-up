#include "Game/Player.hpp"

#include <iostream>

#include "Entities/Aircraft.hpp"
#include "Game/SceneNode.hpp"
#include "SFML/Graphics.hpp"

using shootemup::Aircraft;
using shootemup::Player;

class AircraftMover
{
public:
    AircraftMover(float x_velocity, float y_velocity)
        : m_velocity{x_velocity, y_velocity}
    {
    }

    void operator()(Aircraft& aircraft, sf::Time delta_time) const
    {
        aircraft.accelerate(m_velocity);
    }

private:
    sf::Vector2f m_velocity;
};

Player::Player()
{
    m_key_bindings[sf::Keyboard::Left] = Action::MoveLeft;
    m_key_bindings[sf::Keyboard::Right] = Action::MoveRight;
    m_key_bindings[sf::Keyboard::Up] = Action::MoveUp;
    m_key_bindings[sf::Keyboard::Down] = Action::MoveDown;

    const float player_speed = 200.f;

    m_action_bindings[Action::MoveLeft].action =
        derived_action<Aircraft>(AircraftMover(-player_speed, 0.f));
    m_action_bindings[Action::MoveRight].action =
        derived_action<Aircraft>(AircraftMover(+player_speed, 0.f));
    m_action_bindings[Action::MoveUp].action =
        derived_action<Aircraft>(AircraftMover(0.f, -player_speed));
    m_action_bindings[Action::MoveDown].action =
        derived_action<Aircraft>(AircraftMover(0.f, +player_speed));

    for (auto& action_binding : m_action_bindings)
    {
        action_binding.second.category = EntityCategory::PlayerAircraft;
    }
}

void Player::handle_event(const sf::Event& event, CommandQueue& commands)
{
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::P)
    {
        Command output;
        output.category = shootemup::EntityCategory::PlayerAircraft;
        output.action = [](SceneNode& s, sf::Time) {
            std::cout << s.getPosition().x << ", " << s.getPosition().y
                      << std::endl;
        };
        commands.push(output);
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
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    //{
    //     Command move_left;
    //     move_left.category = shootemup::EntityCategory::PlayerAircraft;
    //     move_left.action =
    //         derived_action<Aircraft>(AircraftMover(-player_speed, 0.f));
    //     commands.push(move_left);
    // }

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    //{
    //     Command move_forward;
    //     move_forward.category = shootemup::EntityCategory::PlayerAircraft;
    //     move_forward.action =
    //         derived_action<Aircraft>(AircraftMover(0, -player_speed));
    //     commands.push(move_forward);
    // }
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
            return true;

        default:
            return false;
    }
}
