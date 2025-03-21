#include "Game.h"

#include "State.h"
#include "StateIdentifiers.h"
#include "Settings.h"
#include "MenuState.h"
#include "GameState.h"
#include "SettingsState.h"

const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
    : mTextures()
    , mFonts()
    , mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
{
   
    sf::Vector2u res = Settings::getInstance().getCurrentResolution();

    if(Settings::getInstance().isFullscreen())
        mWindow.create(sf::VideoMode({res.x, res.y}), "SFML Window", sf::State::Fullscreen);
    else 
        mWindow.create(sf::VideoMode({res.x, res.y}), "SFML Window", sf::Style::Default);

    mFonts.open(Fonts::Main, "C:/Files/EvoGame/build/Debug/Media/Fonts/Sansation.ttf");

	mTextures.load(Textures::Tileset,     "C:/Files/EvoGame/build/Debug/Media/Textures/nature-paltformer.png");
	mTextures.load(Textures::TitleScreen, "C:/Files/EvoGame/build/Debug/Media/Textures/title-screen.png");

    registerStates();
	mStateStack.pushState(States::Menu);
}

void Game::run()
{ 
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    
    while(mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while(timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;

            handleInput();
            update(timePerFrame);

        }
        render();
    }
}

void Game::handleInput()
{
	while(const std::optional event = mWindow.pollEvent())
	{
        mStateStack.handleEvent(*event);
        if (event->is<sf::Event::Closed>() || mStateStack.isEmpty())
        {
            mWindow.close();
        }
    }
}

void Game::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Game::render()
{
    mWindow.clear(sf::Color::Black);
    mStateStack.draw();
    mWindow.display();
}

void Game::registerStates()
{
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<SettingsState>(States::Settings);
}
