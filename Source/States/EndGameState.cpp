#include "EndGameState.hpp"

EndGameState::EndGameState(ah::StateManager& manager)
: ah::State(manager,lp::type<EndGameState>())
{
    sf::Vector2f wSize = static_cast<sf::Vector2f>(ah::Application::getWindow().getSize());

    mText.setFont(ah::Application::getResources().getFont("cool"));
    mText.setColor(sf::Color::White);
    mText.setCharacterSize(40);
    mText.setString(Game::getString("Score") + " : \n\n" + std::to_string((int)Game::getMoneyEarned()) + "\n\n" + Game::getString("AnyKey")+ "\n" + Game::getString("Menu"));
    mText.setOrigin(mText.getGlobalBounds().width/2,mText.getGlobalBounds().height/2);
    mText.setPosition(wSize * 0.5f);

    mShape.setSize(wSize * 0.75f);
    mShape.setOrigin(mShape.getSize().x/2,mShape.getSize().y/2);
    mShape.setPosition(wSize * 0.5f);
    mShape.setFillColor(sf::Color(195.f,195.f,195.f));
    mShape.setOutlineColor(sf::Color::Black);
    mShape.setOutlineThickness(1.f);
}

EndGameState::~EndGameState()
{
}

bool EndGameState::handleEvent(sf::Event const& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        requestClear();
        requestPush(lp::type<MenuState>());
    }
    return false;
}

bool EndGameState::update(sf::Time dt)
{
    return false;
}

void EndGameState::render(sf::RenderTarget& target, sf::RenderStates states)
{
    states.transform *= getTransform();
    target.draw(mShape,states);
    target.draw(mText,states);
}
