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

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    virtual void _draw_current(sf::RenderTarget& target,
                               sf::RenderStates states) const = 0;

private:
    std::vector<Ptr> m_children;
    SceneNode* m_parent;
};

}  // namespace shootemup
