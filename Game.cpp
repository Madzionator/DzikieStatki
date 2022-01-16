#include "Game.h"
#include "MenuGameMode.h"
#include "System.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);
GameMode* Game::currentGameMode = nullptr;
GameMode* Game::nextGameMode = nullptr;

Game::Game() //854x480 16:9
    : mWindow(sf::VideoMode(854, 480), "Dzikie Statki")
{
    System::Window = &mWindow;
    currentGameMode = new MenuGameMode();
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            ProcessEvents();
            Update(TimePerFrame);
        }
        Render();
    }
}

void Game::SetGameMode(GameMode* gameMode)
{
    if(gameMode != nextGameMode)
		delete nextGameMode;
    nextGameMode = gameMode;
}

void Game::ProcessEvents()
{
    sf::Event event{};
    while (mWindow.pollEvent(event))
	    if(event.type == sf::Event::Closed)
		    mWindow.close();
}

void Game::Update(sf::Time deltaTime)
{
	currentGameMode->update(deltaTime);
    if (nextGameMode != nullptr)
    {
        if(nextGameMode != currentGameMode)
            delete currentGameMode;
        currentGameMode = nextGameMode;
        nextGameMode = nullptr;
    }
}

void Game::Render()
{
    mWindow.clear();
    mWindow.draw(*currentGameMode);
    mWindow.display();
}