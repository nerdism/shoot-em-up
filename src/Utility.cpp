#include "Utility.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <concepts>

float shootemup::to_radian(float degree)
{
    return 3.141592653589793238462643383f / 180.f * degree;
}

void shootemup::center_origin(sf::Sprite& sprite)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                     std::floor(bounds.top + bounds.height / 2.f));
}
