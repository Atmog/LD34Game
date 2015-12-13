#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>


class Entity : public sf::Transformable, public sf::Drawable
{
    public:
        Entity();
        ~Entity();

        void setLife(float life);
        float getLife() const;
        void damage(float damage);
        void heal(float heal);

        virtual void update(sf::Time dt);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        sf::Sprite mSprite;
        float mLife;
};

#endif // ENTITY_HPP
