#include "GameState.hpp"
#include <iostream>

GameState::GameState(ah::StateManager& manager)
: ah::State(manager,lp::type<GameState>())
{
    Game::startNewGame();

    mView = ah::Application::getWindow().getDefaultView();
    mView.setCenter(0.f,0.f);
    mAction = 0;

    sf::Vector2f wSize = static_cast<sf::Vector2f>(ah::Application::getWindow().getSize());

    mHUDMoneySprite.setTexture(ah::Application::getResources().getTexture("hud"));
    mHUDMoneySprite.setTextureRect(sf::IntRect(0,0,270,60));
    mHUDMoneySprite.setOrigin(0,60);
    mHUDMoneySprite.setPosition(0.f,wSize.y);
    mHUDMoneyText.setFont(ah::Application::getResources().getFont("cool"));
    mHUDMoneyText.setColor(sf::Color::White);
    mHUDMoneyText.setCharacterSize(30);
    mHUDMoneyText.setString("$" + std::to_string(static_cast<int>(Game::getMoney())));
    mHUDMoneyText.setPosition(135 - mHUDMoneyText.getGlobalBounds().width / 2, wSize.y - 30 - mHUDMoneyText.getGlobalBounds().height / 2);

    mHUDWaveSprite.setTexture(ah::Application::getResources().getTexture("hud"));
    mHUDWaveSprite.setTextureRect(sf::IntRect(0,0,270,60));
    mHUDWaveSprite.setOrigin(270,60);
    mHUDWaveSprite.setPosition(wSize);
    mHUDWaveText.setFont(ah::Application::getResources().getFont("cool"));
    mHUDWaveText.setColor(sf::Color::White);
    mHUDWaveText.setCharacterSize(30);
    mHUDWaveText.setString(Game::getString("NewWave") + " : ?");
    mHUDWaveText.setPosition(mHUDWaveSprite.getPosition().x - 135 - mHUDWaveText.getGlobalBounds().width / 2, mHUDWaveSprite.getPosition().y - 30 - mHUDWaveText.getGlobalBounds().height / 2);

    mHUDActionSprite.setTexture(ah::Application::getResources().getTexture("hud"));
    mHUDActionSprite.setTextureRect(sf::IntRect(270,0,46,46));
    mHUDActionSprite.setPosition(270.f,wSize.y-46);
    mHUDActionIcon.setPosition(mHUDActionSprite.getPosition() + sf::Vector2f(7,7));

    mHUDUnlockSprite.setTexture(ah::Application::getResources().getTexture("hud"));
    mHUDUnlockSprite.setTextureRect(sf::IntRect(270,0,46,46));
    mHUDUnlockSprite.setPosition(wSize.x - 46,100.f-46);
    mHUDUnlockIcon.setTexture(ah::Application::getResources().getTexture("tileset"));
    mHUDUnlockIcon.setTextureRect(sf::IntRect(32,0,32,32));
    mHUDUnlockIcon.setPosition(wSize.x - 46 + 7,100.f + 7 - 46);
    mHUDCollectSprite.setTexture(ah::Application::getResources().getTexture("hud"));
    mHUDCollectSprite.setTextureRect(sf::IntRect(270,0,46,46));
    mHUDCollectSprite.setPosition(wSize.x - 46,100.f);
    mHUDCollectIcon.setTexture(ah::Application::getResources().getTexture("tileset"));
    mHUDCollectIcon.setTextureRect(sf::IntRect(64,0,32,32));
    mHUDCollectIcon.setPosition(wSize.x - 46 + 7,100.f + 7);

    mHUDPlant1Sprite.setTexture(ah::Application::getResources().getTexture("hud"));
    mHUDPlant1Sprite.setTextureRect(sf::IntRect(270,0,46,46));
    mHUDPlant1Sprite.setPosition(wSize.x - 46,110.f +  46.f);
    mHUDPlant1Icon.setTexture(ah::Application::getResources().getTexture("tileset"));
    mHUDPlant1Icon.setTextureRect(sf::IntRect(128,32,32,32));
    mHUDPlant1Icon.setPosition(wSize.x - 46 + 7,110.f + 46.f + 7);
    mHUDPlant2Sprite.setTexture(ah::Application::getResources().getTexture("hud"));
    mHUDPlant2Sprite.setTextureRect(sf::IntRect(270,0,46,46));
    mHUDPlant2Sprite.setPosition(wSize.x - 46,110.f + 2 * 46.f);
    mHUDPlant2Icon.setTexture(ah::Application::getResources().getTexture("tileset"));
    mHUDPlant2Icon.setTextureRect(sf::IntRect(128,64,32,32));
    mHUDPlant2Icon.setPosition(wSize.x - 46 + 7,110.f + 2 * 46 + 7);
    mHUDPlant3Sprite.setTexture(ah::Application::getResources().getTexture("hud"));
    mHUDPlant3Sprite.setTextureRect(sf::IntRect(270,0,46,46));
    mHUDPlant3Sprite.setPosition(wSize.x - 46,110.f + 3 * 46.f);
    mHUDPlant3Icon.setTexture(ah::Application::getResources().getTexture("tileset"));
    mHUDPlant3Icon.setTextureRect(sf::IntRect(128,96,32,32));
    mHUDPlant3Icon.setPosition(wSize.x - 46 + 7,110.f + 3 * 46 + 7);

    mHUDTurret1Sprite.setTexture(ah::Application::getResources().getTexture("hud"));
    mHUDTurret1Sprite.setTextureRect(sf::IntRect(270,0,46,46));
    mHUDTurret1Sprite.setPosition(wSize.x - 46,300.f);
    mHUDTurret1Icon.setTexture(ah::Application::getResources().getTexture("turrets"));
    mHUDTurret1Icon.setTextureRect(sf::IntRect(0,0,32,32));
    mHUDTurret1Icon.setPosition(wSize.x - 46 + 7,300 + 7);
    mHUDTurret2Sprite.setTexture(ah::Application::getResources().getTexture("hud"));
    mHUDTurret2Sprite.setTextureRect(sf::IntRect(270,0,46,46));
    mHUDTurret2Sprite.setPosition(wSize.x - 46,300.f + 46);
    mHUDTurret2Icon.setTexture(ah::Application::getResources().getTexture("turrets"));
    mHUDTurret2Icon.setTextureRect(sf::IntRect(32,0,32,32));
    mHUDTurret2Icon.setPosition(wSize.x - 46 + 7,300 + 7 + 46);
    mHUDTurret3Sprite.setTexture(ah::Application::getResources().getTexture("hud"));
    mHUDTurret3Sprite.setTextureRect(sf::IntRect(270,0,46,46));
    mHUDTurret3Sprite.setPosition(wSize.x - 46,300.f + 2 * 46);
    mHUDTurret3Icon.setTexture(ah::Application::getResources().getTexture("turrets"));
    mHUDTurret3Icon.setTextureRect(sf::IntRect(64,0,32,32));
    mHUDTurret3Icon.setPosition(wSize.x - 46 + 7,300 + 7 + 2 * 46);
    mHUDTurret4Sprite.setTexture(ah::Application::getResources().getTexture("hud"));
    mHUDTurret4Sprite.setTextureRect(sf::IntRect(270,0,46,46));
    mHUDTurret4Sprite.setPosition(wSize.x - 46,300.f + 3 * 46);
    mHUDTurret4Icon.setTexture(ah::Application::getResources().getTexture("turrets"));
    mHUDTurret4Icon.setTextureRect(sf::IntRect(96,0,32,32));
    mHUDTurret4Icon.setPosition(wSize.x - 46 + 7,300 + 7 + 3 * 46);
}

