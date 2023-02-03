
#include "States/MenuState.hpp"

#include "States/StateStack.hpp"

using shootemup::MenuState;

MenuState::MenuState(StateStack& stack, Context context)
    : State{stack, context}
{
    sf::Texture& texture = context.textures->get(TextureId::TitleScreen);
    sf::Font& font = context.fonts->get(FontId::Main);
    m_background_sprite.setTexture(texture);

    tgui::GuiSFML& gui = *context.gui;
    m_play_button = tgui::Button::create();

    m_play_button->setText("Play");
    // m_play_button->setPosition("50%", "50%");
    // m_play_button->setSize("15%", "5%");
    m_play_button->onPress(
        [&]
        {
            _request_stack_pop();
            _request_stack_push(GameState::GamePlay);
        });

    m_exit_button = tgui::Button::create();
    m_exit_button->setText("Exit");
    // m_exit_button->setPosition("50%", "50%");
    // m_exit_button->setSize("15%", "5%");
    m_exit_button->onPress([&] { _request_stack_clear(); });

    m_vertical_layout = tgui::VerticalLayout::create();
    m_vertical_layout->setOrigin(0.5f, 0.5f);
    m_vertical_layout->setPosition("50%", "50%");
    m_vertical_layout->setSize("30%", "20%");
    m_vertical_layout->add(m_play_button);
    m_vertical_layout->add(m_exit_button);
    m_vertical_layout->insertSpace(0, 0.8f);

    gui.add(m_vertical_layout);
}

MenuState::~MenuState()
{
    tgui::GuiSFML& gui = *get_context().gui;
    gui.remove(m_vertical_layout);
}

void MenuState::draw()
{
    sf::RenderWindow& window = *(get_context().window);
    window.draw(m_background_sprite);
}

bool MenuState::update(sf::Time delta_time)
{
    return false;
}

bool MenuState::handle_event(const sf::Event& event)
{
    return false;
}
