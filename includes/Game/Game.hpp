#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <string>

#include "Entities/Aircraft.hpp"
#include "ResourceManager/ResourceManager.hpp"

namespace shootemup
{

class Game
{
public:
    Game(uint32_t screen_width, uint32_t screen_height,
         const std::string& window_title);

    void main_loop();

private:
    void _update_game();

    void _handle_event();

    void _render();

    sf::RenderWindow m_window;

    ResourceHolder<sf::Texture, TextureId> m_resource_holder;
};

}  // namespace shootemup
