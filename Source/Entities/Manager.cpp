#include "Manager.hpp"

Manager::Manager()
{
    mTurrets = 0;
    mZombies = 0;
    mBullets = 0;
    mUnlockPrice = 20;
    for (std::size_t i = 0; i < 9; i++)
    {
        for (std::size_t j = 0; j < 9; j++)
        {
            Plant p;
            p.setPosition(i * 2 + i * 32 - 150.f, j * 2 + j * 32 - 150.f);
            if (i > 5 || i < 3 || j > 5 || j < 3)
            {
                p.setBlocked(true);
            }
            else
            {
                int a = thor::random(0,100);
                if (a < 80)
                {
                    p.setSeedId(0);
                }
                else if (a < 90)
                {
                    p.setSeedId(Plant1);
                }
                else if (a < 97)
                {
                    p.setSeedId(Plant2);
                }
                else if (a <= 100)
                {
                    p.setSeedId(Plant3);
                }
            }
            mPlants.push_back(p);
        }
    }

}

Manager::~Manager()
{
}

std::size_t Manager::getRemainingPlants() const
{
    return mPlants.size();
}

bool Manager::isPlantable(sf::Vector2f const& position)
{
    std::size_t s = mPlants.size();
    for (std::size_t i = 0; i < s; i++)
    {
        if (mPlants[i].collide(position) && !mPlants[i].hasSeed() && !mPlants[i].isBlocked())
        {
            return true;
        }
    }
    return false;
}

void Manager::setPlantSeed(sf::Vector2f const& position, std::size_t seedId)
{
    if (Game::getMoney() >= Plant::getCost(seedId))
    {
        std::size_t s = mPlants.size();
        for (std::size_t i = 0; i < s; i++)
        {
            if (mPlants[i].collide(position) && !mPlants[i].hasSeed() && !mPlants[i].isBlocked())
            {
                mPlants[i].setSeedId(seedId);
                Game::spendMoney(Plant::getCost(seedId));
                ah::Application::getAudio().playSound("Plant");
            }
        }
    }
}

void Manager::collectSeed(sf::Vector2f const& position)
{
    std::size_t s = mPlants.size();
    for (std::size_t i = 0; i < s; i++)
    {
        if (mPlants[i].collide(position) && mPlants[i].canCollect())
        {
            mPlants[i].collectSeed();
            ah::Application::getAudio().playSound("Collect");
        }
    }
}

bool Manager::canBeUnlocked(sf::Vector2f const& position)
{
    std::size_t s = mPlants.size();
    for (std::size_t i = 0; i < s; i++)
    {
        if (mPlants[i].collide(position) && mPlants[i].isBlocked() && Game::getMoney() > mUnlockPrice)
        {
            return true;
        }
    }
    return false;
}

void Manager::unlock(sf::Vector2f const& position)
{
    std::size_t s = mPlants.size();
    for (std::size_t i = 0; i < s; i++)
    {
        if (mPlants[i].collide(position) && mPlants[i].isBlocked() && Game::getMoney() > mUnlockPrice)
        {
            mPlants[i].setBlocked(false);
            Game::spendMoney(mUnlockPrice);
            ah::Application::getAudio().playSound("Unlock");
            mUnlockPrice *= 1.4f;
        }
    }
}

float Manager::getUnlockPrice() const
{
    return mUnlockPrice;
}

Entity* Manager::getNearestZombie(sf::Vector2f const& position)
{
    Entity* z = nullptr;
    float d = 99999.f;
    std::size_t s = mEntities.size();
    for (std::size_t i = 0; i < s; i++)
    {
        if (mEntities[i]->id() == 2)
        {
            float d2 = thor::length(mEntities[i]->getPosition() - position);
            if (d2 < d)
            {
                z = mEntities[i].get();
                d = d2;
            }
        }
    }
    return z;
}

std::size_t Manager::getRemainingTurrets() const
{
    return mTurrets;
}

void Manager::placeTurret(sf::Vector2f const& position, std::size_t turretId)
{
    if (Game::getMoney() >= Turret::getCost(turretId) && getRemainingTurrets() < 500)
    {
        mEntities.emplace_back(std::make_shared<Turret>(this,position,turretId));
        Game::spendMoney(Turret::getCost(turretId));
        ah::Application::getAudio().playSound("Turret");
    }
}

Entity* Manager::getNearestEntity(sf::Vector2f const& position)
{
    Entity* e = nullptr;
    float d = 99999.f;
    std::size_t s = mPlants.size();
    for (std::size_t i = 0; i < s; i++)
    {
        float d2 = thor::length(mPlants[i].getPosition() - position);
        if (d2 < d)
        {
            e = &mPlants[i];
            d = d2;
        }
    }
    s = mEntities.size();
    for (std::size_t i = 0; i < s; i++)
    {
        if (mEntities[i]->id() == 1)
        {
            float d2 = thor::length(mEntities[i]->getPosition() - position);
            if (d2 < d)
            {
                e = mEntities[i].get();
                d = d2;
            }
        }
    }
    return e;
}