GameState::~GameState()
{
    Game::startMenu();
}

bool GameState::handleEvent(sf::Event const& event)
{
    sf::Vector2f mPos = ah::Application::getWindow().getMousePosition();
    sf::Vector2f mPosV = ah::Application::getWindow().getMousePositionView(mView);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        requestPush(lp::type<EndGameState>());
    }
    if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
    {
        if (event.mouseWheelScroll.delta < 1)
        {
            if (mView.getSize().x < 1024.f)
                mView.zoom(1.2f);
        }
        else
        {
            if (mView.getSize().x > 320.f)
                mView.zoom(0.8f);
        }
    }

    if ((mHUDUnlockSprite.getGlobalBounds().contains(mPos) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        || (event.type == sf::Event::KeyPressed && event.key.code == Game::getActionKey("1")))
    {
        mAction = 1;
    }
    else if ((mHUDCollectSprite.getGlobalBounds().contains(mPos) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        || (event.type == sf::Event::KeyPressed && event.key.code == Game::getActionKey("2")))
    {
        mAction = 2;
    }
    else if ((mHUDPlant1Sprite.getGlobalBounds().contains(mPos) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        || (event.type == sf::Event::KeyPressed && event.key.code == Game::getActionKey("3")))
    {
        mAction = 3;
    }
    else if ((mHUDPlant2Sprite.getGlobalBounds().contains(mPos) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        || (event.type == sf::Event::KeyPressed && event.key.code == Game::getActionKey("4")))
    {
        mAction = 4;
    }
    else if ((mHUDPlant3Sprite.getGlobalBounds().contains(mPos) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        || (event.type == sf::Event::KeyPressed && event.key.code == Game::getActionKey("5")))
    {
        mAction = 5;
    }
    else if ((mHUDTurret1Sprite.getGlobalBounds().contains(mPos) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        || (event.type == sf::Event::KeyPressed && event.key.code == Game::getActionKey("6")))
    {
        mAction = 6;
    }
    else if ((mHUDTurret2Sprite.getGlobalBounds().contains(mPos) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        || (event.type == sf::Event::KeyPressed && event.key.code == Game::getActionKey("7")))
    {
        mAction = 7;
    }
    else if ((mHUDTurret3Sprite.getGlobalBounds().contains(mPos) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        || (event.type == sf::Event::KeyPressed && event.key.code == Game::getActionKey("8")))
    {
        mAction = 8;
    }
    else if ((mHUDTurret4Sprite.getGlobalBounds().contains(mPos) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        || (event.type == sf::Event::KeyPressed && event.key.code == Game::getActionKey("9")))
    {
        mAction = 9;
    }
    else
    {
        sf::FloatRect farmRect = sf::FloatRect(-173.f,-173.f,320.f,320.f);
        if (!farmRect.contains(mPosV) && mAction > 5 && mAction <= 9 && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            mManager.placeTurret(mPosV,mAction - 6);
        }
    }

    return true;
}

bool GameState::update(sf::Time dt)
{
    if (mManager.getRemainingPlants() <= 0)
    {
        requestPush(lp::type<EndGameState>());
    }

    sf::Vector2f mPos = ah::Application::getWindow().getMousePositionView(mView);
    sf::Vector2f mPosS = ah::Application::getWindow().getMousePosition();

    // View movement
    lp::ActionMapPtr actions = Game::getActionMap();
    actions->update(ah::Application::getWindow());

    // Update entities
    mManager.update(dt);

    // Update money
    mMoneyTime += dt;
    if (mMoneyTime > sf::seconds(1.f))
    {
        mMoneyTime = sf::Time::Zero;
        Game::increaseMoney(1.f);
    }

    // Handle realtime actions
    // Mouse is pressed and isnt in any buttons
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
     && !(mHUDUnlockSprite.getGlobalBounds().contains(mPosS)
     || mHUDPlant1Sprite.getGlobalBounds().contains(mPosS)
     || mHUDPlant2Sprite.getGlobalBounds().contains(mPosS)
     || mHUDPlant3Sprite.getGlobalBounds().contains(mPosS)
     || mHUDCollectSprite.getGlobalBounds().contains(mPosS)
     || mHUDTurret1Sprite.getGlobalBounds().contains(mPosS)
     || mHUDTurret2Sprite.getGlobalBounds().contains(mPosS)
     || mHUDTurret3Sprite.getGlobalBounds().contains(mPosS)
     || mHUDTurret4Sprite.getGlobalBounds().contains(mPosS)))
    {
        sf::FloatRect farmRect = sf::FloatRect(-173.f,-173.f,320.f,320.f);
        if (farmRect.contains(mPos))
        {
            if (mAction == 1 && mManager.canBeUnlocked(mPos))
            {
                mManager.unlock(mPos);
            }
            else if (mAction > 2 && mAction <= 5 && mManager.isPlantable(mPos))
            {
                mManager.setPlantSeed(mPos,mAction - 2);
            }
            else if (mAction == 2)
            {
                mManager.collectSeed(mPos);
            }
        }
    }

    // Update HUD
    mHUDMoneyText.setString("$" + std::to_string(static_cast<int>(Game::getMoney())));
    mHUDMoneyText.setPosition(135 - mHUDMoneyText.getGlobalBounds().width / 2, mHUDMoneySprite.getPosition().y - 30 - mHUDMoneyText.getGlobalBounds().height / 2);

    int r;
    if (mManager.getDuration() < sf::seconds(15))
    {
        r = (int)15-mManager.getDuration().asSeconds();
    }
    else if (mManager.getDuration() < sf::seconds(200))
    {
        r = (int)200-mManager.getDuration().asSeconds();
    }
    else if (mManager.getDuration() > sf::seconds(200))
    {
        r = (int)mManager.getDuration().asSeconds();
        r %= 100;
        r = 100 - r;
    }
    std::string remaining = (r <= 20) ? std::to_string(r) : "?";
    mHUDWaveText.setString(Game::getString("NewWave") + " : " + remaining);
    mHUDWaveText.setPosition(mHUDWaveSprite.getPosition().x - 135 - mHUDWaveText.getGlobalBounds().width / 2, mHUDWaveSprite.getPosition().y - 30 - mHUDWaveText.getGlobalBounds().height / 2);


    // Debug Info
    ah::Application::getWindow().setDebugInfo("pos-x",std::to_string((int)mPos.x));
    ah::Application::getWindow().setDebugInfo("pos-y",std::to_string((int)mPos.y));
    ah::Application::getWindow().setDebugInfo("plants",std::to_string(mManager.getRemainingPlants()));
    ah::Application::getWindow().setDebugInfo("turrets",std::to_string(mManager.getRemainingTurrets()));
    ah::Application::getWindow().setDebugInfo("zombies",std::to_string(mManager.getRemainingZombies()));
    ah::Application::getWindow().setDebugInfo("action",std::to_string(mAction));
    ah::Application::getWindow().setDebugInfo("tSpawn",std::to_string(1/(0.01f * mManager.getDuration().asSeconds() + 0.5f)));
    ah::Application::getWindow().setDebugInfo("tDuration",std::to_string((int)mManager.getDuration().asSeconds()));
    ah::Application::getWindow().setDebugInfo("tSpawnCount",std::to_string(mManager.getSpawnCount()));

    return true;
}

void GameState::render(sf::RenderTarget& target, sf::RenderStates states)
{
    sf::Vector2f mPos = ah::Application::getWindow().getMousePosition();

    sf::View old = target.getView();
    target.setView(mView);

    states.transform *= getTransform();
    target.draw(mBgLayer,states);

    mManager.render(target,states);

    sf::RectangleShape farmRect;
    farmRect.setSize(sf::Vector2f(320,320));
    farmRect.setPosition(-173.f,-173.f);
    farmRect.setOutlineColor(sf::Color::Red);
    farmRect.setOutlineThickness(2.f);
    farmRect.setFillColor(sf::Color::Transparent);
    target.draw(farmRect);

    target.setView(old);

    target.draw(mHUDMoneySprite);
    target.draw(mHUDMoneyText);

    target.draw(mHUDWaveSprite);
    target.draw(mHUDWaveText);

    target.draw(mHUDUnlockSprite);
    target.draw(mHUDPlant1Sprite);
    target.draw(mHUDPlant2Sprite);
    target.draw(mHUDPlant3Sprite);
    target.draw(mHUDCollectSprite);
    target.draw(mHUDUnlockIcon);
    target.draw(mHUDPlant1Icon);
    target.draw(mHUDPlant2Icon);
    target.draw(mHUDPlant3Icon);
    target.draw(mHUDCollectIcon);

    target.draw(mHUDTurret1Sprite);
    target.draw(mHUDTurret2Sprite);
    target.draw(mHUDTurret3Sprite);
    target.draw(mHUDTurret4Sprite);
    target.draw(mHUDTurret1Icon);
    target.draw(mHUDTurret2Icon);
    target.draw(mHUDTurret3Icon);
    target.draw(mHUDTurret4Icon);

    target.draw(mHUDActionSprite);
    switch (mAction)
    {
        case 1: // unlock
        {
            mHUDActionIcon.setTexture(ah::Application::getResources().getTexture("tileset"));
            mHUDActionIcon.setTextureRect(sf::IntRect(32,0,32,32));
        } break;
        case 2: // collect
        {
            mHUDActionIcon.setTexture(ah::Application::getResources().getTexture("tileset"));
            mHUDActionIcon.setTextureRect(sf::IntRect(64,0,32,32));
        } break;
        case 3: // plant 1
        {
            mHUDActionIcon.setTexture(ah::Application::getResources().getTexture("tileset"));
            mHUDActionIcon.setTextureRect(sf::IntRect(128,32,32,32));
        } break;
        case 4: // plant 2
        {
            mHUDActionIcon.setTexture(ah::Application::getResources().getTexture("tileset"));
            mHUDActionIcon.setTextureRect(sf::IntRect(128,64,32,32));
        } break;
        case 5: // plant 3
        {
            mHUDActionIcon.setTexture(ah::Application::getResources().getTexture("tileset"));
            mHUDActionIcon.setTextureRect(sf::IntRect(128,96,32,32));
        } break;
        case 6: // turret 1
        {
            mHUDActionIcon.setTexture(ah::Application::getResources().getTexture("turrets"));
            mHUDActionIcon.setTextureRect(sf::IntRect(0,0,32,32));
        } break;
        case 7: // turret 2
        {
            mHUDActionIcon.setTexture(ah::Application::getResources().getTexture("turrets"));
            mHUDActionIcon.setTextureRect(sf::IntRect(32,0,32,32));
        } break;
        case 8: // turret 3
        {
            mHUDActionIcon.setTexture(ah::Application::getResources().getTexture("turrets"));
            mHUDActionIcon.setTextureRect(sf::IntRect(64,0,32,32));
        } break;
        case 9: // turret 4
        {
            mHUDActionIcon.setTexture(ah::Application::getResources().getTexture("turrets"));
            mHUDActionIcon.setTextureRect(sf::IntRect(96,0,32,32));
        } break;
        default: break;
    }
    if (mAction != 0)
    {
        target.draw(mHUDActionIcon);
    }

    sf::Sprite hoverBg(ah::Application::getResources().getTexture("hud"));
    hoverBg.setTextureRect(sf::IntRect(270+46+1,0,135,98));
    sf::Text hoverText("",ah::Application::getResources().getFont("cool"),20);
    hoverText.setColor(sf::Color::White);
    if (mHUDUnlockSprite.getGlobalBounds().contains(mPos))
    {
        hoverBg.setPosition(mHUDUnlockSprite.getPosition().x - 145,mHUDUnlockSprite.getPosition().y - 23);
        std::ostringstream oss;
        oss << Game::getString("Unlock") + "\n";
        oss << Game::getString("Cost") + ":" + std::to_string((int)mManager.getUnlockPrice()) + "\n";
        hoverText.setString(oss.str());
        hoverText.setPosition(hoverBg.getPosition().x + hoverBg.getGlobalBounds().width/2 - hoverText.getGlobalBounds().width/2,
                              hoverBg.getPosition().y + hoverBg.getGlobalBounds().height/2 - hoverText.getGlobalBounds().height/2);

        target.draw(hoverBg);
        target.draw(hoverText);
    }
    else if (mHUDPlant1Sprite.getGlobalBounds().contains(mPos))
    {
        hoverBg.setPosition(mHUDPlant1Sprite.getPosition().x - 145,mHUDPlant1Sprite.getPosition().y - 23);
        std::ostringstream oss;
        oss << Game::getString("Cost") + ":" + std::to_string((int)Plant::getCost(1)) + "\n";
        oss << Game::getString("Time") + ":" + std::to_string((int)Plant::getDuration(1).asSeconds()) + "\n";
        oss << Game::getString("Price") + ":" + std::to_string((int)Plant::getMoney(1));
        hoverText.setString(oss.str());
        hoverText.setPosition(hoverBg.getPosition().x + hoverBg.getGlobalBounds().width/2 - hoverText.getGlobalBounds().width/2,
                              hoverBg.getPosition().y + hoverBg.getGlobalBounds().height/2 - hoverText.getGlobalBounds().height/2);

        target.draw(hoverBg);
        target.draw(hoverText);
    }
    else if (mHUDPlant2Sprite.getGlobalBounds().contains(mPos))
    {
        hoverBg.setPosition(mHUDPlant2Sprite.getPosition().x - 145,mHUDPlant2Sprite.getPosition().y - 23);
        std::ostringstream oss;
        oss << Game::getString("Cost") + ":" + std::to_string((int)Plant::getCost(2)) + "\n";
        oss << Game::getString("Time") + ":" + std::to_string((int)Plant::getDuration(2).asSeconds()) + "\n";
        oss << Game::getString("Price") + ":" + std::to_string((int)Plant::getMoney(2));
        hoverText.setString(oss.str());
        hoverText.setPosition(hoverBg.getPosition().x + hoverBg.getGlobalBounds().width/2 - hoverText.getGlobalBounds().width/2,
                              hoverBg.getPosition().y + hoverBg.getGlobalBounds().height/2 - hoverText.getGlobalBounds().height/2);

        target.draw(hoverBg);
        target.draw(hoverText);
    }
    else if (mHUDPlant3Sprite.getGlobalBounds().contains(mPos))
    {
        hoverBg.setPosition(mHUDPlant3Sprite.getPosition().x - 145,mHUDPlant3Sprite.getPosition().y - 23);
        std::ostringstream oss;
        oss << Game::getString("Cost") + ":" + std::to_string((int)Plant::getCost(3)) + "\n";
        oss << Game::getString("Time") + ":" + std::to_string((int)Plant::getDuration(3).asSeconds()) + "\n";
        oss << Game::getString("Price") + ":" + std::to_string((int)Plant::getMoney(3));
        hoverText.setString(oss.str());
        hoverText.setPosition(hoverBg.getPosition().x + hoverBg.getGlobalBounds().width/2 - hoverText.getGlobalBounds().width/2,
                              hoverBg.getPosition().y + hoverBg.getGlobalBounds().height/2 - hoverText.getGlobalBounds().height/2);

        target.draw(hoverBg);
        target.draw(hoverText);
    }
    else if (mHUDCollectSprite.getGlobalBounds().contains(mPos))
    {
        hoverBg.setPosition(mHUDCollectSprite.getPosition().x - 145,mHUDCollectSprite.getPosition().y - 23);
        std::ostringstream oss;
        oss << Game::getString("Collect");
        hoverText.setString(oss.str());
        hoverText.setPosition(hoverBg.getPosition().x + hoverBg.getGlobalBounds().width/2 - hoverText.getGlobalBounds().width/2,
                              hoverBg.getPosition().y + hoverBg.getGlobalBounds().height/2 - hoverText.getGlobalBounds().height/2);

        target.draw(hoverBg);
        target.draw(hoverText);
    }
    else if (mHUDTurret1Sprite.getGlobalBounds().contains(mPos))
    {
        hoverBg.setPosition(mHUDTurret1Sprite.getPosition().x - 145,mHUDTurret1Sprite.getPosition().y - 23);
        std::ostringstream oss;
        oss << Game::getString("Cost") + ":" + std::to_string((int)Turret::getCost(0)) + "\n";
        oss << Game::getString("DPS") + ":" + std::to_string((int)(Turret::getDamage(0) / Turret::getRate(0).asSeconds())) + "\n";
        oss << Game::getString("Life") + ":" + std::to_string((int)Turret::getLife(0));
        hoverText.setString(oss.str());
        hoverText.setPosition(hoverBg.getPosition().x + hoverBg.getGlobalBounds().width/2 - hoverText.getGlobalBounds().width/2,
                              hoverBg.getPosition().y + hoverBg.getGlobalBounds().height/2 - hoverText.getGlobalBounds().height/2);

        target.draw(hoverBg);
        target.draw(hoverText);
    }
    else if (mHUDTurret2Sprite.getGlobalBounds().contains(mPos))
    {
        hoverBg.setPosition(mHUDTurret2Sprite.getPosition().x - 145,mHUDTurret2Sprite.getPosition().y - 23);
        std::ostringstream oss;
        oss << Game::getString("Cost") + ":" + std::to_string((int)Turret::getCost(1)) + "\n";
        oss << Game::getString("DPS") + ":" + std::to_string((int)(Turret::getDamage(1) / Turret::getRate(1).asSeconds())) + "\n";
        oss << Game::getString("Life") + ":" + std::to_string((int)Turret::getLife(1));
        hoverText.setString(oss.str());
        hoverText.setPosition(hoverBg.getPosition().x + hoverBg.getGlobalBounds().width/2 - hoverText.getGlobalBounds().width/2,
                              hoverBg.getPosition().y + hoverBg.getGlobalBounds().height/2 - hoverText.getGlobalBounds().height/2);

        target.draw(hoverBg);
        target.draw(hoverText);
    }
    else if (mHUDTurret3Sprite.getGlobalBounds().contains(mPos))
    {
        hoverBg.setPosition(mHUDTurret3Sprite.getPosition().x - 145,mHUDTurret3Sprite.getPosition().y - 23);
        std::ostringstream oss;
        oss << Game::getString("Cost") + ":" + std::to_string((int)Turret::getCost(2)) + "\n";
        oss << Game::getString("DPS") + ":" + std::to_string((int)(Turret::getDamage(2) / Turret::getRate(2).asSeconds())) + "\n";
        oss << Game::getString("Life") + ":" + std::to_string((int)Turret::getLife(2));
        hoverText.setString(oss.str());
        hoverText.setPosition(hoverBg.getPosition().x + hoverBg.getGlobalBounds().width/2 - hoverText.getGlobalBounds().width/2,
                              hoverBg.getPosition().y + hoverBg.getGlobalBounds().height/2 - hoverText.getGlobalBounds().height/2);

        target.draw(hoverBg);
        target.draw(hoverText);
    }
    else if (mHUDTurret4Sprite.getGlobalBounds().contains(mPos))
    {
        hoverBg.setPosition(mHUDTurret4Sprite.getPosition().x - 145,mHUDTurret4Sprite.getPosition().y - 23);
        std::ostringstream oss;
        oss << Game::getString("Cost") + ":" + std::to_string((int)Turret::getCost(3)) + "\n";
        oss << Game::getString("DPS") + ":" + std::to_string((int)(Turret::getDamage(3) / Turret::getRate(3).asSeconds())) + "\n";
        oss << Game::getString("Life") + ":" + std::to_string((int)Turret::getLife(3));
        hoverText.setString(oss.str());
        hoverText.setPosition(hoverBg.getPosition().x + hoverBg.getGlobalBounds().width/2 - hoverText.getGlobalBounds().width/2,
                              hoverBg.getPosition().y + hoverBg.getGlobalBounds().height/2 - hoverText.getGlobalBounds().height/2);

        target.draw(hoverBg);
        target.draw(hoverText);
    }
}
