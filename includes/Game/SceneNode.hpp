#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "Commands/Command.hpp"

namespace shootemup
{

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
                               sf::RenderStates states) const;

    sf::Transform get_world_transform() const;

    sf::Vector2f get_world_position() const;

    virtual uint32_t get_category() const;

    void on_command(const Command& command, sf::Time delta_time);

protected:
    virtual void _update_current(sf::Time delta_time);

private:
    void _update_children(sf::Time delta_time);

    std::vector<Ptr> m_children;
    SceneNode* m_parent;
};

}  // namespace shootemup
