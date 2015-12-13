#include "Bullet.hpp"
#include "Manager.hpp"

Bullet::Bullet()
{
}

Bullet::Bullet(sf::Vector2f const& begin, sf::Vector2f const& end)
{
    mSprite.setTexture(ah::Application::getResources().getTexture("turrets"));
    mSprite.setTextureRect(sf::IntRect(0,32,5,2));
    mSprite.setOrigin(2.5f,1);
    mSprite.setRotation(thor::polarAngle(end-begin));
    setPosition(begin);
    mEnd = end;
}

Bullet::~Bullet()
{
}

void Bullet::update(sf::Time dt)
{
    sf::Vector2f m = getPosition();
    float d = thor::length(m - mEnd);
    if (d > 10)
    {
        sf::Vector2f u = thor::unitVector(mEnd-m);
        move(u * dt.asSeconds() * 700.f);
    }
    else
    {
        mLife = -100.f;
    }
}
