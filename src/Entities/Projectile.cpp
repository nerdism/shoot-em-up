#include "Entities/Projectile.hpp"

using shootemup::Projectile;

Projectile::Projectile(Type type, const TextureHolder& textures)
    : Entity{1},
      m_type{type},
      m_sprite{}
{
}
