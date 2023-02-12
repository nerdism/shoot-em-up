
#include "Game/DataTables.hpp"

#include <vector>

#include "Entities/Aircraft.hpp"
#include "Entities/Projectile.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Utility.hpp"

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;
using shootemup::Aircraft;
using shootemup::AircraftData;
using shootemup::Direction;
using shootemup::enum_to_int;
using shootemup::Projectile;
using shootemup::ProjectileData;
using shootemup::TextureId;

std::vector<AircraftData> shootemup::initialize_aircraft_data()
{
    std::vector<AircraftData> data(static_cast<int>(Aircraft::Type::TypeCount));

    auto eagle_index = static_cast<uint32_t>(Aircraft::Type::Eagle);
    auto raptor_index = static_cast<uint32_t>(Aircraft::Type::Raptor);
    auto avenger_index = static_cast<uint32_t>(Aircraft::Type::Avenger);

    data[eagle_index].hitpoints = 120;
    data[eagle_index].fireInterval = sf::seconds(1);
    data[eagle_index].texture = TextureId::Airplane_Eagle;

    data[raptor_index].hitpoints = 20;
    data[raptor_index].speed = 80.f;
    data[raptor_index].texture = TextureId::Airplane_Raptor;
    data[raptor_index].directions.emplace_back(+45.f, 80.f);
    data[raptor_index].directions.emplace_back(-45.f, 160.f);
    data[raptor_index].directions.emplace_back(+45.f, 80.f);
    data[raptor_index].fireInterval = sf::Time::Zero;

    data[avenger_index].hitpoints = 40;
    data[avenger_index].speed = 50.f;
    data[avenger_index].texture = TextureId::Airplane_Avenger;
    data[avenger_index].directions.emplace_back(+45.f, 50.f);
    data[avenger_index].directions.emplace_back(0.f, 50.f);
    data[avenger_index].directions.emplace_back(-45.f, 100.f);
    data[avenger_index].directions.emplace_back(0.f, 50.f);
    data[avenger_index].directions.emplace_back(+45.f, 50.f);
    data[avenger_index].fireInterval = sf::seconds(2);

    return data;
}

std::vector<ProjectileData> initialize_projectile_data()
{
    std::vector<ProjectileData> data(
        enum_to_int<uint32_t>(Projectile::Type::TypeCount));

    auto allied_index = enum_to_int<uint32_t>(Projectile::Type::AlliedBullet);
    auto enemy_index = enum_to_int<uint32_t>(Projectile::Type::EnemyBullet);
    auto missile_index = enum_to_int<uint32_t>(Projectile::Type::Missile);

    data[allied_index].damage = 10;
    data[allied_index].speed = 300.f;
    data[allied_index].texture = TextureId::Bullet;

    data[enemy_index].damage = 10;
    data[enemy_index].speed = 300.f;
    data[enemy_index].texture = TextureId::Bullet;

    data[missile_index].damage = 200;
    data[missile_index].speed = 150.f;
    data[missile_index].texture = TextureId::Missile;

    return data;
}
/*

std::vector<PickupData> initialize_pickup_data()
{
    std::vector<PickupData> data(Pickup::TypeCount);

    data[Pickup::HealthRefill].texture = Textures::HealthRefill;
    data[Pickup::HealthRefill].action = [](Aircraft& a) { a.repair(25); };

    data[Pickup::MissileRefill].texture = Textures::MissileRefill;
    data[Pickup::MissileRefill].action =
        std::bind(&Aircraft::Type::collectMissiles, _1, 3);

    data[Pickup::FireSpread].texture = Textures::FireSpread;
    data[Pickup::FireSpread].action = std::bind(&Aircraft::Type::increaseSpread,
_1);

    data[Pickup::FireRate].texture = Textures::FireRate;
    data[Pickup::FireRate].action = std::bind(&Aircraft::Type::increaseFireRate,
_1);

    return data;
}
*/
