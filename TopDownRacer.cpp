#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h";
#include "Car.h";

int main()
{
    // Create a window that can't be resized
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Top down racer", sf::Style::Close);
    // Create Delta clock for counting frame delta to untie physics from framerate
    sf::Clock deltaClock;

    #pragma region Initialize the car shape
    sf::RectangleShape carShape(sf::Vector2f(25,50));
    carShape.setFillColor(sf::Color::Red);
    carShape.setOrigin(carShape.getSize().x / 2, carShape.getSize().y / 2);
    carShape.setPosition(800, 450);
    carShape.setRotation(45);
    #pragma endregion

    // Create the player
    Player player;
    // Initialize the car
    Car car(player, carShape);

    #pragma region Each frame when the window is open
    while (window.isOpen())
    {
        // Create an event
        sf::Event event;
        // Get an event from the queue of current events
        while (window.pollEvent(event))
        {
            // If a key is pressed
            if (event.type == sf::Event::KeyPressed)
                player.keyEvent(event.key.code, true);
            // If a key is released
            if (event.type == sf::Event::KeyReleased)
                player.keyEvent(event.key.code, false);
            // If the window is closed
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Get the time between the frames
        sf::Time deltaTime = deltaClock.restart();

        // Update the car physics
        car.physicsUpdate(deltaTime.asSeconds());
        
        #pragma region Rendering
        window.clear();
        window.draw(carShape);
        window.display();
        #pragma endregion
    }
    #pragma endregion

    // End of the program
    return 0;
}