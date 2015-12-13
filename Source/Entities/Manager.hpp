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

        Entity* getNearestZombie(sf::Vector2f const& position);
        std::size_t getRemainingTurrets() const;
        void placeTurret(sf::Vector2f const& position, std::size_t turretId);

        Entity* getNearestEntity(sf::Vector2f const& position);
        std::size_t getRemainingZombies() const;
        void spawnZombie();

        void spawnBullet(sf::Vector2f const& b, sf::Vector2f const& e);

        void update(sf::Time dt);
        void render(sf::RenderTarget& target, sf::RenderStates states);

        sf::Time getDuration();
        float getSpawnTime();
        std::size_t getSpawnCount();

        std::size_t getRemainingBullets() const;

        void turret(int modify);
        void zombie(int modify);
        void bullet(int modify);

    private:
        std::vector<Plant> mPlants;
        std::vector<Entity::Ptr> mEntities;

        std::size_t mTurrets;
        std::size_t mZombies;
        std::size_t mBullets;

        float mUnlockPrice;

        sf::Time mSpawner;
        sf::Time mDuration;
};

#endif // MANAGER_HPP
