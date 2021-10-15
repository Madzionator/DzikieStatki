#include "Game.h"

#include "MenuGameMode.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
    : mWindow(sf::VideoMode(640, 480), "Statki")
{
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
        case sf::Event::KeyPressed:
            //handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            //handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::MouseButtonReleased:
            //handlePlayerMouseClick(event.mo)
            break;
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
    // TODO: Update your objects here
    // Example: mWindow.draw(mPlayer);
}

void Game::Render()
{
    mWindow.clear();

    // TODO: Draw your objects here

    mWindow.display();
}