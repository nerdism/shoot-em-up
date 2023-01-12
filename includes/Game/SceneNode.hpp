#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace shootemup
{

enum class SceneLayer
{
    Background,
    Air,
    LayerCount
};

class SceneNode : public sf::Drawable, public sf::Transformable
{
public:
    using Ptr = std::unique_ptr<SceneNode>;

    SceneNode() { m_parent = nullptr; };

    SceneNode(const SceneNode&) = delete;
    SceneNode& operator=(const SceneNode&) = delete;

    void attach_child(Ptr child);
    Ptr dettach_child(const SceneNode& node);

    void update(sf::Time delta_time);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    virtual void _draw_current(sf::RenderTarget& target,
                               sf::RenderStates states) const = 0;

    sf::Transform get_world_transform() const;

    sf::Vector2f get_world_position() const;

protected:
    virtual void _update_current(sf::Time delta_time) = 0;

private:
    void _update_children(sf::Time delta_time);

    std::vector<Ptr> m_children;
    SceneNode* m_parent;
};

class SpriteNode : public SceneNode
{
public:
    explicit SpriteNode(const sf::Texture& texture);
    SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

private:
    void _draw_current(sf::RenderTarget& target,
                       sf::RenderStates states) const override;

    sf::Sprite m_sprite;
};

}  // namespace shootemup
