#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h";
#include "Car.h";

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Top down racer", sf::Style::Close);
    sf::Clock deltaClock;

    sf::RectangleShape carShape(sf::Vector2f(50,100));
    carShape.setFillColor(sf::Color::Red);
    carShape.setOrigin(25, 50);
    carShape.setPosition(800, 450);

    Player player;
    Car car(player, carShape);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Key pressed
            if (event.type == sf::Event::KeyPressed)
                player.keyEvent(event.key.code, true);
            // Key released
            if (event.type == sf::Event::KeyReleased)
                player.keyEvent(event.key.code, false);
            // Close window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        sf::Time deltaTime = deltaClock.restart();
        car.physicsUpdate(deltaTime.asSeconds());
        
        window.clear();
        window.draw(carShape);
        window.display();
    }

    return 0;
}