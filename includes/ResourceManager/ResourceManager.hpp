
#pragma once
#include <SFML/Graphics.hpp>
#include <cmrc/cmrc.hpp>
#include <map>
#include <memory>

CMRC_DECLARE(game_resources);

namespace shootemup
{

enum class FontId
{
    Main
};

enum class TextureId
{
    TitleScreen,
    Desert,
    Airplane_Eagle,
    Airplane_Raptor,
    Airplane_Avenger,
};

template <typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder = ResourceHolder<sf::Texture, TextureId>;
using FontHolder = ResourceHolder<sf::Font, FontId>;

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    void load(Identifier resource_id, const std::string &file_name);
    void load_compiled_resource(Identifier resource_id,
                                const std::string &file_name);

    Resource &get(Identifier resource_id);
    const Resource &get(Identifier resource_id) const;

private:
    std::map<Identifier, std::unique_ptr<Resource>> m_resource_map;
};

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier resource_id,
                                                const std::string &file_name)
{
    std::unique_ptr<Resource> resource_ptr = std::make_unique<Resource>();
    resource_ptr->loadFromFile(file_name);

    m_resource_map.insert(std::make_pair(resource_id, std::move(resource_ptr)));
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load_compiled_resource(
    Identifier resource_id, const std::string &file_name)
{
    std::unique_ptr<Resource> resource_ptr = std::make_unique<Resource>();

    auto resource_fs = cmrc::game_resources::get_filesystem();
    auto compiled_resource = resource_fs.open(file_name);
    resource_ptr->loadFromMemory(compiled_resource.begin(),
                                 compiled_resource.size());

    m_resource_map.insert(std::make_pair(resource_id, std::move(resource_ptr)));
}

template <typename Resource, typename Identifier>
Resource &ResourceHolder<Resource, Identifier>::get(Identifier resource_id)
{
    auto element = m_resource_map.find(resource_id);
    return *element->second;
}

template <typename Resource, typename Identifier>
const Resource &ResourceHolder<Resource, Identifier>::get(
    Identifier resource_id) const
{
    auto element = m_resource_map.find(resource_id);
    return *element->second;
}

}  // namespace shootemup
