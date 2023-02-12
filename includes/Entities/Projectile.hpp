#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "ResourceManager/ResourceManager.hpp"

namespace shootemup
{
class Projectile : public Entity
{
public:
    enum Type
    {
        AlliedBullet,
        EnemyBullet,
        Missile,
        TypeCount
    };

public:
    Projectile(Type type, const TextureHolder& textures);

    void guide_towards(sf::Vector2f position);
    bool is_guided() const;

    unsigned int get_category() const override;
    sf::FloatRect get_bounding_rect() const;
    float get_max_speed() const;
    int get_damage() const;

private:
    void _update_current(sf::Time dt) override;

    void _draw_current(sf::RenderTarget& target,
                       sf::RenderStates states) const override;

private:
    Type m_type;
    sf::Sprite m_sprite;
    sf::Vector2f m_target_direction;
};
}  // namespace shootemup
