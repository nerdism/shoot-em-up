#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "State.hpp"

namespace shootemup
{
class PauseState : public State
{
public:
    PauseState(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time delta_time) override;
    bool handle_event(const sf::Event& event) override;

private:
    sf::Text m_paused_text;
    sf::Text m_instruction_text;
};
}  // namespace shootemup