#include "Manager.hpp"

Manager::Manager()
{
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
    for (std::size_t i = 0; i < mPlants.size(); i++)
    {
        if (mPlants[i].collide(position) && !mPlants[i].hasSeed())
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
        for (std::size_t i = 0; i < mPlants.size(); i++)
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
    for (std::size_t i = 0; i < mPlants.size(); i++)
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
    for (std::size_t i = 0; i < mPlants.size(); i++)
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
    for (std::size_t i = 0; i < mPlants.size(); i++)
    {
        if (mPlants[i].collide(position) && mPlants[i].isBlocked() && Game::getMoney() > mUnlockPrice)
        {
            mPlants[i].setBlocked(false);
            Game::spendMoney(mUnlockPrice);
            ah::Application::getAudio().playSound("Unlock");
            mUnlockPrice *= 1.2f;
        }
    }
}

float Manager::getUnlockPrice() const
{
    return mUnlockPrice;
}

Zombie* Manager::getNearestZombie(sf::Vector2f const& position)
{
    Zombie* z = nullptr;
    float d = 99999.f;
    for (std::size_t i = 0; i < mZombies.size(); i++)
    {
        float d2 = thor::length(mZombies[i].getPosition() - position);
        if (d2 < d)
        {
            z = &mZombies[i];
            d = d2;
        }
    }
    return z;
}

std::size_t Manager::getRemainingTurrets() const
{
    return mTurrets.size();
}

void Manager::placeTurret(sf::Vector2f const& position, std::size_t turretId)
{
    if (Game::getMoney() >= Turret::getCost(turretId) && mTurrets.size() < 500)
    {
        Turret t(this,position,turretId);
        mTurrets.push_back(t);
        Game::spendMoney(Turret::getCost(turretId));
        ah::Application::getAudio().playSound("Turret");
    }
}

Plant* Manager::getNearestPlant(sf::Vector2f const& position)
{
    Plant* p = nullptr;
    float d = 99999.f;
    for (std::size_t i = 0; i < mPlants.size(); i++)
    {
        float d2 = thor::length(mPlants[i].getPosition() - position);
        if (d2 < d)
        {
            p = &mPlants[i];
            d = d2;
        }
    }
    return p;
}

Turret* Manager::getNearestTurret(sf::Vector2f const& position)
{
    Turret* t = nullptr;
    float d = 99999.f;
    for (std::size_t i = 0; i < mTurrets.size(); i++)
    {
        float d2 = thor::length(mTurrets[i].getPosition() - position);
        if (d2 < d)
        {
            t = &mTurrets[i];
            d = d2;
        }
    }
    return t;
}

std::size_t Manager::getRemainingZombies() const
{
    return mZombies.size();
}

void Manager::spawnZombie()
{
    float a = thor::random(0.f,360.f);
    sf::Vector2f pos = sf::Vector2f(std::cos(thor::toRadian(a)) * 800.f, std::sin(thor::toRadian(a)) * 800.f);
    std::size_t zombieId;
    int r = thor::random(0,100);
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

    if (r != 100) // If r = 100, don't spawn zombie, why being so evil ?
    {
        Zombie z(this,pos,zombieId);
        mZombies.push_back(z);
    }
}

void Manager::spawnBullet(sf::Vector2f const& b, sf::Vector2f const& e)
{
    if (mBullets.size() < 50)
    {
        Bullet bullet(b,e);
        mBullets.push_back(bullet);
        if (thor::random(0,2) == 0)
        {
            ah::Application::getAudio().playSound("Shoot");
        }
    }
}

void Manager::update(sf::Time dt)
{
    for (std::size_t i = 0; i < mPlants.size(); i++)
    {
        mPlants[i].update(dt);
    }
    for (std::size_t i = 0; i < mTurrets.size(); i++)
    {
        mTurrets[i].update(dt);
    }
    for (std::size_t i = 0; i < mZombies.size(); i++)
    {
        mZombies[i].update(dt);
    }
    for (std::size_t i = 0; i < mBullets.size(); i++)
    {
        mBullets[i].update(dt);
    }

    { // Spawn zombies
        mDuration += dt;
        mSpawner += dt;
        if (mSpawner.asSeconds() > getSpawnTime() && mDuration > sf::seconds(15.f))
        {
            mSpawner = sf::Time::Zero;
            for (std::size_t i = 0; i < getSpawnCount(); i++)
            {
                spawnZombie();
            }
        }
    }

    mPlants.erase(std::remove_if(mPlants.begin(),mPlants.end(),[](Plant p){return (p.Entity::getLife() <= 0.f);}),mPlants.end());
    mTurrets.erase(std::remove_if(mTurrets.begin(),mTurrets.end(),[](Turret t){return (t.Entity::getLife() <= 0.f);}),mTurrets.end());
    mZombies.erase(std::remove_if(mZombies.begin(),mZombies.end(),[](Zombie z){return (z.Entity::getLife() <= 0.f);}),mZombies.end());
    mBullets.erase(std::remove_if(mBullets.begin(),mBullets.end(),[](Bullet b){return (b.Entity::getLife() <= 0.f);}),mBullets.end());
}

void Manager::render(sf::RenderTarget& target, sf::RenderStates states)
{
    for (std::size_t i = 0; i < mPlants.size(); i++)
    {
        target.draw(mPlants[i],states);
    }
    for (std::size_t i = 0; i < mTurrets.size(); i++)
    {
        target.draw(mTurrets[i],states);
    }
    for (std::size_t i = 0; i < mZombies.size(); i++)
    {
        target.draw(mZombies[i],states);
    }
    for (std::size_t i = 0; i < mBullets.size(); i++)
    {
        target.draw(mBullets[i],states);
    }
    // TODO : Better rendering
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
    return n;
}
