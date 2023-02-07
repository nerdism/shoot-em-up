
#include "Game/TextNode.hpp"

#include <string>

using shootemup::FontHolder;
using shootemup::TextNode;

TextNode::TextNode(const FontHolder& font_holder, const std::string& text)
{
    m_text.setFont(font_holder.get(FontId::Main));
    m_text.setCharacterSize(20);
    set_text(text);
}

void TextNode::set_text(const std::string& text)
{
    m_text.setString(text);

    sf::FloatRect text_node_bounds = m_text.getLocalBounds();
    m_text.setOrigin(
        std::floor(text_node_bounds.left + text_node_bounds.width / 2.f),
        std::floor(text_node_bounds.top + text_node_bounds.height / 2.f));
}

void TextNode::_draw_current(sf::RenderTarget& target,
                             sf::RenderStates states) const
{
    target.draw(m_text, states);
}
