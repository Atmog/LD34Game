#include "PreGameState.hpp"
#include "../Game.hpp"

PreGameState::PreGameState(ah::StateManager& manager)
: ah::State(manager,lp::type<PreGameState>())
{
    sf::Vector2f wSize = static_cast<sf::Vector2f>(ah::Application::getWindow().getSize());

    mMainText.setFont(ah::Application::getResources().getFont("cool"));
    mMoneyText.setFont(ah::Application::getResources().getFont("cool"));
    mWaveText.setFont(ah::Application::getResources().getFont("cool"));
    mTurretText.setFont(ah::Application::getResources().getFont("cool"));
    mSeedText.setFont(ah::Application::getResources().getFont("cool"));
    mToolText.setFont(ah::Application::getResources().getFont("cool"));
    mSkipText.setFont(ah::Application::getResources().getFont("cool"));

    mMainText.setColor(sf::Color::White);
    mMoneyText.setColor(sf::Color::White);
    mWaveText.setColor(sf::Color::White);
    mTurretText.setColor(sf::Color::White);
    mSeedText.setColor(sf::Color::White);
    mToolText.setColor(sf::Color::White);
    mSkipText.setColor(sf::Color::White);

    mMainText.setCharacterSize(25);
    mMoneyText.setCharacterSize(25);
    mWaveText.setCharacterSize(25);
    mTurretText.setCharacterSize(25);
    mSeedText.setCharacterSize(25);
    mToolText.setCharacterSize(25);
    mSkipText.setCharacterSize(25);

    mMainText.setString(Game::getString("Desc1") + "\n" + Game::getString("Desc2") + "\n" + Game::getString("Desc3"));
    mMoneyText.setString(Game::getString("Money"));
    mWaveText.setString(Game::getString("Wave"));
    mTurretText.setString(Game::getString("Turrets"));
    mSeedText.setString(Game::getString("Seeds"));
    mToolText.setString(Game::getString("Tools"));
    mSkipText.setString(Game::getString("Skip"));

    mMainText.setPosition(30,30);
    mMoneyText.setPosition(135-mMoneyText.getGlobalBounds().width/2,wSize.y-60-22-mMoneyText.getGlobalBounds().height);
    mWaveText.setPosition(wSize.x-135-mWaveText.getGlobalBounds().width/2,wSize.y-60-22-mWaveText.getGlobalBounds().height);
    mTurretText.setPosition(wSize.x - 46 - 16 - mTurretText.getGlobalBounds().width,300.f + 2 * 46);
    mSeedText.setPosition(wSize.x - 46 - 16 - mSeedText.getGlobalBounds().width,110.f + 3 * 46.f - 23);
    mToolText.setPosition(wSize.x - 46 -16 - mToolText.getGlobalBounds().width,100.f + 7);
    mSkipText.setPosition(30,300);

    mMainShape.setSize(sf::Vector2f(mMainText.getGlobalBounds().width + 10, mMainText.getGlobalBounds().height + 20));
    mMoneyShape.setSize(sf::Vector2f(mMoneyText.getGlobalBounds().width + 10, mMoneyText.getGlobalBounds().height + 20));
    mWaveShape.setSize(sf::Vector2f(mWaveText.getGlobalBounds().width + 10, mWaveText.getGlobalBounds().height + 20));
    mTurretShape.setSize(sf::Vector2f(mTurretText.getGlobalBounds().width + 10, mTurretText.getGlobalBounds().height + 20));
    mSeedShape.setSize(sf::Vector2f(mSeedText.getGlobalBounds().width + 10, mSeedText.getGlobalBounds().height + 20));
    mToolShape.setSize(sf::Vector2f(mToolText.getGlobalBounds().width + 10, mToolText.getGlobalBounds().height + 20));
    mSkipShape.setSize(sf::Vector2f(mSkipText.getGlobalBounds().width + 10, mSkipText.getGlobalBounds().height + 20));

    mMainShape.setFillColor(sf::Color(195,195,195));
    mMoneyShape.setFillColor(sf::Color(195,195,195));
    mWaveShape.setFillColor(sf::Color(195,195,195));
    mTurretShape.setFillColor(sf::Color(195,195,195));
    mSeedShape.setFillColor(sf::Color(195,195,195));
    mToolShape.setFillColor(sf::Color(195,195,195));
    mSkipShape.setFillColor(sf::Color(195,195,195));

    mMainShape.setPosition(mMainText.getPosition() - sf::Vector2f(5.f,5.f));
    mMoneyShape.setPosition(mMoneyText.getPosition() - sf::Vector2f(5.f,5.f));
    mWaveShape.setPosition(mWaveText.getPosition() - sf::Vector2f(5.f,5.f));
    mTurretShape.setPosition(mTurretText.getPosition() - sf::Vector2f(5.f,5.f));
    mSeedShape.setPosition(mSeedText.getPosition() - sf::Vector2f(5.f,5.f));
    mToolShape.setPosition(mToolText.getPosition() - sf::Vector2f(5.f,5.f));
    mSkipShape.setPosition(mSkipText.getPosition() - sf::Vector2f(5.f,5.f));

    mMainShape.setOutlineColor(sf::Color::Black);
    mMoneyShape.setOutlineColor(sf::Color::Black);
    mWaveShape.setOutlineColor(sf::Color::Black);
    mTurretShape.setOutlineColor(sf::Color::Black);
    mSeedShape.setOutlineColor(sf::Color::Black);
    mToolShape.setOutlineColor(sf::Color::Black);
    mSkipShape.setOutlineColor(sf::Color::Black);

    mMainShape.setOutlineThickness(1.f);
    mMoneyShape.setOutlineThickness(1.f);
    mWaveShape.setOutlineThickness(1.f);
    mTurretShape.setOutlineThickness(1.f);
    mSeedShape.setOutlineThickness(1.f);
    mToolShape.setOutlineThickness(1.f);
    mSkipShape.setOutlineThickness(1.f);
}

PreGameState::~PreGameState()
{
}

bool PreGameState::handleEvent(sf::Event const& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        requestPop();
    }
    return false;
}

bool PreGameState::update(sf::Time dt)
{
    return false;
}

void PreGameState::render(sf::RenderTarget& target, sf::RenderStates states)
{
    states.transform *= getTransform();
    target.draw(mMainShape,states);
    target.draw(mMoneyShape,states);
    target.draw(mWaveShape,states);
    target.draw(mTurretShape,states);
    target.draw(mSeedShape,states);
    target.draw(mToolShape,states);
    target.draw(mSkipShape,states);
    target.draw(mMainText,states);
    target.draw(mMoneyText,states);
    target.draw(mWaveText,states);
    target.draw(mTurretText,states);
    target.draw(mSeedText,states);
    target.draw(mToolText,states);
    target.draw(mSkipText,states);
}
