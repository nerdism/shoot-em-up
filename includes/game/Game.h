#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <string>

#include "game/GameState.h"

namespace shootemup
{

class Game
{
public:
    Game(uint32_t screen_width, uint32_t screen_height,
         const std::string& window_title);

    void mainloop();

private:
    void _update_game();

    void _handle_event();

    void _render();

    sf::RenderWindow _window;

    std::stack<GameStatePtr> _game_states;
};

}  // namespace shootemup
