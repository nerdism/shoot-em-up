
#include "States/StateStack.hpp"

#include <cassert>
#include <memory>

using shootemup::State;
using shootemup::StateStack;

StateStack::StateStack(State::Context context)
    : m_context{context}
{
}

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

void StateStack::draw()
{
    for (auto iter = m_state_stack.begin(); iter != m_state_stack.end(); ++iter)
    {
        (*iter)->draw();
    }
}
void StateStack::update(sf::Time delta_time)
{
    for (auto iter = m_state_stack.rbegin(); iter != m_state_stack.rend();
         ++iter)
    {
        if (!(*iter)->update(delta_time))
        {
            return;
        }
    }
    _apply_pending_changes();
}

void StateStack::_apply_pending_changes()
{
    for (auto& pending_change : m_pending_list)
    {
        switch (pending_change.action)
        {
            case StackAction::Push:
                m_state_stack.push_back(
                    _create_state(pending_change.game_state));
                break;
            case StackAction::Pop:
                m_state_stack.pop_back();
                break;
            case StackAction::Clear:
                m_state_stack.clear();
                break;
        }
    }
}

void StateStack::push_state(GameState game_state)
{
    m_pending_list.emplace_back(StackAction::Push, game_state);
}
void StateStack::pop_state()
{
    m_pending_list.pop_back();
}
void StateStack::clear_states()
{
    m_pending_list.clear();
}

StateStack::PendingChange::PendingChange(StackAction action,
                                         GameState game_state)
    : action{action},
      game_state{game_state}
{
}

bool StateStack::is_empty() const
{
    return m_state_stack.empty();
}