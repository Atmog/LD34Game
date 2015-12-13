#include "Zombie.hpp"
#include "Manager.hpp"

Zombie::Zombie()
{
}

Zombie::Zombie(Manager* manager, sf::Vector2f const& position, std::size_t type)
: mManager(manager)
{
    mSprite.setTexture(ah::Application::getResources().getTexture("zombies"));
    mSprite.setTextureRect(sf::IntRect(type * 32,0,32,32));
    mSprite.setOrigin(16.f,16.f);

    setPosition(position);

    mType = type;

    mLife = getLife(mType);

    // This is to prevent from lagging the game -> The player have to loose :D
    if (mManager != nullptr)
    {
        if (mManager->getDuration() > sf::seconds(500))
        {
            mLife += 20;
        }
        else if (mManager->getDuration() > sf::seconds(600))
        {
            mLife += 40;
        }
        else if (mManager->getDuration() > sf::seconds(700))
        {
            mLife += 60;
        }
        else if (mManager->getDuration() > sf::seconds(800))
        {
            mLife += 80;
        }
        else if (mManager->getDuration() > sf::seconds(900))
        {
            mLife += 100;
        }
        else if (mManager->getDuration() > sf::seconds(1000))
        {
            mLife *= 2;
        }
        else if (mManager->getDuration() > sf::seconds(1200))
        {
            mLife *= mLife; // I hope no-one will survive this ?
        }
    }
}

Zombie::~Zombie()
{
}

void Zombie::update(sf::Time dt)
{
    mLastHit += dt;

    if (mManager == nullptr)
    {
        return;
    }

    Plant* p = mManager->getNearestPlant(getPosition());
    Turret* t = mManager->getNearestTurret(getPosition());

    if (p != nullptr && t != nullptr)
    {
        // Find the nearest one
        float d1 = thor::length(p->getPosition() - getPosition());
        float d2 = thor::length(t->getPosition() - getPosition());
        if (d1 < d2)
        {
            if (updateToTarget(dt,p->getPosition()))
            {
                attack(p);
            }
        }
        else
        {
            if (updateToTarget(dt,t->getPosition()))
            {
                attack(t);
            }
        }
    }
    else if (p != nullptr && t == nullptr)
    {
        if (updateToTarget(dt,p->getPosition()))
        {
            attack(p);
        }
    }
    else if (p == nullptr && t != nullptr)
    {
        if (updateToTarget(dt,t->getPosition()))
        {
            attack(t);
        }
    }
}

bool Zombie::updateToTarget(sf::Time dt, sf::Vector2f const& position)
{
    const float dcac = 30.f;

    float d = thor::length(position - getPosition());
    if (d > dcac)
    {
        sf::Vector2f u = thor::unitVector(position - getPosition());
        move(u * dt.asSeconds() * getSpeed(mType));
        d = thor::length(position - getPosition());
    }
    return (d <= dcac);
}

void Zombie::attack(Entity* e)
{
    if (e != nullptr && mLastHit > getRate(mType))
    {
        e->damage(getDamage(mType));
        mLastHit = sf::Time::Zero;
    }
}

float Zombie::getSpeed(std::size_t type)
{
    float speed;
    switch (type)
    {
        case 0: speed = 50.f; break;
        case 1: speed = 80.f; break;
        case 2: speed = 55.f; break;
        case 3: speed = 40.f; break;
    }
    return speed;
}

float Zombie::getDamage(std::size_t type)
{
    float damage;
    switch (type)
    {
        case 0: damage = 10.f; break;
        case 1: damage = 6.f; break;
        case 2: damage = 20.f; break;
        case 3: damage = 50.f; break;
    }
    return damage;
}

sf::Time Zombie::getRate(std::size_t type)
{
    sf::Time rate;
    switch (type)
    {
        case 0: rate = sf::seconds(0.4f); break;
        case 1: rate = sf::seconds(0.2f); break;
        case 2: rate = sf::seconds(0.4f); break;
        case 3: rate = sf::seconds(0.4f); break;
    }
    return rate;
}

float Zombie::getLife(std::size_t type)
{
    float life;
    switch (type)
    {
        case 0: life = 200.f; break;
        case 1: life = 190.f; break;
        case 2: life = 225.f; break;
        case 3: life = 800.f; break;
    }
    return life;
}
