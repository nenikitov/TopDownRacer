#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h";
#include "Car.h";

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Top down racer", sf::Style::Close);
    Player player;
    Car car(player);

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

        window.clear();
        window.display();
    }

    return 0;
}