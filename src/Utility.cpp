#include "Utility.hpp"

float shootemup::to_radian(float degree)
{
    return 3.141592653589793238462643383f / 180.f * degree;
}

template <typename NumericType, typename EnumType>
NumericType shootemup::enum_to_int(EnumType enum_name)
{
    return static_cast<NumericType>(enum_name);
}
