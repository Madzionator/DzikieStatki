#include "Game.h"
#include "MenuGameMode.h"
#include "System.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);
GameMode* Game::mGameMode = nullptr;

Game::Game()
    : mWindow(sf::VideoMode(854, 480), "Statki")
{
    System::Window = &mWindow;
    SetGameMode(new MenuGameMode());
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
    mGameMode = gameMode;
}

void Game::ProcessEvents()
{
    sf::Event event{};

    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            mWindow.close();
            break;
        default:
            break;
        }

    }
}

void Game::Update(sf::Time deltaTime)
{
	mGameMode->update(deltaTime);
}

void Game::Render()
{
	mWindow.clear();

	mWindow.draw(*mGameMode);

	mWindow.display();
}