std::size_t Manager::getRemainingZombies() const
{
    return mZombies;
}

void Manager::spawnZombie()
{
    float a = thor::random(0.f,360.f);
    sf::Vector2f pos = sf::Vector2f(std::cos(thor::toRadian(a)) * 800.f, std::sin(thor::toRadian(a)) * 800.f);
    std::size_t zombieId;
    int r = thor::random(0,100);
    if (mDuration < sf::seconds(300))
    {
        if (r < 70)
        {
            zombieId = 0;
        }
        else if (r < 89)
        {
            zombieId = 1;
        }
        else if (r < 99)
        {
            zombieId = 2;
        }
        else if (r == 99)
        {
            zombieId = 3;
        }
    }
    else
    {
        if (r < 50)
        {
            zombieId = 0;
        }
        else if (r < 80)
        {
            zombieId = 1;
        }
        else if (r < 98)
        {
            zombieId = 2;
        }
        else if (r <= 99)
        {
            zombieId = 3;
        }
    }

    if (r != 100) // If r = 100, don't spawn zombie, why being so evil ?
    {
        mEntities.emplace_back(std::make_shared<Zombie>(this,pos,zombieId));
    }
}

void Manager::spawnBullet(sf::Vector2f const& b, sf::Vector2f const& e)
{
    if (mBullets < 30)
    {
        mEntities.emplace_back(std::make_shared<Bullet>(this,b,e));
        if (thor::random(0,4) == 0)
        {
            ah::Application::getAudio().playSound("Shoot");
        }
    }
}

void Manager::update(sf::Time dt)
{
    std::size_t s = mPlants.size();
    for (std::size_t i = 0; i < s; i++)
    {
        mPlants[i].update(dt);
    }
    s = mEntities.size();
    for (std::size_t i = 0; i < s; i++)
    {
        mEntities[i]->update(dt);
    }

    // Spawn zombies
    mDuration += dt;
    mSpawner += dt;
    if (mSpawner.asSeconds() > getSpawnTime() && mDuration > sf::seconds(20.f))
    {
        mSpawner = sf::Time::Zero;
        std::size_t t = getSpawnCount();
        for (std::size_t i = 0; i < t; i++)
        {
            spawnZombie();
        }
    }

    // Remove dead entities
    mPlants.erase(std::remove_if(mPlants.begin(),mPlants.end(),[](Plant p){return (p.Entity::getLife() <= 0.f);}),mPlants.end());
    mEntities.erase(std::remove_if(mEntities.begin(),mEntities.end(),[](Entity::Ptr e){return (e->getLife() <= 0.f);}),mEntities.end());
}

void Manager::render(sf::RenderTarget& target, sf::RenderStates states)
{
    std::size_t s = mPlants.size();
    for (std::size_t i = 0; i < s; i++)
    {
        target.draw(mPlants[i],states);
    }

    std::sort(mEntities.begin(),mEntities.end(),[](Entity::Ptr a, Entity::Ptr b) -> bool
    {
        return (a->getPosition().y < b->getPosition().y);
    });

    s = mEntities.size();
    for (std::size_t i = 0; i < s; i++)
    {
        target.draw(*mEntities[i],states);
    }
}

sf::Time Manager::getDuration()
{
    return mDuration;
}

float Manager::getSpawnTime()
{
    return 1/(0.005f * mDuration.asSeconds() + 0.5f);
}

std::size_t Manager::getSpawnCount()
{
    std::size_t n = (std::size_t)(mDuration.asSeconds() / 100.f);
    if (n == 0)
    {
        n++;
    }
    if (mDuration > sf::seconds(500.f))
    {
        n++;
    }
    if (mDuration > sf::seconds(600.f))
    {
        n++;
    }
    if (mDuration > sf::seconds(700.f))
    {
        n++;
    }
    if (mDuration > sf::seconds(800.f))
    {
        n++;
    }
    if (mDuration > sf::seconds(9000.f))
    {
        n++;
    }
    if (mDuration > sf::seconds(9000.f))
    {
        n += 2;
    }
    return n;
}

std::size_t Manager::getRemainingBullets() const
{
    return mBullets;
}

void Manager::turret(int modify)
{
    mTurrets += modify;
}

void Manager::zombie(int modify)
{
    mZombies += modify;
}

void Manager::bullet(int modify)
{
    mBullets += modify;
}


