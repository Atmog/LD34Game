#ifndef BULLET_HPP
#define BULLET_HPP

#include "Entity.hpp"

class Bullet : public Entity
{
    public:
        Bullet();
        Bullet(sf::Vector2f const& begin, sf::Vector2f const& end);
        ~Bullet();

        void update(sf::Time dt);

    private:
        sf::Vector2f mEnd;
};

#endif // BULLET_HPP
