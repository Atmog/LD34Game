#include "SettingsState.hpp"

SettingsState::SettingsState(ah::StateManager& manager)
: ah::State(manager,lp::type<SettingsState>())
{
    mKeySelected = 0;

    sf::Vector2u wSize = ah::Application::getWindow().getSize();
    sf::Vector2f scale = sf::Vector2f(wSize.x/800.f,wSize.y/600.f);

    sf::Vector2f bSize = sf::Vector2f(400 * scale.x, 75 * scale.y);

    mWindow = sfg::Window::Create(sfg::Window::BACKGROUND);
    auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);

    //Begin Audio
    mGlobalL = sfg::Label::Create(std::to_string(static_cast<int>(ah::Application::getAudio().getGlobalVolume())));
    mGlobalS = sfg::Scale::Create(0.f,100.f,1.f,sfg::Range::Orientation::HORIZONTAL);
    mGlobalS->SetValue(ah::Application::getAudio().getGlobalVolume());
    mGlobalS->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect([&]()
    {
        float v = mGlobalS->GetValue();
        mGlobalL->SetText(std::to_string(static_cast<int>(v)));
        ah::Application::getAudio().setGlobalVolume(v);
    });
    auto h1 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h1->Pack(sfg::Label::Create(Game::getString("Global")));
    h1->Pack(mGlobalS);
    h1->Pack(mGlobalL);

    mMusicL = sfg::Label::Create(std::to_string(static_cast<int>(ah::Application::getAudio().getMusicVolume())));
    mMusicS = sfg::Scale::Create(0.f,100.f,1.f,sfg::Range::Orientation::HORIZONTAL);
    mMusicS->SetValue(ah::Application::getAudio().getMusicVolume());
    mMusicS->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect([&]()
    {
        float v = mMusicS->GetValue();
        mMusicL->SetText(std::to_string(static_cast<int>(v)));
        ah::Application::getAudio().setMusicVolume(v);
        Game::updateMusicVolume();
    });
    auto h2 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h2->Pack(sfg::Label::Create(Game::getString("Music")));
    h2->Pack(mMusicS);
    h2->Pack(mMusicL);

    mSoundL = sfg::Label::Create(std::to_string(static_cast<int>(ah::Application::getAudio().getSoundVolume())));
    mSoundS = sfg::Scale::Create(0.f,100.f,1.f,sfg::Range::Orientation::HORIZONTAL);
    mSoundS->SetValue(ah::Application::getAudio().getSoundVolume());
    mSoundS->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect([&]()
    {
        float v = mSoundS->GetValue();
        mSoundL->SetText(std::to_string(static_cast<int>(v)));
        ah::Application::getAudio().setSoundVolume(v);
    });
    auto h3 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h3->Pack(sfg::Label::Create(Game::getString("Sound")));
    h3->Pack(mSoundS);
    h3->Pack(mSoundL);

    auto a = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);
    a->Pack(h1);
    a->Pack(h2);
    a->Pack(h3);

    auto frameA = sfg::Frame::Create(Game::getString("Audio"));
    frameA->Add(a);
    frameA->SetAlignment(sf::Vector2f(0.1f,0.f));

    box->Pack(frameA);
    //End Audio

    // Begin Graphics
    mRes = sfg::ComboBox::Create();
    auto res = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < res.size(); i++)
    {
        sf::Vector2u s = sf::Vector2u(res[i].width,res[i].height);
        if (s.x != wSize.x && s.y != wSize.y)
        {
            mRes->AppendItem(std::to_string(s.x) + "x" + std::to_string(s.y));
        }
    }
    mRes->PrependItem(std::to_string(wSize.x) + "x" + std::to_string(wSize.y));
    mRes->SelectItem(0);
    mRes->GetSignal(sfg::ComboBox::OnSelect).Connect([&]()
    {
        std::string s = static_cast<std::string>(mRes->GetSelectedText());
        std::string w = s.substr(0,s.find("x"));
        std::string h = s.substr(s.find("x")+1);
        ah::Application::getWindow().setVideoMode(sf::VideoMode(std::stoi(w),std::stoi(h)));
        sf::Vector2u ws = ah::Application::getWindow().getSize();
        sf::Vector2f sc = sf::Vector2f(ws.x/800.f,ws.y/600.f);
        mWindow->Refresh();
        mWindow->SetPosition(sf::Vector2f(ws.x / 2.f - mWindow->GetAllocation().width / 2.f, ws.y / 2.f - mWindow->GetAllocation().height / 2.f));
        mBackground.setScale(sc);
        ah::Application::getWindow().useCustomMouseCursor(&ah::Application::getResources().getTexture("cursor"));
    });

    auto h4 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h4->Pack(sfg::Label::Create(Game::getString("VideoMode")));
    h4->Pack(mRes);

    mVerticalSync = sfg::CheckButton::Create(Game::getString("VerticalSync"));
    mVerticalSync->SetActive(ah::Application::getWindow().isVerticalSyncEnabled());
    mVerticalSync->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        ah::Application::getWindow().setVerticalSyncEnabled(mVerticalSync->IsActive());
        ah::Application::getWindow().setDebugInfo("VerticalSync",std::to_string(ah::Application::getWindow().isVerticalSyncEnabled()));
    });
    auto h5 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h5->Pack(mVerticalSync);

    mFullscreen = sfg::CheckButton::Create(Game::getString("Fullscreen"));
    mFullscreen->SetActive(ah::Application::getWindow().isFullscreen());
    mFullscreen->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        ah::Application::getWindow().setFullscreen(mFullscreen->IsActive());
        ah::Application::getWindow().useCustomMouseCursor(&ah::Application::getResources().getTexture("cursor"));
    });
    auto h6 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h6->Pack(mFullscreen);

    auto b = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);
    b->Pack(h4);
    b->Pack(h5);
    b->Pack(h6);

    auto frameG = sfg::Frame::Create(Game::getString("Graphics"));
    frameG->Add(b);
    frameG->SetAlignment(sf::Vector2f(0.1f,0.f));

    box->Pack(frameG);
    // End Graphics

    // Begin Key Binding
    mKey1 = sfg::Button::Create(thor::toString(Game::getActionKey("1")));
    mKey1->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        mKeySelected = 1;
    });
    auto h7 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h7->Pack(sfg::Label::Create(Game::getString("UnlockK")));
    h7->Pack(mKey1);

    mKey2 = sfg::Button::Create(thor::toString(Game::getActionKey("2")));
    mKey2->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        mKeySelected = 2;
    });
    auto h8 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h8->Pack(sfg::Label::Create(Game::getString("CollectK")));
    h8->Pack(mKey2);

    mKey3 = sfg::Button::Create(thor::toString(Game::getActionKey("3")));
    mKey3->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        mKeySelected = 3;
    });
    auto h9 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h9->Pack(sfg::Label::Create(Game::getString("Plant1")));
    h9->Pack(mKey3);

    mKey4 = sfg::Button::Create(thor::toString(Game::getActionKey("4")));
    mKey4->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        mKeySelected = 4;
    });
    auto h10 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h10->Pack(sfg::Label::Create(Game::getString("Plant2")));
    h10->Pack(mKey4);

    mKey5 = sfg::Button::Create(thor::toString(Game::getActionKey("5")));
    mKey5->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        mKeySelected = 5;
    });
    auto h11 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h11->Pack(sfg::Label::Create(Game::getString("Plant3")));
    h11->Pack(mKey5);

    mKey6 = sfg::Button::Create(thor::toString(Game::getActionKey("6")));
    mKey6->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        mKeySelected = 6;
    });
    auto h12 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h12->Pack(sfg::Label::Create(Game::getString("Turret1")));
    h12->Pack(mKey6);

    mKey7 = sfg::Button::Create(thor::toString(Game::getActionKey("7")));
    mKey7->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        mKeySelected = 7;
    });
    auto h13 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h13->Pack(sfg::Label::Create(Game::getString("Turret2")));
    h13->Pack(mKey7);

    mKey8 = sfg::Button::Create(thor::toString(Game::getActionKey("8")));
    mKey8->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        mKeySelected = 8;
    });
    auto h14 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h14->Pack(sfg::Label::Create(Game::getString("Turret3")));
    h14->Pack(mKey8);

    mKey9 = sfg::Button::Create(thor::toString(Game::getActionKey("9")));
    mKey9->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        mKeySelected = 9;
    });
    auto h15 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    h15->Pack(sfg::Label::Create(Game::getString("Turret4")));
    h15->Pack(mKey9);

    auto c = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 2.f);
    c->Pack(h7);
    c->Pack(h8);
    c->Pack(h9);
    c->Pack(h10);
    c->Pack(h11);
    c->Pack(h12);
    c->Pack(h13);
    c->Pack(h14);
    c->Pack(h15);

    auto frameB = sfg::Frame::Create(Game::getString("Binding"));
    frameB->Add(c);
    frameB->SetAlignment(sf::Vector2f(0.1f,0.f));

    box->Pack(frameB);

    // End Key Binding

    auto buttonQuit = sfg::Button::Create(Game::getString("Return"));
	buttonQuit->SetClass("menu_button");
	buttonQuit->SetAllocation(sf::FloatRect(wSize.x / 2 - bSize.x * 0.5f, 450.f * scale.y, bSize.x, bSize.y));
	buttonQuit->GetSignal(sfg::Widget::OnLeftClick).Connect([&]()
    {
        ah::Application::getWindow().useCustomMouseCursor(&ah::Application::getResources().getTexture("cursor"));
        requestClear();
        requestPush(lp::type<MenuState>());
    });

    box->Pack(buttonQuit);

    mWindow->Add(box);
    mWindow->SetPosition(sf::Vector2f(wSize.x / 2.f - mWindow->GetAllocation().width / 2.f, wSize.y / 2.f - mWindow->GetAllocation().height / 2.f));

	mDesktop.SetProperty("Button.menu_button","FontSize",std::to_string(static_cast<unsigned int>(25 * scale.y)));
	mDesktop.Add(mWindow);

	mBackground.setTexture(ah::Application::getResources().getTexture("bg"));
	mBackground.setScale(scale);
}

