#ifndef BULLET_HPP
#define BULLET_HPP

#include "Entity.hpp"

class Manager;

class Bullet : public Entity
{
    public:
        Bullet(Manager* manager, sf::Vector2f const& begin, sf::Vector2f const& end);
        ~Bullet();

        std::size_t id() const;

        void update(sf::Time dt);

    private:
        Manager* mManager;
        sf::Vector2f mEnd;
};

#endif // BULLET_HPP
