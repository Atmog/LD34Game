#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <vector>

#include <Thor/Vectors/VectorAlgebra2D.hpp>
#include <Thor/Math.hpp>

#include "Plant.hpp"
#include "Zombie.hpp"
#include "Turret.hpp"
#include "Bullet.hpp"

class Manager
{
    public:
        Manager();
        ~Manager();

        std::size_t getRemainingPlants() const;
        bool isPlantable(sf::Vector2f const& position);
        void setPlantSeed(sf::Vector2f const& position, std::size_t seedId);
        void collectSeed(sf::Vector2f const& position);
        bool canBeUnlocked(sf::Vector2f const& position);
        void unlock(sf::Vector2f const& position);
        float getUnlockPrice() const;

        Zombie* getNearestZombie(sf::Vector2f const& position);
        std::size_t getRemainingTurrets() const;
        void placeTurret(sf::Vector2f const& position, std::size_t turretId);

        Plant* getNearestPlant(sf::Vector2f const& position);
        Turret* getNearestTurret(sf::Vector2f const& position);
        std::size_t getRemainingZombies() const;
        void spawnZombie();

        void spawnBullet(sf::Vector2f const& b, sf::Vector2f const& e);

        void update(sf::Time dt);
        void render(sf::RenderTarget& target, sf::RenderStates states);

        sf::Time getDuration();
        float getSpawnTime();
        std::size_t getSpawnCount();

    private:
        std::vector<Plant> mPlants;
        std::vector<Zombie> mZombies;
        std::vector<Turret> mTurrets;
        std::vector<Bullet> mBullets;

        float mUnlockPrice;

        sf::Time mSpawner;
        sf::Time mDuration;
};

#endif // MANAGER_HPP
