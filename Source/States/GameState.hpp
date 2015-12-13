#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../Application/Application.hpp"
#include "../Application/State.hpp"
#include "States.hpp"
#include "../Game.hpp"

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../Entities/Manager.hpp"

class GameState : public ah::State
{
    public:
        GameState(ah::StateManager& manager);
        virtual ~GameState();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render(sf::RenderTarget& target, sf::RenderStates states);

    protected:
        sf::View mView;

        sf::RectangleShape mBg;

        Manager mManager;

        sf::Sprite mHUDMoneySprite;
        sf::Text mHUDMoneyText;

        sf::Sprite mHUDWaveSprite;
        sf::Text mHUDWaveText;

        sf::Sprite mHUDActionSprite;
        sf::Sprite mHUDActionIcon;

        sf::Sprite mHUDUnlockSprite;
        sf::Sprite mHUDUnlockIcon;
        sf::Sprite mHUDPlant1Sprite;
        sf::Sprite mHUDPlant1Icon;
        sf::Sprite mHUDPlant2Sprite;
        sf::Sprite mHUDPlant2Icon;
        sf::Sprite mHUDPlant3Sprite;
        sf::Sprite mHUDPlant3Icon;
        sf::Sprite mHUDCollectSprite;
        sf::Sprite mHUDCollectIcon;

        sf::Sprite mHUDTurret1Sprite;
        sf::Sprite mHUDTurret1Icon;
        sf::Sprite mHUDTurret2Sprite;
        sf::Sprite mHUDTurret2Icon;
        sf::Sprite mHUDTurret3Sprite;
        sf::Sprite mHUDTurret3Icon;
        sf::Sprite mHUDTurret4Sprite;
        sf::Sprite mHUDTurret4Icon;

        std::size_t mAction;

        sf::Time mMoneyTime;
};

#endif // GAMESTATE_HPP
