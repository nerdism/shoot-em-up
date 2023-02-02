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
    bool update(sf::Time delta_time) override;
    bool handle_event(const sf::Event& event) override;

private:
    World m_world;
    Player& m_player;
};

}  // namespace shootemup
