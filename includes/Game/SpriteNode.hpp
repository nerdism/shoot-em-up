#pragma once
#include "SceneNode.hpp"

namespace shootemup
{
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
