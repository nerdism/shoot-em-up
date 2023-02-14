#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "Game/DataTables.hpp"
#include "ResourceManager/ResourceManager.hpp"

namespace shootemup
{
class Projectile : public Entity
{
public:
    enum class Type
    {
        AlliedBullet,
        EnemyBullet,
        Missile,
        TypeCount
    };

    Projectile(Type type, const TextureHolder& textures);

    void guide_towards(sf::Vector2f position);
    bool is_guided() const;

    uint32_t get_category() const override;
    // sf::FloatRect get_bounding_rect() const;
    float get_max_speed() const;
    int get_damage() const;

private:
    void _update_current(sf::Time delta_time) override;

    void _draw_current(sf::RenderTarget& target,
                       sf::RenderStates states) const override;

    Type m_type;
    sf::Sprite m_sprite;
    sf::Vector2f m_target_direction;

    static const std::vector<ProjectileData> m_data;
};
}  // namespace shootemup
