#pragma once

#include "Game/Player.hpp"
#include "Game/World.hpp"
#include "StateStack.hpp"

namespace shootemup
{

class GamePlayState : public State
{
public:
    GamePlayState(StateStack& stack, Context context);
    void draw() override;
    bool update(sf::Time dt) override;
    bool handle_event(const sf::Event& event) override;

private:
    // World mWorld;
    // Player& mPlayer;
};

}  // namespace shootemup
