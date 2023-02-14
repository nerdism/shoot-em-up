#pragma once

#include <SFML/Graphics.hpp>
#include <type_traits>

namespace shootemup
{
float to_radian(float degree);

// requires std::is_enum_v<EnumType> && std::is_integral_v<NumericType>
template <typename EnumType>
constexpr auto enum_to_int(EnumType enum_name) noexcept
{
    return static_cast<std::underlying_type_t<EnumType>>(enum_name);
}

void center_origin(sf::Sprite& sprite);

}  // namespace shootemup
