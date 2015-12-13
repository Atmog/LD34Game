#include "Game.hpp"
#include "Application/Application.hpp"

Game Game::mInstance;

std::string Game::getTitle()
{
    return "Test";
}

void Game::startMenu()
{
    mInstance.mMusic.openFromFile("Assets/Musics/Menu.ogg");
    mInstance.mMusic.setLoop(true);
    mInstance.mMusic.setVolume(ah::Application::getAudio().getMusicVolume());
    mInstance.mMusic.play();
}

void Game::updateMusicVolume()
{
    mInstance.mMusic.setVolume(ah::Application::getAudio().getMusicVolume());
}

void Game::startNewGame()
{
    mInstance.mMoney = 1000;
    mInstance.mMoneyEarned = 0.f;
    mInstance.mGameDuration.restart();
    mInstance.mMusic.openFromFile("Assets/Musics/Game.ogg");
    mInstance.mMusic.setLoop(true);
    mInstance.mMusic.setVolume(ah::Application::getAudio().getMusicVolume());
    mInstance.mMusic.play();
}

float Game::getMoney()
{
    return mInstance.mMoney;
}

void Game::spendMoney(float value)
{
    mInstance.mMoney -= value;
}

void Game::increaseMoney(float value)
{
    mInstance.mMoney += value;
    mInstance.mMoneyEarned += value;
}

float Game::getMoneyEarned()
{
    return mInstance.mMoneyEarned;
}

sf::Time Game::getDuration()
{
    return mInstance.mGameDuration.getElapsedTime();
}

void Game::setActionKey(std::string const& id, sf::Keyboard::Key key)
{
    mInstance.mKeys[id].first = key;
    (*mInstance.mActionMap)[id] = thor::Action(mInstance.mKeys[id].first,(mInstance.mKeys[id].second) ? thor::Action::Hold : thor::Action::PressOnce);
}

sf::Keyboard::Key Game::getActionKey(std::string const& id)
{
    return mInstance.mKeys[id].first;
}

lp::ActionMapPtr Game::getActionMap()
{
    return mInstance.mActionMap;
}

std::string Game::getString(std::string const& id)
{
    if (mInstance.mLang.find(id) != mInstance.mLang.end())
    {
        return mInstance.mLang.at(id);
    }
    return id;
}

Game::Game()
{
    mActionMap = std::make_shared<thor::ActionMap<std::string>>();

    if (!load())
    {
        mKeys["1"].first = sf::Keyboard::Num1;
        mKeys["2"].first = sf::Keyboard::Num2;
        mKeys["3"].first = sf::Keyboard::Num3;
        mKeys["4"].first = sf::Keyboard::Num4;
        mKeys["5"].first = sf::Keyboard::Num5;
        mKeys["6"].first = sf::Keyboard::Num6;
        mKeys["7"].first = sf::Keyboard::Num7;
        mKeys["8"].first = sf::Keyboard::Num8;
        mKeys["9"].first = sf::Keyboard::Num9;
    }

    for (auto itr = mKeys.begin(); itr != mKeys.end(); itr++)
    {
        (*mActionMap)[itr->first] = thor::Action(itr->second.first,(itr->second.second) ? thor::Action::Hold : thor::Action::PressOnce);
    }

    std::ifstream file("Assets/Data/lang.dat");
    if (file)
    {
        std::string line;
        while (std::getline(file,line))
        {
            auto f = line.find("=");
            std::string id = line.substr(0,f);
            std::string str = line.substr(f+1);
            mInstance.mLang[id] = str;
        }
    }
    else
    {
        // Default Lang : English
        std::ifstream eng("Assets/Data/eng.dat");
        if (eng)
        {
            std::string line;
            while (std::getline(file,line))
            {
                auto f = line.find("=");
                std::string id = line.substr(0,f);
                std::string str = line.substr(f+1);
                mInstance.mLang[id] = str;
            }
        }
    }
}

Game::~Game()
{
    save();
}

bool Game::load()
{
    //
    // Load Keys
    //
    pugi::xml_document doc;
    if (!doc.load_file("Assets/Data/settings.xml"))
    {
        return false;
    }
    pugi::xml_node game = doc.child("GameSettings");
    if (game)
    {
        for (pugi::xml_node action = game.child("Action"); action; action = action.next_sibling("Action"))
        {
            std::string id = action.attribute("id").value();
            std::string key = action.attribute("key").value();
            bool hold = action.attribute("hold").as_bool();

            mKeys[id].first = thor::toKeyboardKey(key);
            mKeys[id].second = hold;
        }

        return true;
    }
    return false;
}

void Game::save()
{
    pugi::xml_document doc;
    doc.load_file("Assets/Data/settings.xml");
    if (doc.child("GameSettings"))
    {
        doc.remove_child("GameSettings");
    }
    pugi::xml_node game = doc.append_child("GameSettings");

    for (auto itr = mKeys.begin(); itr != mKeys.end(); itr++)
    {
        pugi::xml_node a = game.append_child("Action");
        a.append_attribute("id") = itr->first.c_str();
        a.append_attribute("key") = thor::toString(itr->second.first).c_str();
        a.append_attribute("hold") = itr->second.second;
    }

    doc.save_file("Assets/Data/settings.xml");
}
