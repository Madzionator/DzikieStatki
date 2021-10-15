#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 600), "SFML works!");
    sf::CircleShape shape(50.f);
    sf::RectangleShape miner(sf::Vector2f(10, 10));
    sf::Vector2f vec(50, 50);
    char direct = 0;
    float speed = 0.01;
    sf::Text speedTxt;
    speedTxt.setPosition(50, 550);
    speedTxt.setCharacterSize(24);
    speedTxt.setString("Speed 1");
    sf::Font font = sf::Font();
    if (!font.loadFromFile("arial.ttf")) {
        return 0;

    }
    speedTxt.setFont(font);
    speedTxt.setFillColor(sf::Color::Red);
    shape.setFillColor(sf::Color::Green);
    miner.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        window.clear();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        {
            speed = 0.01;
            speedTxt.setString("Speed 1");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        {
            speed = 0.05;
            speedTxt.setString("Speed 2");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        {
            speed = 0.1;
            speedTxt.setString("Speed 3");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        {
            speed = 0.5;
        	speedTxt.setString("Speed 4");
        }
        window.draw(speedTxt);
    	
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    	for(int i =0; i<5; i++)
            for (int j = 0; j < 5; j++)
            {
                shape.setPosition(i*100, j*100);
                window.draw(shape);
            }

        window.draw(miner);
        switch (direct)
        {
        case 0:
            vec.x += speed;
            if (vec.x > 450)
                direct++;
            break;
        case 1:
            vec.y += speed;
            if (vec.y > 450)
                direct++;
            break;
        case 2:
            vec.x -= speed;
            if (vec.x < 50)
                direct++;
            break;
        case 3:
            vec.y -= speed;
            if (vec.y < 50)
                direct = 0;
            break;
        }   
        miner.setPosition(vec);      
        window.display();
    }

    return 0;
}