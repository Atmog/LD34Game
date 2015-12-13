#include "Entity.hpp"

Entity::Entity()
{
    mLife = 50.f;
}

Entity::~Entity()
{
}

void Entity::setLife(float life)
{
    mLife = life;
}

float Entity::getLife() const
{
    return mLife;
}

void Entity::damage(float damage)
{
    mLife -= damage;
}

void Entity::heal(float heal)
{
    mLife += heal;
}

void Entity::update(sf::Time dt)
{
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite,states);
}
