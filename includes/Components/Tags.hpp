#pragma once

#include <entt/entt.hpp>

namespace shootemup
{

namespace tag
{
using namespace entt::literals;

using RootSceneNode = entt::tag<"root scene node"_hs>;

using BackgroundLayerScenenNode = entt::tag<"Background layer scene node"_hs>;
using AirLayerScenenNode = entt::tag<"Air layer scene node"_hs>;
using AirLayerEntity = entt::tag<"air layer drawable entities"_hs>;

using Aircraft = entt::tag<"aircraft"_hs>;
using PlayerAircraft = entt::tag<"player aircraft"_hs>;
using EnemyAircraft = entt::tag<"enemy aircraft"_hs>;
using Bullet = entt::tag<"aircraft bullet"_hs>;
using PlayerBullet = entt::tag<"player aircraft bullet"_hs>;
using EnemyBullet = entt::tag<"enemy aircraft bullet"_hs>;
using Missile = entt::tag<"aircraft Missile"_hs>;
using PlayerMissile = entt::tag<"Player aircraft Missile"_hs>;

}  // namespace tag
}  // namespace shootemup
