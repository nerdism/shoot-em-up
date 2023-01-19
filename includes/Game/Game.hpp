#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <string>

#include "Entities/Aircraft.hpp"
#include "Player.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "World.hpp"

namespace shootemup
{

class Game
{
public:
    Game(uint32_t screen_width, uint32_t screen_height,
         const std::string& window_title);

    void main_loop();

private:
    void _update_game(sf::Time delta_time);

    void _handle_event();

    void _render();

    sf::RenderWindow m_window;
    World m_world;
    Player m_player;
};

}  // namespace shootemup
