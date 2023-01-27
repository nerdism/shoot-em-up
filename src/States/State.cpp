
#include "States/State.hpp"

using shootemup::State;

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures,
                        Player& player)
    : window{&window},
      textures{&textures},
      player{&player}
{
}