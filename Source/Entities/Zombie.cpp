#include "Zombie.hpp"
#include "Manager.hpp"

Zombie::Zombie(Manager* manager, sf::Vector2f const& position, std::size_t type)
: mManager(manager)
{
    if (mManager != nullptr)
    {
        mManager->zombie(+1);
    }

    mSprite.setTexture(ah::Application::getResources().getTexture("zombies"));
    mSprite.setTextureRect(sf::IntRect(type * 32,0,32,48));
    mSprite.setOrigin(16.f,38.f);

    if (type == 1) // Speedster
    {
        mSprite.setColor(sf::Color(190,230,25));
        mSprite.setScale(1.1,1.1);
    }
    if (type == 2) // Mini-boss
    {
        mSprite.setColor(sf::Color(200,115,25));
        mSprite.setScale(1.3,1.3);
    }
    if (type == 3) // BOSS
    {
        mSprite.setColor(sf::Color(230,25,25));
        mSprite.setScale(1.6,1.6);
    }

    setPosition(position);

    mType = type;

    mLife = getLife(mType);

    // This is to prevent from lagging the game -> The player have to loose :D
    if (mManager != nullptr)
    {
        if (mManager->getDuration() > sf::seconds(800))
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
        else if (mManager->getDuration() > sf::seconds(1200))
        {
            mLife *= mLife * mLife; // I hope no-one will survive this ?
        }
    }
}

Zombie::~Zombie()
{
    if (mManager != nullptr)
    {
        mManager->zombie(-1);
    }
}

std::size_t Zombie::id() const
{
    return 2;
}

void Zombie::update(sf::Time dt)
{
    mLastHit += dt;

    if (mManager == nullptr)
    {
        return;
    }

    Entity* e = mManager->getNearestEntity(getPosition());
    if (e != nullptr)
    {
        sf::Vector2f v = e->getPosition() - getPosition();

        std::size_t sheetY = 2;
        float angle = thor::toDegree(-std::atan2(v.y,v.x));
        while(angle > 360)
            angle -= 360;
        while(angle <= 0)
            angle += 360;
        if (angle > 0 && angle <= 90)
            sheetY = 0;
        else if (angle > 90 && angle <= 180)
            sheetY = 1;
        else if (angle > 180 && angle <= 270)
            sheetY = 2;
        else if (angle > 270 && angle <= 360)
            sheetY = 3;

        std::size_t sheetX = 0;
        if (mType != 1)
        {
            if (mWalking.getElapsedTime() > sf::seconds(1.f))
            {
                mWalking.restart();
            }
            if (mWalking.getElapsedTime() <= sf::seconds(0.66f) && mWalking.getElapsedTime() > sf::seconds(0.33f))
            {
                sheetX = 1;
            }
            if (mWalking.getElapsedTime() > sf::seconds(0.66f))
            {
                sheetX = 2;
            }
        }
        if (mType == 1)
        {
            if (mWalking.getElapsedTime() > sf::seconds(0.5f))
            {
                mWalking.restart();
            }
            if (mWalking.getElapsedTime() <= sf::seconds(0.66f * 0.5) && mWalking.getElapsedTime() > sf::seconds(0.33f * 0.5))
            {
                sheetX = 1;
            }
            if (mWalking.getElapsedTime() > sf::seconds(0.66f * 0.5))
            {
                sheetX = 2;
            }
        }

        mSprite.setTextureRect(sf::IntRect(sheetX * 32, sheetY * 48,32,48));

        const float dcac = 30.f;
        float d = thor::length(v);
        if (d > dcac)
        {
            sf::Vector2f u = thor::unitVector(v);
            move(u * dt.asSeconds() * getSpeed(mType));
            d = thor::length(e->getPosition() - getPosition());
        }

        if (d <= dcac)
        {
            mWalking.restart();
            if (mLastHit > getRate(mType))
            {
                e->damage(getDamage(mType));
                mLastHit = sf::Time::Zero;
            }
        }
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
