#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <set>
#include <vector>

#include "Commands/Command.hpp"
#include "Commands/CommandQueue.hpp"
#include "Entities/EntityCategory.hpp"

namespace shootemup
{
class Command;
using CommandQueue = std::queue<Command>;

class SceneNode : public sf::Drawable, public sf::Transformable
{
public:
    using Ptr = std::unique_ptr<SceneNode>;
    using Pair = std::pair<SceneNode*, SceneNode*>;

    SceneNode(EntityCategory type = EntityCategory::None);

    SceneNode(const SceneNode&) = delete;

    SceneNode& operator=(const SceneNode&) = delete;

    void attach_child(Ptr child);

    Ptr dettach_child(const SceneNode& node);

    void update(sf::Time delta_time, CommandQueue& command_queue);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    virtual void _draw_current(sf::RenderTarget& target,
                               sf::RenderStates states) const;

    sf::Transform get_world_transform() const;

    sf::Vector2f get_world_position() const;

    virtual uint32_t get_category() const;

    void on_command(const Command& command, sf::Time delta_time);

    virtual sf::FloatRect get_bounding_rect() const;

    void check_node_colission(SceneNode& node, std::set<Pair>& colission_pairs);
    void check_scene_colission(SceneNode& scene_graph,
                               std::set<Pair>& colission_pairs);

    void remove_destroyed_nodes();

    virtual bool is_destroyed() const;

    virtual bool is_marked_for_removal() const;

protected:
    virtual void _update_current(sf::Time delta_time,
                                 CommandQueue& command_queue);

private:
    void _update_children(sf::Time delta_time, CommandQueue& command_queue);

    void draw_bounding_rect(sf::RenderTarget& target,
                            sf::RenderStates states) const;

    std::vector<Ptr> m_children;
    SceneNode* m_parent;
    EntityCategory m_category;
};

bool collision(const SceneNode& lhs, const SceneNode& rhs);

}  // namespace shootemup
