#include "Turret.hpp"
#include "Manager.hpp"

Turret::Turret()
{
}

Turret::Turret(Manager* manager, sf::Vector2f const& position, std::size_t type)
: mManager(manager)
{
    mSprite.setTexture(ah::Application::getResources().getTexture("turrets"));
    mSprite.setTextureRect(sf::IntRect(type * 32,0,32,32));
    mSprite.setOrigin(16.f,16.f);

    setPosition(position);

    mType = type;

    mLife = getLife(mType);
}

Turret::~Turret()
{
}

void Turret::update(sf::Time dt)
{
    mLastFire += dt;

    if (mManager == nullptr)
    {
        return;
    }

    Zombie* zombie = mManager->getNearestZombie(getPosition());
    if (zombie != nullptr)
    {
        if (thor::length(zombie->getPosition() - getPosition()) <= 350.f && mLastFire >= getRate(mType))
        {
            mLastFire = sf::Time::Zero;

            // TODO : Animation Canon

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
