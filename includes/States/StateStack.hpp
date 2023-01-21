#pragma once

#include <SFML/Graphics.hpp>

#include "States/State.hpp"

namespace shootemup
{
class StateStack
{
public:
    enum StackAction
    {
        Push,
        Pop,
        Clear,
    };

    StateStack(const StateStack&) = delete;
    StateStack& operator=(const StateStack&) = delete;

    explicit StateStack(State::Context context);

    template <typename T>
    void register_state(GameState game_state);

    void update(sf::Time delta_time);
    void draw();
    void handle_event(const sf::Event& event);

    void push_state(GameState game_state);
    void pop_state();
    void clear_states();

    [[nodiscard]] bool is_empty() const;

private:
    State::Ptr _create_state(GameState game_state);
    void _apply_pending_changes();

    struct PendingChange
    {
        explicit PendingChange(StackAction action,
                               GameState game_state = GameState::None);

        StackAction action;

        GameState game_state;
    };

    std::vector<State::Ptr> m_state_stack;

    std::vector<PendingChange> m_pending_list;

    State::Context m_context;

    std::map<GameState, std::function<State::Ptr()> > m_factories;
};

}  // namespace shootemup
