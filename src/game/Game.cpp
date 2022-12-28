
#include "game/Game.h"

#include <Thor/Resources.hpp>

#include "game/MainMenuState.h"

using shootemup::Game;
using shootemup::GameStatePtr;

Game::Game(const uint32_t screen_width, const uint32_t screen_height,
           const std::string& window_title)
    : _window{sf::VideoMode(screen_width, screen_height), window_title}
{
    const uint32_t framerate = 60;

    _window.setFramerateLimit(framerate);

    _game_states.push(std::move(std::make_unique<MainMenuState>(_window)));
}

void Game::mainloop()
{
    while (_window.isOpen())
    {
        _handle_event();
        _update_game();
        _render();
    }
}

void Game::_handle_event()
{
    sf::Event event;

    while (_window.pollEvent(event))
    {
        // window close button
        if (event.type == sf::Event::Closed)
        {
            _window.close();
        }

        const GameStatePtr& current_state = _game_states.top();

        current_state->handle_events(event, _window);

        // if (event.type == sf::Event::KeyPressed)
        //{
        //     // fullscreen _window for demonestration
        //     if (event.key.code == sf::Keyboard::Escape)
        //     {
        //         _window.close();
        //     }
        // }
    }
}

void Game::_update_game() {}

void Game::_render()
{
    _window.clear(sf::Color::White);

    const GameStatePtr& current_state = _game_states.top();
    current_state->render(_window);

    _window.display();
}