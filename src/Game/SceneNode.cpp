#include "Game/SceneNode.hpp"

#include <cassert>

#include "Commands/Command.hpp"
#include "Utility.hpp"

using shootemup::CommandQueue;
using shootemup::EntityCategory;
using shootemup::SceneNode;

SceneNode::SceneNode(EntityCategory type)
    : m_parent{nullptr},
      m_category{type}
{
}

void SceneNode::attach_child(Ptr child)
{
    child->m_parent = this;
    m_children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::dettach_child(const SceneNode& node)
{
    auto found =
        std::find_if(m_children.begin(), m_children.end(),
                     [&](Ptr& ptr) -> bool { return ptr.get() == &node; });
    assert(found != m_children.end());
    Ptr result = std::move(*found);
    result->m_parent = nullptr;
    m_children.erase(found);
    return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    _draw_current(target, states);
    draw_bounding_rect(target, states);

    for (const auto& iter : m_children)
    {
        iter->draw(target, states);
    }
}

void SceneNode::update(sf::Time delta_time, CommandQueue& command_queue)
{
    _update_current(delta_time, command_queue);
    _update_children(delta_time, command_queue);
}

void SceneNode::_update_children(sf::Time delta_time,
                                 CommandQueue& command_queue)
{
    for (const auto& iter : m_children)
    {
        iter->update(delta_time, command_queue);
    }
}

sf::Transform SceneNode::get_world_transform() const
{
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode* node = this; node != nullptr; node = node->m_parent)
    {
        transform = node->getTransform() * transform;
    }

    return transform;
}

void SceneNode::_draw_current(sf::RenderTarget& target,
                              sf::RenderStates states) const
{
}

void SceneNode::_update_current(sf::Time delta_time,
                                CommandQueue& command_queue)
{
}

sf::Vector2f SceneNode::get_world_position() const
{
    return get_world_transform() * sf::Vector2f();
}

uint32_t SceneNode::get_category() const
{
    return shootemup::enum_to_int(m_category);
}

void SceneNode::on_command(const Command& command, sf::Time delta_time)
{
    const uint32_t and_result = command.category & get_category();
    if (static_cast<bool>(and_result))
    {
        command.action(*this, delta_time);
    }

    for (const auto& iter : m_children)
    {
        iter->on_command(command, delta_time);
    }
}

sf::FloatRect SceneNode::get_bounding_rect() const
{
    return sf::FloatRect();
}

void SceneNode::draw_bounding_rect(sf::RenderTarget& target,
                                   sf::RenderStates states) const
{
    sf::FloatRect rect = get_bounding_rect();

    sf::RectangleShape shape;
    shape.setPosition(sf::Vector2f(rect.left, rect.top));
    shape.setSize(sf::Vector2f(rect.width, rect.height));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(1.f);

    target.draw(shape);
}

bool shootemup::collision(const SceneNode& lhs, const SceneNode& rhs)
{
    return lhs.get_bounding_rect().intersects(rhs.get_bounding_rect());
}
