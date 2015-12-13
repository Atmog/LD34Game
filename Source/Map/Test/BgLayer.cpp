#include "BgLayer.hpp"

BgLayer::BgLayer()
{
    mSprite.setTexture(ah::Application::getResources().getTexture("tileset"));
    mSprite.setTextureRect(sf::IntRect(0,0,32,32));
    mSprite.setScale(200,200);
    mSprite.setPosition(-1000,-1000);
}

sf::Vector2f BgLayer::getSizePx() const
{
    return static_cast<sf::Vector2f>(ah::Application::getWindow().getSize());
}

void BgLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}
