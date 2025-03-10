#include "Game.h"

#include "State.h"
#include "StateIdentifiers.h"
#include "Settings.h"
#include <iostream> 

const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);
const int mapWidth = Settings::getInstance().getWidth();
const int mapHeight = Settings::getInstance().getHeight();

Game::Game()
    : mWindow(sf::VideoMode(sf::Vector2u(mapWidth, mapHeight)), "MyProject", sf::Style::Close | sf::Style::Resize)
    , mTextures()
    , mFonts()
    , mStateStack(State::Context(mWindow, mTextures, mFonts))
{
    mFonts.open(Fonts::Main, "/home/miha/MyNewPetProject/build/Media/Fonts/Sansation.ttf");

    std::cout << mapWidth << ", " << mapHeight << std::endl;

	mTextures.load(Textures::Tileset,     "/home/miha/MyNewPetProject/build/Media/Textures/nature-paltformer.png");
	mTextures.load(Textures::TitleScreen, "/home/miha/MyNewPetProject/build/Media/Textures/title-screen.png");
    
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
