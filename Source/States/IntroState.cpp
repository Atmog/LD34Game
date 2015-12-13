#include "IntroState.hpp"

IntroState::IntroState(ah::StateManager& manager)
: ah::State(manager,lp::type<IntroState>())
{
    sf::Vector2u wSize = ah::Application::getWindow().getSize();
    sf::Vector2f scale = sf::Vector2f(wSize.x/800.f,wSize.y/600.f);

    mAtmogText.setFont(ah::Application::getResources().getFont("atmog"));
    mAtmogText.setString(L"Atmög");
    mAtmogText.setCharacterSize(static_cast<unsigned int>(200 * scale.y));
    mAtmogText.setPosition(wSize.x * 0.5f - mAtmogText.getGlobalBounds().width * 0.5f,wSize.y * 0.5f - mAtmogText.getGlobalBounds().height * 0.5f);
    mAtmogText.setColor(sf::Color::White);

    mAtmogShadow.setFont(ah::Application::getResources().getFont("atmog"));
    mAtmogShadow.setString(mAtmogText.getString());
    mAtmogShadow.setCharacterSize(mAtmogText.getCharacterSize());
    mAtmogShadow.setPosition(mAtmogText.getPosition() + sf::Vector2f(4.f * scale.x, 4.f * scale.y));
    mAtmogShadow.setColor(sf::Color::Black);
}

IntroState::~IntroState()
{
    Game::startMenu();
}

bool IntroState::handleEvent(sf::Event const& event)
{
    return true;
}

bool IntroState::update(sf::Time dt)
{
    sf::Vector2u wSize = ah::Application::getWindow().getSize();
    sf::Vector2f scale = sf::Vector2f(wSize.x/800.f,wSize.y/600.f);

    if (mClock.getElapsedTime() < sf::seconds(1.f))
    {
        mBackground.setTexture(ah::Application::getResources().getTexture("ld34"));
        mBackground.setScale(wSize.x/900.f,scale.y);
        mBackground.setPosition(0,0);
    }
    else if (mClock.getElapsedTime() < sf::seconds(2.f))
    {
        mSfml.setTexture(ah::Application::getResources().getTexture("sfml"));
        mSfml.setPosition(wSize.x/2-mSfml.getGlobalBounds().width/2,wSize.y/2-mSfml.getGlobalBounds().height/2);
        mSfml.setScale(scale);
    }
    else if (mClock.getElapsedTime() < sf::seconds(3.f))
    {
        mBackground.setScale(1.f,1.f);
        mBackground.setTexture(ah::Application::getResources().getTexture("bg"));
        mBackground.setScale(scale);
        mBackground.setPosition(0,0);
    }
    else
    {
        requestClear();
        requestPush(lp::type<MenuState>());
    }
    return true;
}

void IntroState::render(sf::RenderTarget& target, sf::RenderStates states)
{
    states.transform *= getTransform();
    if (mClock.getElapsedTime() > sf::seconds(1.f) && mClock.getElapsedTime() <= sf::seconds(2.f))
    {
        sf::RectangleShape b;
        b.setSize(static_cast<sf::Vector2f>(ah::Application::getWindow().getSize()));
        b.setFillColor(sf::Color::White);
        target.draw(b,states);
        target.draw(mSfml,states);
    }
    else
    {
        target.draw(mBackground,states);
    }
    if (mClock.getElapsedTime() > sf::seconds(2.f) && mClock.getElapsedTime() <= sf::seconds(3.f))
    {
        target.draw(mAtmogShadow,states);
        target.draw(mAtmogText,states);
    }
}

void IntroState::onActivate()
{
    ah::Application::getWindow().hideMouseCursor();
}

void IntroState::onDeactivate()
{
    ah::Application::getWindow().useCustomMouseCursor(&ah::Application::getResources().getTexture("cursor"));
}
