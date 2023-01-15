#pragma once

#include <SFML/Graphics.hpp>

namespace shootemup
{
class Player
{
    void handle_event(const sf::Event& event, CommandQueue& commands);

    void handle_realtime_input(CommandQueue& commands);
};
}  // namespace shootemup
