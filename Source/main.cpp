#include "Application/Application.hpp"
#include "States/States.hpp"
#include "Game.hpp"

int main()
{
    ah::Application::getResources().loadImage("icon","Assets/Textures/icon.png");

    ah::Application::getResources().loadTexture("bg","Assets/Textures/back.png");
    ah::Application::getResources().loadTexture("bgmenu","Assets/Textures/bgmenu.png");
    ah::Application::getResources().loadTexture("cursor","Assets/Textures/cursor.png");
    ah::Application::getResources().loadTexture("sfml","Assets/Textures/sfml.png");
    ah::Application::getResources().loadTexture("ld34","Assets/Textures/ld34.png");
    ah::Application::getResources().loadTexture("tileset","Assets/Textures/tileset.png");
    ah::Application::getResources().loadTexture("turrets","Assets/Textures/turrets.png");
    ah::Application::getResources().loadTexture("zombies","Assets/Textures/zombies.png");
    ah::Application::getResources().loadTexture("hud","Assets/Textures/hud.png");

    ah::Application::getResources().getTexture("bg").setSmooth(true);
    ah::Application::getResources().getTexture("bgmenu").setSmooth(true);
    ah::Application::getResources().getTexture("cursor").setSmooth(true);
    ah::Application::getResources().getTexture("sfml").setSmooth(true);
    ah::Application::getResources().getTexture("ld34").setSmooth(true);
    ah::Application::getResources().getTexture("tileset").setSmooth(true);
    ah::Application::getResources().getTexture("turrets").setSmooth(true);
    ah::Application::getResources().getTexture("zombies").setSmooth(true);
    ah::Application::getResources().getTexture("hud").setSmooth(true);

    ah::Application::getResources().loadFont("cool","Assets/Fonts/coolveticca.ttf");
    ah::Application::getResources().loadFont("atmog","Assets/Fonts/atmogFont.ttf");

    ah::Application::getResources().loadSoundBuffer("Plant","Assets/Sounds/Plant.wav");
    ah::Application::getResources().loadSoundBuffer("Collect","Assets/Sounds/Recolt.wav");
    ah::Application::getResources().loadSoundBuffer("Turret","Assets/Sounds/Turret.wav");
    ah::Application::getResources().loadSoundBuffer("Unlock","Assets/Sounds/Unlock.wav");
    ah::Application::getResources().loadSoundBuffer("Shoot","Assets/Sounds/Shoot.wav");
    ah::Application::getResources().loadSoundBuffer("Select","Assets/Sounds/Select.wav");

    ah::Application::getAudio().registerMusicFile("Game","Assets/Musics/Game.ogg");
    ah::Application::getAudio().registerMusicFile("Menu","Assets/Musics/Menu.ogg");

    ah::Application::getWindow().setTitle(Game::getTitle());
    ah::Application::getWindow().create();
    ah::Application::getWindow().setIcon(&ah::Application::getResources().getImage("icon"));
    ah::Application::getWindow().setDebugInfoFont(&ah::Application::getResources().getFont("cool"));
    ah::Application::getWindow().showDebugInfo(false);

    ah::Application::getStates().registerState<IntroState>();
    ah::Application::getStates().registerState<MenuState>();
    ah::Application::getStates().registerState<PreGameState>();
    ah::Application::getStates().registerState<GameState>();
    ah::Application::getStates().registerState<EndGameState>();
    ah::Application::getStates().registerState<SettingsState>();

    ah::Application::getStates().pushState<IntroState>();

    ah::Application::run();

    return 0;
}
