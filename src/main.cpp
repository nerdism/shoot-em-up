
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "game/game.hpp"

using shootemup::Game;

int main()
{
    const uint32_t screen_width = 640;
    const uint32_t screen_height = 480;

    Game game{screen_width, screen_height, "Hello Window"};

    game.main_loop();

    return 0;
}
