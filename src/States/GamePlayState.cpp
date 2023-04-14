#include "States/GamePlayState.hpp"

using shootemup::GamePlayState;

GamePlayState::GamePlayState(StateStack& stack, Context context)
    : State{stack, context},
      m_world{*context.window, *context.textures, *context.fonts},
      m_player{*context.player}
{
}

void GamePlayState::draw()
{
    m_world.draw();
}

bool GamePlayState::update(sf::Time delta_time)
{
    CommandQueue& command_queue = m_world.get_command_queue();

    m_player.handle_realtime_input(command_queue);

    m_world.update(delta_time);
    return false;
}

bool GamePlayState::handle_event(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape)
    {
        _request_stack_push(GameState::Pause);
    }
    else
    {
        CommandQueue& command_queue = m_world.get_command_queue();
        m_player.handle_event(event, command_queue);
    }

    return false;
}
