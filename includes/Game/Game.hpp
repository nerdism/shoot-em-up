#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <string>

#include "Entities/Aircraft.hpp"
#include "Player.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "States/StateStack.hpp"
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

    void _process_inputs();

    void _render();

    void _register_states();

    sf::RenderWindow m_window;
    TextureHolder m_texture_holder;
    Player m_player;

    StateStack m_state_stack;
};

}  // namespace shootemup
