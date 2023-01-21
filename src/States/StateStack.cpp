
#include "States/StateStack.hpp"

#include <cassert>
#include <memory>

using shootemup::State;
using shootemup::StateStack;

template <typename T>
void StateStack::register_state(GameState game_state)
{
    m_factories[game_state] = [this]()
    { return State::Ptr(new T(*this, m_context)); };
}

State::Ptr StateStack::_create_state(GameState game_state)
{
    auto found = m_factories.find(game_state);

    assert(found != m_factories.end());

    return found->second();
}

void StateStack::handle_event(const sf::Event& event)
{
    for (auto iter = m_state_stack.rbegin(); iter != m_state_stack.rend();
         ++iter)
    {
        if (!(*iter)->handle_event(event))
        {
            return;
        }
    }
    _apply_pending_changes();
}

void StateStack::_apply_pending_changes()
{
}