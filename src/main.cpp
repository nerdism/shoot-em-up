
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Game/Game.hpp"

using shootemup::Game;

int main()
{
    const uint32_t screen_width = 640;
    const uint32_t screen_height = 480;

    try
    {
        Game game{screen_width, screen_height, "ShootEmUp"};
        game.main_loop();
    }
    catch (std::exception& e)
    {
        std::cout << "\nException: " << e.what() << std::endl;
    }

    return 0;
}
