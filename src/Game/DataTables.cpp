
#include "Game/DataTables.hpp"

#include <vector>

#include "Entities/Aircraft.hpp"
#include "ResourceManager/ResourceManager.hpp"

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;
using shootemup::Aircraft;
using shootemup::AircraftData;
using shootemup::Direction;
using shootemup::TextureId;

std::vector<AircraftData> initialize_aircraft_data()
{
    std::vector<AircraftData> data(static_cast<int>(Aircraft::Type::TypeCount));

    auto eagle_index = static_cast<uint32_t>(Aircraft::Type::Eagle);
    auto raptor_index = static_cast<uint32_t>(Aircraft::Type::Raptor);
    auto avenger_index = static_cast<uint32_t>(Aircraft::Type::Avenger);

    data[eagle_index].hitpoints = 100;
    data[eagle_index].speed = 200.f;
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
/*
std::vector<ProjectileData> initialize_projectile_data()
{
    std::vector<ProjectileData> data(Projectile::TypeCount);

    data[Projectile::AlliedBullet].damage = 10;
    data[Projectile::AlliedBullet].speed = 300.f;
    data[Projectile::AlliedBullet].texture = Textures::Bullet;

    data[Projectile::EnemyBullet].damage = 10;
    data[Projectile::EnemyBullet].speed = 300.f;
    data[Projectile::EnemyBullet].texture = Textures::Bullet;

    data[Projectile::Missile].damage = 200;
    data[Projectile::Missile].speed = 150.f;
    data[Projectile::Missile].texture = Textures::Missile;

    return data;
}

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
