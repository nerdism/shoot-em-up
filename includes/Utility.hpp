#pragma once

namespace shootemup
{
float to_radian(float degree);

template <typename NumericType, typename EnumType>
NumericType enum_to_int(EnumType enum_name);

}  // namespace shootemup
