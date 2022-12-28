

#include "game/MainMenuState.h"

#include <SFML/Audio.hpp>
#include <TGUI/TGUI.hpp>
#include <cmrc/cmrc.hpp>
#include <memory>

CMRC_DECLARE(game_resources);

using shootemup::MainMenuState;

class CustomThemeLoader : public tgui::DefaultThemeLoader
{
protected:
    std::unique_ptr<tgui::DataIO::Node> readFile(
        const tgui::String& themeName) const override
    {
        std::stringstream ss;
        auto fs = cmrc::game_resources::get_filesystem();
        auto theme = fs.open(themeName.toStdString());
        ss << theme.cbegin();

        // Load the theme file from the zip here and store the file contents in
        // the string stream. On error, either return nullptr or throw an
        // exception.

        return tgui::DataIO::parse(ss);
    }
};

bool customTextureLoader(tgui::BackendTextureBase& texture,
                         const tgui::String& imageId)
{
    auto fs = cmrc::game_resources::get_filesystem();
    sf::Image image;
    std::string theme_resource = "resources/gui-theme/" + imageId.toStdString();
    auto theme_image = fs.open(theme_resource);
    image.loadFromMemory(theme_image.cbegin(), theme_image.size());
    tgui::Vector2u imageSize(image.getSize().x, image.getSize().y);

    const size_t image_size_byte = image.getSize().x * image.getSize().y * 4;
    std::unique_ptr<uint8_t[]> pixels =
        std::make_unique<uint8_t[]>(image_size_byte);

    std::copy(image.getPixelsPtr(), (image.getPixelsPtr() + image_size_byte),
              pixels.get());

    // uint8_t myarray[] = static_cast<uint8_t[]>(ptr2);

    return texture.load(imageSize, std::move(pixels));
}

MainMenuState::MainMenuState(sf::RenderWindow& window)
{
    _gui.setTarget(window);

    tgui::Theme::setThemeLoader(std::make_shared<CustomThemeLoader>());
    tgui::Texture::setBackendTextureLoader(customTextureLoader);
    tgui::Theme::setDefault("resources/gui-theme/green.txt");

    auto fs = cmrc::game_resources::get_filesystem();
    auto kenny_font = fs.open("resources/gui-theme/Blomberg-8MKKZ.otf");

    tgui::Font font(kenny_font.begin(), kenny_font.size());

    tgui::VerticalLayout::Ptr menu_buttons_vlayout =
        tgui::VerticalLayout::create();
    menu_buttons_vlayout->setOrigin(0.5f, 0.5f);
    menu_buttons_vlayout->setSize("20%", "50%");
    menu_buttons_vlayout->setPosition("50%", "50%");
    menu_buttons_vlayout->setInheritedFont(font);
    menu_buttons_vlayout->setTextSize(30);

    const tgui::Button::Ptr play_game_button =
        tgui::Button::create("Play Game");
    const tgui::Button::Ptr settings_button = tgui::Button::create("Settings");
    const tgui::Button::Ptr exit_button = tgui::Button::create("Exit");
    // auto fs = cmrc::game_resources::get_filesystem();
    // auto click_sound_file = fs.open("resources/sounds/gui/click1.ogg");

    menu_buttons_vlayout->add(play_game_button);
    menu_buttons_vlayout->add(settings_button);
    menu_buttons_vlayout->add(exit_button);
    menu_buttons_vlayout->insertSpace(2, 0.8f);
    menu_buttons_vlayout->insertSpace(1, 0.8f);

    tgui::Label::Ptr label = tgui::Label::create("Shoot Em up");
    label->setOrigin(0.5f, 0.5f);
    label->setPosition("50%", "15%");
    label->setInheritedFont(font);
    label->setTextSize(90);
    label->getRenderer()->setTextColor(tgui::Color::Green);
    _gui.add(label);
    _gui.add(menu_buttons_vlayout);
}

void MainMenuState::render(sf::RenderWindow& /*window*/) { _gui.draw(); }

void MainMenuState::handle_events(const sf::Event& event,
                                  sf::RenderWindow& window)
{
    _gui.handleEvent(event);
    if (event.type == sf::Event::KeyPressed)
    {
        // fullscreen _window for demonestration
        if (event.key.code == sf::Keyboard::Escape)
        {
            window.close();
        }
    }
}

void MainMenuState::update() {}
