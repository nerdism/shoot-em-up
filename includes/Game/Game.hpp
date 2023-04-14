#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
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

    void _load_textures();

    void _load_fonts();

    sf::RenderWindow m_window;
    TextureHolder m_texture_holder;
    FontHolder m_font_holder;
    Player m_player;

    StateStack m_state_stack;
    tgui::GuiSFML m_gui;
};

}  // namespace shootemup
