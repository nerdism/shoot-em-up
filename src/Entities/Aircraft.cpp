#include "Entities/AirCraft.hpp"

#include "Commands/Command.hpp"

using shootemup::Aircraft;

Aircraft::Aircraft(Type type, const TextureHolder& texture_holder,
                   const FontHolder& font_holder)
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
    std::unique_ptr<TextNode> text_node =
        std::make_unique<TextNode>(font_holder, "");
    m_health_display = text_node.get();
    attach_child(std::move(text_node));

    m_health_display->setPosition(0.f, 50.f);
    m_health_display->set_text("100 HP");
    m_health_display->setRotation(-getRotation());
}

void Aircraft::_draw_current(sf::RenderTarget& target,
                             sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

void Aircraft::_update_current(sf::Time delta_time)
{
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
