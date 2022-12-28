#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

namespace shootemup
{

class GameState
{
public:
    virtual void render(sf::RenderWindow& window) = 0;

    virtual void handle_events(const sf::Event& event,
                               sf::RenderWindow& window) = 0;

    virtual void update() = 0;
};

using GameStatePtr = std::unique_ptr<GameState>;

}  // namespace shootemup
