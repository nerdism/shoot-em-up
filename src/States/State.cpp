
#include "States/State.hpp"

#include "States/StateStack.hpp"

using shootemup::State;

State::State(StateStack& stack, Context context)
    : m_state_stack{&stack},
      m_context{context}
{
}

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures,
                        FontHolder& fonts, Player& player)
    : window{&window},
      textures{&textures},
      fonts{&fonts},
      player{&player}
{
}

void State::_request_stack_push(GameState game_state)
{
    m_state_stack->push_state(game_state);
}

void State::_request_stack_pop()
{
    m_state_stack->pop_state();
}
void State::_request_state_clear()
{
    m_state_stack->clear_states();
}

State::Context State::get_context() const
{
    return m_context;
}