#pragma once
#include "ResourceManager/ResourceManager.hpp"
#include "SceneNode.hpp"

namespace shootemup
{
class TextNode : public SceneNode
{
public:
    TextNode(const FontHolder& font_holder, const std::string& text);
    void set_text(const std::string& text);

private:
    void _draw_current(sf::RenderTarget& target,
                       sf::RenderStates states) const override;

    sf::Text m_text;
};
}  // namespace shootemup
