#ifndef PLANT_HPP
#define PLANT_HPP

#include "Entity.hpp"
#include "../Application/Application.hpp"
#include "../Game.hpp"


enum SeedId
{
    PlantNone = 0,
    Plant1 = 1,
    Plant2 = 2,
    Plant3 = 3,
};

class Plant : public Entity
{
    public:
        Plant();
        ~Plant();

        std::size_t id() const;

        typedef std::shared_ptr<Plant> Ptr;

        bool hasSeed() const;
        std::size_t getSeedId() const;
        void setSeedId(std::size_t seedId);

        bool isSeedDone() const;
        sf::Time getSeedRemainingTime() const;
        sf::Time getActualTime() const;

        bool canCollect() const;
        void collectSeed();

        bool isBlocked() const;
        void setBlocked(bool blocked);

        bool collide(sf::Vector2f const& position);

        void update(sf::Time dt);

        static sf::Time getDuration(std::size_t seedId);
        static float getCost(std::size_t seedId);
        static float getMoney(std::size_t seedId);

    protected:
        std::size_t mSeedId;
        sf::Time mSeedTime;
        bool mBlocked;
};

#endif // PLANT_HPP