SettingsState::~SettingsState()
{
}

bool SettingsState::handleEvent(sf::Event const& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        mKeySelected = 0;
    }
    if (event.type == sf::Event::KeyPressed && mKeySelected != 0)
    {
        switch (mKeySelected)
        {
            case 1:
            {
                Game::setActionKey("1",event.key.code);
                mKey1->SetLabel(thor::toString(event.key.code));
            } break;

            case 2:
            {
                Game::setActionKey("2",event.key.code);
                mKey2->SetLabel(thor::toString(event.key.code));
            } break;

            case 3:
            {
                Game::setActionKey("3",event.key.code);
                mKey3->SetLabel(thor::toString(event.key.code));
            } break;

            case 4:
            {
                Game::setActionKey("4",event.key.code);
                mKey4->SetLabel(thor::toString(event.key.code));
            } break;

            case 5:
            {
                Game::setActionKey("5",event.key.code);
                mKey5->SetLabel(thor::toString(event.key.code));
            } break;

            case 6:
            {
                Game::setActionKey("6",event.key.code);
                mKey6->SetLabel(thor::toString(event.key.code));
            } break;

            case 7:
            {
                Game::setActionKey("7",event.key.code);
                mKey7->SetLabel(thor::toString(event.key.code));
            } break;

            case 8:
            {
                Game::setActionKey("8",event.key.code);
                mKey8->SetLabel(thor::toString(event.key.code));
            } break;

            case 9:
            {
                Game::setActionKey("9",event.key.code);
                mKey9->SetLabel(thor::toString(event.key.code));
            } break;


            default: break;
        }
    }

    mDesktop.HandleEvent(event);
    return true;
}

bool SettingsState::update(sf::Time dt)
{
    mDesktop.Update(dt.asSeconds());
    return true;
}

void SettingsState::render(sf::RenderTarget& target, sf::RenderStates states)
{
    states.transform *= getTransform();
    target.draw(mBackground,states);
    mSfgui.Display(ah::Application::getWindow());
}

void SettingsState::onActivate()
{
}

void SettingsState::onDeactivate()
{
    ah::Application::getWindow().removeDebugInfo("VerticalSync");
}
