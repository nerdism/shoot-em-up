
#include "Game/Game.hpp"

#include <iostream>

using shootemup::Game;

Game::Game(const uint32_t screen_width, const uint32_t screen_height,
           const std::string& window_title)
    : m_window{sf::VideoMode(screen_width, screen_height), window_title}
{
    const uint32_t framerate = 60;
    m_window.setFramerateLimit(framerate);

    m_resource_holder.load_compiled_resource(
        TextureId::Airplane, "resources/images/gameplay/Eagle.png");
}

void Game::main_loop()
{
    while (m_window.isOpen())
    {
        _handle_event();
        _update_game();
        _render();
    }
}

void Game::_handle_event()
{
    sf::Event event;

    while (m_window.pollEvent(event))
    {
        // window close button
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }

        // if (event.type == sf::Event::KeyPressed)
        //{
        //     // fullscreen m_window for demonestration
        //     if (event.key.code == sf::Keyboard::Escape)
        //     {
        //         m_window.close();
        //     }
        // }
    }
}

void Game::_update_game() {}

void Game::_render()
{
    m_window.clear(sf::Color::White);
    m_window.display();
}