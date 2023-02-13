#include "Entities/Projectile.hpp"

#include "Game/DataTables.hpp"
#include "Utility.hpp"

using shootemup::Entity;
using shootemup::Projectile;
using shootemup::ProjectileData;

const std::vector<ProjectileData> Projectile::m_data =
    shootemup::initialize_projectile_data();

Projectile::Projectile(Type type, const TextureHolder& textures)
    : Entity{1},
      m_type{type},
      m_sprite{
          textures.get(m_data[shootemup::enum_to_int<uint32_t>(type)].texture)}
{
    set_velocity(sf::Vector2f(
        0.f, m_data[shootemup::enum_to_int<uint32_t>(type)].speed));
}

uint32_t Projectile::get_category() const
{
    if (m_type == Projectile::AlliedBullet)
    {
        return EntityCategory::AlliedProjectile;
    }

    return EntityCategory::EnemyProjectile;
}

float Projectile::get_max_speed() const
{
    return m_data[shootemup::enum_to_int<uint32_t>(m_type)].speed;
}

int Projectile::get_damage() const
{
    return m_data[shootemup::enum_to_int<uint32_t>(m_type)].damage;
}

void Projectile::_update_current(sf::Time delta_time)
{
    Entity::_update_current(delta_time);
}

void Projectile::_draw_current(sf::RenderTarget& target,
                               sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
