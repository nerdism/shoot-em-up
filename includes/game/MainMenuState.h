#pragma once
#include <SFML/Audio.hpp>
#include <TGUI/TGUI.hpp>

#include "game/GameState.h"

namespace shootemup
{
class MainMenuState : public GameState
{
public:
    explicit MainMenuState(sf::RenderWindow& window);

    void handle_events(const sf::Event& event,
                       sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
    void update() override;

private:
    tgui::GuiSFML _gui;
};
}  // namespace shootemup
