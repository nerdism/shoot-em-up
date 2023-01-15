#include "Entities/AirCraft.hpp"

#include "Commands/Command.hpp"

using shootemup::Aircraft;

Aircraft::Aircraft(Type type,
                   const ResourceHolder<sf::Texture, TextureId>& texture_holder)
    : m_type{type}
{
    if (type == Type::Raptor)
    {
        m_sprite.setTexture(texture_holder.get(TextureId::Airplane_Raptor));
    }
    else
    {
        m_sprite.setTexture(texture_holder.get(TextureId::Airplane_Eagle));
    }

    const sf::FloatRect rect = m_sprite.getLocalBounds();
    m_sprite.setOrigin(rect.width / 2.f, rect.height / 2.f);
}

void Aircraft::_draw_current(sf::RenderTarget& target,
                             sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

uint32_t Aircraft::get_category() const
{
    switch (m_type)
    {
        case Type::Eagle:
            return EntityCategory::PlayerAircraft;

        default:
            return EntityCategory::EnemyAircraft;
    }
}
