#include "Entities/Projectile.hpp"

#include "Game/DataTables.hpp"
#include "Utility.hpp"

using shootemup::CommandQueue;
using shootemup::Entity;
using shootemup::Projectile;
using shootemup::ProjectileData;

const std::vector<ProjectileData> Projectile::m_data =
    shootemup::initialize_projectile_data();

Projectile::Projectile(Type type, const TextureHolder& textures)
    : Entity{1},
      m_type{type},
      m_sprite{textures.get(m_data[shootemup::enum_to_int(type)].texture)}
{
    center_origin(m_sprite);
    set_velocity(
        -sf::Vector2f(0.f, m_data[shootemup::enum_to_int(type)].speed));
}

uint32_t Projectile::get_category() const
{
    if (m_type == Projectile::Type::AlliedBullet)
    {
        return shootemup::enum_to_int(EntityCategory::AlliedProjectile);
    }

    return shootemup::enum_to_int(EntityCategory::EnemyProjectile);
}

float Projectile::get_max_speed() const
{
    return m_data[shootemup::enum_to_int(m_type)].speed;
}

int Projectile::get_damage() const
{
    return m_data[shootemup::enum_to_int(m_type)].damage;
}

void Projectile::_update_current(sf::Time delta_time,
                                 CommandQueue& command_queue)
{
    Entity::_update_current(delta_time, command_queue);
}

void Projectile::_draw_current(sf::RenderTarget& target,
                               sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

sf::FloatRect Projectile::get_bounding_rect() const
{
    // TODO: did not understand this
    return get_world_transform().transformRect(m_sprite.getGlobalBounds());
}