#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "State.hpp"

namespace shootemup
{
class MenuState : public State
{
public:
    MenuState(StateStack& stack, Context context);
    ~MenuState();

    void draw() override;
    bool update(sf::Time delta_time) override;
    bool handle_event(const sf::Event& event) override;

private:
    sf::Sprite m_background_sprite;
    tgui::VerticalLayout::Ptr m_vertical_layout;
    tgui::Label::Ptr m_play_button;
    tgui::Label::Ptr m_exit_button;
};
}  // namespace shootemup
