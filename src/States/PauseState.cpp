#include "States/PauseState.hpp"

using shootemup::PauseState;

PauseState::PauseState(StateStack& stack, Context context)
    : State{stack, context}
{
    sf::Font& font = context.fonts->get(FontId::Main);
    sf::Vector2f view_size = context.window->getView().getSize();

    m_paused_text.setFont(font);
    m_paused_text.setString("Game Paused");
    m_paused_text.setCharacterSize(70);
    m_paused_text.setPosition(0.5f * view_size.x, 0.4f * view_size.y);

    sf::FloatRect pause_text_bounds = m_paused_text.getLocalBounds();
    m_paused_text.setOrigin(
        std::floor(pause_text_bounds.left + pause_text_bounds.width / 2.f),
        std::floor(pause_text_bounds.top + pause_text_bounds.height / 2.f));

    m_instruction_text.setFont(font);
    m_instruction_text.setString(
        "(Press Backspace to return to the main menu)");
    m_instruction_text.setCharacterSize(15);
    m_instruction_text.setPosition(0.5f * view_size.x, 0.6f * view_size.y);

    sf::FloatRect instruction_text_bounds = m_instruction_text.getLocalBounds();
    m_instruction_text.setOrigin(
        std::floor(instruction_text_bounds.left +
                   instruction_text_bounds.width / 2.f),
        std::floor(instruction_text_bounds.top +
                   instruction_text_bounds.height / 2.f));
}

void PauseState::draw()
{
    sf::RenderWindow& window = *(get_context().window);
    window.setView(window.getDefaultView());

    sf::RectangleShape rectangle_shape;
    rectangle_shape.setFillColor(sf::Color(0, 0, 0, 150));
    rectangle_shape.setSize(sf::Vector2f(window.getSize()));
    window.draw(rectangle_shape);
    window.draw(m_paused_text);
    window.draw(m_instruction_text);
}
bool PauseState::update(sf::Time delta_time)
{
    return false;
}
bool PauseState::handle_event(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape)
    {
        _request_stack_pop();
    }
    else if (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::BackSpace)
    {
        _request_stack_clear();
        _request_stack_push(GameState::Menu);
    }
    return false;
}
