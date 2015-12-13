#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <fstream>
#include <SFML/System/Clock.hpp>
#include <SFML/Audio/Music.hpp>
#include <Thor/Input.hpp>
#include "Helper/ActionTarget.hpp"
#include "Helper/pugixml.hpp"

class Game
{
    public:
        static Game& instance();

        static std::string getTitle();

        static void startMenu();
        static void updateMusicVolume();

        static void startNewGame();

        static float getMoney();
        static void spendMoney(float value);
        static void increaseMoney(float value);

        static float getMoneyEarned();

        static sf::Time getDuration();

        static void setActionKey(std::string const& id, sf::Keyboard::Key key);
        static sf::Keyboard::Key getActionKey(std::string const& id);

        static lp::ActionMapPtr getActionMap();

        static std::string getString(std::string const& id);

    private:
        Game();
        ~Game();

		bool load();
		void save();

        static Game mInstance;

        float mMoney;
        float mMoneyEarned;
        lp::ActionMapPtr mActionMap;
        std::map<std::string,std::pair<sf::Keyboard::Key,bool>> mKeys;

        std::map<std::string,std::string> mLang;

        sf::Clock mGameDuration;

        sf::Music mMusic;
};

#endif // GAME_HPP
