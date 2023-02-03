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

    void draw() override;
    bool update(sf::Time delta_time) override;
    bool handle_event(const sf::Event& event) override;

    void update_option_text();

private:
    enum class OptionNames
    {
        Play,
        Exit,
    };

private:
    sf::Sprite m_background_sprite;
    std::vector<sf::Text> m_options;
    std::size_t m_option_index;
};
}  // namespace shootemup
