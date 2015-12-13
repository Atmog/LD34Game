#ifndef ENDGAMESTATE_HPP
#define ENDGAMESTATE_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../Application/Application.hpp"

#include "../Application/State.hpp"
#include "States.hpp"

class EndGameState : public ah::State
{
    public:
        EndGameState(ah::StateManager& manager);
        virtual ~EndGameState();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render(sf::RenderTarget& target, sf::RenderStates states);

    private:
        sf::Text mText;
        sf::RectangleShape mShape;
};

#endif // ENDGAMESTATE_HPP
