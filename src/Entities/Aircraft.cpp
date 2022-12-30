#include "Entities/AirCraft.hpp"

using shootemup::Aircraft;

Aircraft::Aircraft(Type type,
                   const ResourceHolder<sf::Texture, TextureId>& texture_holder)
    : m_type{type}
{
    if (type == Type::Eagle)
        m_sprite.setTexture(texture_holder.get(TextureId::Airplane));
    else
        m_sprite.setTexture(texture_holder.get(TextureId::Airplane));

    sf::FloatRect rect = m_sprite.getLocalBounds();
    m_sprite.setOrigin(rect.width, rect.height);
}

void Aircraft::_draw_current(sf::RenderTarget& target,
                             sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
