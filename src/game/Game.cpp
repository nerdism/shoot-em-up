
#include "Game/Game.hpp"

#include <iostream>

#include "Commands/CommandQueue.hpp"
#include "States/GamePlayState.hpp"
#include "States/MenuState.hpp"
#include "States/PauseState.hpp"
#include "States/StateStack.hpp"
#include "States/TitleState.hpp"

using shootemup::CommandQueue;
using shootemup::Game;
using shootemup::GamePlayState;
using shootemup::MenuState;
using shootemup::PauseState;
using shootemup::TitleState;

Game::Game(const uint32_t screen_width, const uint32_t screen_height,
           const std::string& window_title)
    : m_window{sf::VideoMode(screen_width, screen_height), window_title},
      m_state_stack{State::Context{m_window, m_gui, m_texture_holder,
                                   m_font_holder, m_player}}
{
    const uint32_t framerate = 60;
    m_window.setFramerateLimit(framerate);
    m_gui.setTarget(m_window);

    m_texture_holder.load_compiled_resource(
        TextureId::TitleScreen, "resources/images/menu/TitleScreen.png");

    m_font_holder.load_compiled_resource(
        FontId::Main, "resources/gui-theme/kenvector_future.ttf");
    _register_states();

    m_state_stack.push_state(GameState::Title);
}

void Game::main_loop()
{
    const sf::Time delta_time = sf::seconds(1.f / 60.f);
    while (m_window.isOpen())
    {
        _process_inputs();
        _update_game(delta_time);
        _render();
        if (m_state_stack.is_empty())
        {
            m_window.close();
        }
    }
}

void Game::_process_inputs()
{
    sf::Event event;

    while (m_window.pollEvent(event))
    {
        // tgui handle event
        m_gui.handleEvent(event);

        // window close button
        m_state_stack.handle_event(event);

        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }
    }
}

void Game::_update_game(sf::Time delta_time)
{
    m_state_stack.update(delta_time);
}

void Game::_render()
{
    m_window.clear();
    m_state_stack.draw();
    m_window.setView(m_window.getDefaultView());
    m_gui.draw();
    m_window.display();
}

void Game::_register_states()
{
    m_state_stack.register_state<GamePlayState>(GameState::GamePlay);
    m_state_stack.register_state<TitleState>(GameState::Title);
    m_state_stack.register_state<MenuState>(GameState::Menu);
    m_state_stack.register_state<PauseState>(GameState::Pause);
}