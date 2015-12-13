#include "Bullet.hpp"
#include "Manager.hpp"

Bullet::Bullet(Manager* manager, sf::Vector2f const& begin, sf::Vector2f const& end)
: mManager(manager)
{
    if (mManager != nullptr)
    {
        mManager->bullet(+1);
    }

    mSprite.setTexture(ah::Application::getResources().getTexture("turrets"));
    mSprite.setTextureRect(sf::IntRect(143,19,5,2));
    mSprite.setOrigin(2.5f,1);
    mSprite.setRotation(thor::polarAngle(end-begin));
    setPosition(begin);
    mEnd = end;
}

Bullet::~Bullet()
{
    if (mManager != nullptr)
    {
        mManager->bullet(-1);
    }
}

std::size_t Bullet::id() const
{
    return 0;
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
