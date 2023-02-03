#include "States/TitleState.hpp"

using shootemup::TitleState;

TitleState::TitleState(StateStack& stack, Context context)
    : State(stack, context),
      m_show_text{true},
      m_text_effect_time{sf::Time::Zero}
{
    m_background_sprite.setTexture(
        context.textures->get(TextureId::TitleScreen));
    m_text.setFont(context.fonts->get(FontId::Main));
    m_text.setString("Press Any Key To Continue");

    sf::FloatRect bounds = m_text.getLocalBounds();
    m_text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                     std::floor(bounds.top + bounds.height / 2.f));
    m_text.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw()
{
    sf::RenderWindow& window = *(get_context().window);
    window.draw(m_background_sprite);
    if (m_show_text)
    {
        window.draw(m_text);
    }
}
bool TitleState::update(sf::Time delta_time)
{
    m_text_effect_time += delta_time;

    if (m_text_effect_time >= sf::seconds(0.5f))
    {
        m_show_text = !m_show_text;
        m_text_effect_time = sf::Time::Zero;
    }

    return true;
}
bool TitleState::handle_event(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        _request_stack_pop();
        _request_stack_push(GameState::Menu);
    }
    return true;
}
