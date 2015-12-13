#include "Plant.hpp"

Plant::Plant()
{
    mSprite.setTexture(ah::Application::getResources().getTexture("tileset"));
    mSeedId = 0;
    mSeedTime = sf::Time::Zero;
    mSprite.setTextureRect(sf::IntRect(96,0,32,32));
    mSprite.setOrigin(16.f,16.f);
    mBlocked = false;
}

Plant::~Plant()
{
}

std::size_t Plant::id() const
{
    return 1;
}

bool Plant::hasSeed() const
{
    return mSeedId != 0;
}

std::size_t Plant::getSeedId() const
{
    return mSeedId;
}

void Plant::setSeedId(std::size_t seedId)
{
    if (!hasSeed() && !isBlocked())
    {
        mSeedId = seedId;
        mSeedTime = sf::Time::Zero;
        if (mSeedId == 0)
        {
            mSprite.setTextureRect(sf::IntRect(96,0,32,32));
        }
        else
        {
            mSprite.setTextureRect(sf::IntRect(0,mSeedId * 32,32,32));
        }
    }
}

bool Plant::isSeedDone() const
{
    return mSeedTime >= getDuration(mSeedId);
}

sf::Time Plant::getSeedRemainingTime() const
{
    return getDuration(mSeedId) - mSeedTime;
}

sf::Time Plant::getActualTime() const
{
    return mSeedTime;
}

bool Plant::canCollect() const
{
    return (hasSeed() && isSeedDone() && !isBlocked());
}

void Plant::collectSeed()
{
    if (canCollect())
    {
        Game::increaseMoney(getMoney(mSeedId));

        mSeedId = 0;
        mSprite.setTextureRect(sf::IntRect(96,0,32,32));
        mSeedTime = sf::Time::Zero;
    }
}

bool Plant::isBlocked() const
{
    return mBlocked;
}

void Plant::setBlocked(bool blocked)
{
    mBlocked = blocked;
    if (mBlocked)
    {
        mSprite.setTextureRect(sf::IntRect(128,0,32,32));
        mSeedId = 0;
        mSeedTime = sf::Time::Zero;
    }
    else
    {
        mSprite.setTextureRect(sf::IntRect(96,0,32,32));
        mSeedId = 0;
        mSeedTime = sf::Time::Zero;
    }
}

bool Plant::collide(sf::Vector2f const& position)
{
    sf::FloatRect rect = mSprite.getGlobalBounds();
    rect.left += getPosition().x;
    rect.top += getPosition().y;
    return rect.contains(position);
}

void Plant::update(sf::Time dt)
{
    if (hasSeed() && !isBlocked())
    {
        mSeedTime += dt;
        sf::Time duration = getDuration(mSeedId);
        float ratio = mSeedTime.asSeconds() / duration.asSeconds();

        if (isSeedDone())
        {
            mSprite.setTextureRect(sf::IntRect(128,mSeedId * 32,32,32));
        }
        else if (ratio < 0.25f)
        {
            mSprite.setTextureRect(sf::IntRect(0,mSeedId * 32,32,32));
        }
        else if (ratio < 0.5f)
        {
            mSprite.setTextureRect(sf::IntRect(32,mSeedId * 32,32,32));
        }
        else if (ratio < 0.75f)
        {
            mSprite.setTextureRect(sf::IntRect(64,mSeedId * 32,32,32));
        }
        else
        {
            mSprite.setTextureRect(sf::IntRect(96,mSeedId * 32,32,32));
        }
    }
}

sf::Time Plant::getDuration(std::size_t seedId)
{
    sf::Time duration;
    switch (seedId)
    {
        case 1: duration = sf::seconds(5.f); break;
        case 2: duration = sf::seconds(10.f); break;
        case 3: duration = sf::seconds(20.f); break;
    }
    return duration;
}

float Plant::getCost(std::size_t seedId)
{
    float cost;
    switch (seedId)
    {
        case 1: cost = 25.f; break;
        case 2: cost = 50.f; break;
        case 3: cost = 100.f; break;
    }
    return cost;
}

float Plant::getMoney(std::size_t seedId)
{
    float money;
    switch (seedId)
    {
        case 1: money = 40.f; break;
        case 2: money = 80.f; break;
        case 3: money = 180.f; break;
    }
    return money;
}

