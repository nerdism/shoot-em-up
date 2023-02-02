#pragma once

#include <SFML/Graphics.hpp>

#include "Game/Player.hpp"
#include "ResourceManager/ResourceManager.hpp"

namespace shootemup
{
class StateStack;
class Player;

enum class GameState
{
    None,
    Title,
    Menu,
    GamePlay,
    Loading,
    Pause
};

class State
{
public:
    using Ptr = std::unique_ptr<State>;

    struct Context
    {
        Context(sf::RenderWindow& window, TextureHolder& textures,
                FontHolder& fonts, Player& player);

        sf::RenderWindow* window;
        TextureHolder* textures;
        FontHolder* fonts;
        Player* player;
    };

    State(StateStack& stack, Context context);
    virtual ~State() = default;

    virtual void draw() = 0;
    virtual bool update(sf::Time delta_time) = 0;
    virtual bool handle_event(const sf::Event& event) = 0;

protected:
    void _request_stack_push(GameState game_state);
    void _request_stack_pop();
    void _request_state_clear();

    [[nodiscard]] Context get_context() const;

private:
    StateStack* m_state_stack;
    Context m_context;
};
}  // namespace shootemup
