
#include "States/State.hpp"

using shootemup::State;

State::State(StateStack& stack, Context context)
    : m_state_stack{&stack},
      m_context{context}
{
}

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures,
                        Player& player)
    : window{&window},
      textures{&textures},
      player{&player}
{
}

void State::request_stack_push(GameState game_state)
{
}
void State::request_stack_pop()
{
}
void State::request_state_clear()
{
}
