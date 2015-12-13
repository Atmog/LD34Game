#include "Turret.hpp"
#include "Manager.hpp"

Turret::Turret(Manager* manager, sf::Vector2f const& position, std::size_t type)
: mManager(manager)
{
    if (mManager != nullptr)
    {
        mManager->turret(+1);
    }

    mSprite.setTexture(ah::Application::getResources().getTexture("turrets"));
    mSprite.setTextureRect(sf::IntRect(thor::random(0,3) * 64,type * 64,64,64));
    mSprite.setOrigin(32,32);
    mSprite.setScale(0.5,0.5);

    setPosition(position);

    mType = type;

    mLife = getLife(mType);
}

Turret::~Turret()
{
    if (mManager != nullptr)
    {
        mManager->turret(-1);
    }
}

std::size_t Turret::id() const
{
    return 1;
}

void Turret::update(sf::Time dt)
{
    mLastFire += dt;

    if (mManager == nullptr)
    {
        return;
    }

    Entity* zombie = mManager->getNearestZombie(getPosition());
    if (zombie != nullptr)
    {
        sf::Vector2f v = zombie->getPosition() - getPosition();

        float angle = thor::toDegree(-std::atan2(v.y,v.x));
        while(angle > 360)
            angle -= 360;
        while(angle <= 0)
            angle += 360;
        if (angle > 0 && angle <= 90)
            mSprite.setTextureRect(sf::IntRect(0,mType * 64,64,64));
        else if (angle > 90 && angle <= 180)
            mSprite.setTextureRect(sf::IntRect(64,mType * 64,64,64));
        else if (angle > 180 && angle <= 270)
            mSprite.setTextureRect(sf::IntRect(128,mType * 64,64,64));
        else if (angle > 270 && angle <= 360)
            mSprite.setTextureRect(sf::IntRect(192,mType * 64,64,64));

        sf::Time rate = getRate(mType);
        if (mManager->getDuration() > sf::seconds(1000.f))
        {
            rate += sf::seconds(0.2f);
        }
        if (mManager->getDuration() > sf::seconds(1100.f))
        {
            rate += sf::seconds(0.2f);
        }
        if (mManager->getDuration() > sf::seconds(1200.f))
        {
            rate += sf::seconds(0.2f);
        }

        if (thor::length(v) <= 350.f && mLastFire >= rate)
        {
            mLastFire = sf::Time::Zero;

            mManager->spawnBullet(getPosition(),zombie->getPosition());

            zombie->damage(getDamage(mType));
        }
    }
}

float Turret::getDamage(std::size_t type)
{
    float damage;
    switch (type)
    {
        case 0: damage = 10.f * 1.3; break;
        case 1: damage = 7.875f * 1.2; break;
        case 2: damage = 55.f * 1.1; break;
        case 3: damage = 96.f; break;
    }
    return damage;
}

sf::Time Turret::getRate(std::size_t type)
{
    sf::Time rate;
    switch (type)
    {
        case 0: rate = sf::seconds(0.5f); break;
        case 1: rate = sf::seconds(0.25f); break;
        case 2: rate = sf::seconds(1.f); break;
        case 3: rate = sf::seconds(0.5f); break;
    }
    return rate;
}

float Turret::getLife(std::size_t type)
{
    float life;
    switch (type)
    {
        case 0: life = 300.f; break;
        case 1: life = 350.f; break;
        case 2: life = 400.f; break;
        case 3: life = 450.f; break;
    }
    return life;
}

float Turret::getCost(std::size_t type)
{
    float cost;
    switch (type)
    {
        case 0: cost = 100.f; break;
        case 1: cost = 150.f; break;
        case 2: cost = 250.f; break;
        case 3: cost = 400.f; break;
    }
    return cost;
}
