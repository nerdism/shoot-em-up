
#include "States/MenuState.hpp"

#include "States/StateStack.hpp"

using shootemup::MenuState;

MenuState::MenuState(StateStack& stack, Context context)
    : State{stack, context},
      m_options{},
      m_option_index(0)
{
    sf::Texture& texture = context.textures->get(TextureId::TitleScreen);
    sf::Font& font = context.fonts->get(FontId::Main);

    m_background_sprite.setTexture(texture);

    // A simple menu demonstration
    sf::Text play_option;
    play_option.setFont(font);
    play_option.setString("Play");
    sf::FloatRect play_option_bounds = play_option.getLocalBounds();
    play_option.setOrigin(
        std::floor(play_option_bounds.left + play_option_bounds.width / 2.f),
        std::floor(play_option_bounds.top + play_option_bounds.height / 2.f));
    play_option.setPosition(context.window->getView().getSize() / 2.f);
    m_options.push_back(play_option);

    sf::Text exit_option;
    exit_option.setFont(font);
    exit_option.setString("Exit");
    sf::FloatRect exit_option_bounds = exit_option.getLocalBounds();
    exit_option.setOrigin(
        std::floor(exit_option_bounds.left + exit_option_bounds.width / 2.f),
        std::floor(exit_option_bounds.top + exit_option_bounds.height / 2.f));

    exit_option.setPosition(play_option.getPosition() +
                            sf::Vector2f(0.f, 30.f));
    m_options.push_back(exit_option);

    update_option_text();
}

void MenuState::draw()
{
    sf::RenderWindow& window = *(get_context().window);
    window.draw(m_background_sprite);
    for (auto& option : m_options)
    {
        window.draw(option);
    }
}

bool MenuState::update(sf::Time delta_time)
{
    return false;
}

bool MenuState::handle_event(const sf::Event& event)
{
    // The demonstration menu logic
    if (event.type != sf::Event::KeyPressed)
    {
        return false;
    }

    if (event.key.code == sf::Keyboard::Return ||
        event.key.code == sf::Keyboard::Space)
    {
        if (m_option_index == static_cast<std::size_t>(OptionNames::Play))
        {
            _request_stack_pop();
            _request_stack_push(GameState::GamePlay);
        }
        else if (m_option_index == static_cast<std::size_t>(OptionNames::Exit))
        {
            // The exit option was chosen, by removing itself, the stack will be
            // empty, and the game will know it is time to close.
            _request_stack_pop();
        }
    }

    else if (event.key.code == sf::Keyboard::Up ||
             event.key.code == sf::Keyboard::W)
    {
        // Decrement and wrap-around
        if (m_option_index > 0)
        {
            m_option_index--;
        }
        else
        {
            m_option_index = m_options.size() - 1;
        }

        update_option_text();
    }

    else if (event.key.code == sf::Keyboard::Down ||
             event.key.code == sf::Keyboard::S)
    {
        // Increment and wrap-around
        if (m_option_index < m_options.size() - 1)
        {
            m_option_index++;
        }
        else
        {
            m_option_index = 0;
        }

        update_option_text();
    }
    return false;
}

void MenuState::update_option_text()
{
    if (m_options.empty())
    {
        return;
    }
    // White all texts
    for (auto& option : m_options)
    {
        option.setColor(sf::Color::White);
    }
    // Red the selected text
    m_options[m_option_index].setColor(sf::Color::Red);
}
