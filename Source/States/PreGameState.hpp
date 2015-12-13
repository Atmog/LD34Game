#ifndef PREGAMESTATE_HPP
#define PREGAMESTATE_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../Application/Application.hpp"

#include "State.hpp"

class PreGameState : public ah::State
{
    public:
        PreGameState(ah::StateManager& manager);
        virtual ~PreGameState();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render(sf::RenderTarget& target, sf::RenderStates states);

    private:
        sf::Clock mClock;

        sf::Text mMainText;
        sf::RectangleShape mMainShape;

        sf::Text mMoneyText;
        sf::RectangleShape mMoneyShape;

        sf::Text mWaveText;
        sf::RectangleShape mWaveShape;

        sf::Text mTurretText;
        sf::RectangleShape mTurretShape;

        sf::Text mSeedText;
        sf::RectangleShape mSeedShape;

        sf::Text mToolText;
        sf::RectangleShape mToolShape;

        sf::Text mSkipText;
        sf::RectangleShape mSkipShape;
};

#endif // PREGAMESTATE_HPP
