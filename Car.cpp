#include "Car.h"
#include <iostream>

Car::Car(Player& player, sf::RectangleShape& carShape) : carShape(carShape), player(player)
{
	this->player = player;
	this->carShape = carShape;
	this->position = carShape.getPosition();
	this->angle = carShape.getRotation() / -180 * 3.14159265358979323846;
}

void Car::physicsUpdate(double frameDelta)
{
	// Position and rotation sync
	this->position = carShape.getPosition();
	this->angle = carShape.getRotation() / -180 * 3.14159265358979323846;

	// Current engine force is calculated from player controls and engine force
	double currentEngineForce = player.forward * (player.forward > 0 ? engineForceFWD : engineForceBWD);

	// Create useful variables for calculating forces
	double speed = sqrt(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y);
	sf::Vector2f forwardVector(cos(this->angle), sin(this->angle));
	sf::Vector2f speedForwardVector(speed == 0 ? 0 : velocity.x / speed, speed == 0 ? 0 : velocity.y / speed);

	// Calculate all the forces that affect the car moving in a straight line
	sf::Vector2f ftraction;
	sf::Vector2f fdrag(-this->cdrag * this->velocity.x * speed, -this->cdrag * this->velocity.y * speed);
	sf::Vector2f froll(this->croll * this->velocity.x, this->croll * this->velocity.y);
	// Traction can be breaking force when the player is breaking or it can be traction force when the player is moving
	if (this->player.stop && speed > 0.25)
		ftraction = sf::Vector2f(-speedForwardVector.x * this->cbreak, -speedForwardVector.y * this->cbreak);
	else
		ftraction = sf::Vector2f(currentEngineForce * forwardVector.x, currentEngineForce * forwardVector.y);
	sf::Vector2f flong = ftraction + fdrag + froll;

	// Apply forces to position
	sf::Vector2f acceleration = sf::Vector2f(flong.x / this->mass, flong.y / this->mass);

	this->velocity.x = this->velocity.x + frameDelta * acceleration.x;
	this->velocity.y = this->velocity.y + frameDelta * acceleration.y;

	this->position.x = this->position.x + frameDelta * this->velocity.x;
	this->position.y = this->position.y + frameDelta * this->velocity.y;

	// Apply final position
	carShape.setPosition(this->position);
}