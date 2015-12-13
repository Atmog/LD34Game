#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "Entity.hpp"

#include <Thor/Vectors/VectorAlgebra2D.hpp>

class Manager;

enum ZombieType
{
    Zombie1 = 0, // 70% // Normal
    Zombie2 = 1, // 19  // Faster
    Zombie3 = 2, // 10  // Power
    Zombie4 = 3, // 1   // BOSS
};

class Zombie : public Entity
{
    public:
        Zombie();
        Zombie(Manager* manager, sf::Vector2f const& position, std::size_t type = Zombie1);
        ~Zombie();

        void update(sf::Time dt);

        bool updateToTarget(sf::Time dt, sf::Vector2f const& tPosition);
        void attack(Entity* e);

        static float getSpeed(std::size_t type);
        static float getDamage(std::size_t type);
        static sf::Time getRate(std::size_t type);
        static float getLife(std::size_t type);

    private:
        Manager* mManager;
        std::size_t mType;
        sf::Time mLastHit;
};

#endif // ZOMBIE_HPP
