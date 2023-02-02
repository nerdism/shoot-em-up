#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"

namespace shootemup
{
class TitleState : public State
{
public:
    TitleState(StateStack& stack, Context context);
    void draw() override;
    bool update(sf::Time delta_time) override;
    bool handle_event(const sf::Event& event) override;

private:
    sf::Sprite m_background_sprite;
    sf::Text m_text;

    bool m_show_text;
    sf::Time m_text_effect_time;
};
}  // namespace shootemup
