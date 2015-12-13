#ifndef TURRET_HPP
#define TURRET_HPP

#include "Entity.hpp"

#include <Thor/Vectors/VectorAlgebra2D.hpp>

class Manager;

enum TurretType
{
    Turret1 = 0,
    Turret2 = 1,
    Turret3 = 2,
    Turret4 = 3,
};

class Turret : public Entity
{
    public:
        Turret(Manager* manager, sf::Vector2f const& position, std::size_t type = Turret1);
        ~Turret();

        std::size_t id() const;

        typedef std::shared_ptr<Turret> Ptr;

        void update(sf::Time dt);

        static float getDamage(std::size_t type);
        static sf::Time getRate(std::size_t type);
        static float getLife(std::size_t type);
        static float getCost(std::size_t type);

    private:
        Manager* mManager;
        std::size_t mType;
        sf::Time mLastFire;
};

#endif // TURRET_HPP
