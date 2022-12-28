
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <vector>

#include "game/game.h"

using shootemup::Game;

int main()
{
    const uint32_t screen_width = 1280;
    const uint32_t screen_height = 768;

    Game game{screen_width, screen_height, "Hello Window"};

    game.mainloop();

    return 0;
}
