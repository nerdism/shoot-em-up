#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "Commands/CommandQueue.hpp"

namespace shootemup
{
class Player
{
public:
    enum class Action
    {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };
    Player();

    void handle_event(const sf::Event& event, CommandQueue& commands);

    void handle_realtime_input(CommandQueue& commands);

    void assign_key(Action action, sf::Keyboard::Key key);

    sf::Keyboard::Key get_assigned_key(Action action) const;

private:
    static bool _is_realtime_action(Action action);
    std::map<sf::Keyboard::Key, Action> m_key_bindings;
    std::map<Action, Command> m_action_bindings;
};
}  // namespace shootemup
