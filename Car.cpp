#include "Car.h"
#include <iostream>

/// <summary>
/// Initialize the car object
/// </summary>
/// <param name="player">The player that will control the car</param>
/// <param name="carShape">The rectangle that represents the car</param>
/// <returns></returns>
Car::Car(Player& player, sf::RectangleShape& carShape) : carShape(carShape), player(player)
{
	this->player = player;
	this->carShape = carShape;
	this->position = carShape.getPosition();
	this->angle = carShape.getRotation() / -180 * 3.14159265358979323846;
}

/// <summary>
/// Update car physics. This will update the car's location and rotation using the player's controls
/// </summary>
/// <param name="frameDelta">The time difference in between the frames. It is used to untie the physics from the framerate</param>
void Car::physicsUpdate(double frameDelta)
{
	#pragma region Sync car angle and position
	this->position = carShape.getPosition();
	this->angle = carShape.getRotation() / -180 * 3.14159265358979323846;
	#pragma endregion

	#pragma region Interpret player controls
	double currentEngineForce;
	if (player.forward == 1)
		currentEngineForce = engineForceFWD;
	else if (player.forward == -1)
		currentEngineForce = -engineForceBWD;
	else
		currentEngineForce = 0;
	#pragma endregion

	#pragma region Forces that affect the car moving in a straight line
	// Create useful variables for calculating forces
	double speed = sqrt(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y);
	sf::Vector2f forwardVector(cos(this->angle), sin(this->angle));
	sf::Vector2f speedForwardVector(speed == 0 ? 0 : velocity.x / speed, speed == 0 ? 0 : velocity.y / speed);

	// Drag
	sf::Vector2f fdrag(-this->cdrag * this->velocity.x * speed, -this->cdrag * this->velocity.y * speed);

	// Roll
	sf::Vector2f froll(this->croll * this->velocity.x, this->croll * this->velocity.y);

	// Traction
	sf::Vector2f ftraction;
	// Can be breaking force if the player is breaking
	if (this->player.stop && speed > 0.25)
		ftraction = sf::Vector2f(-speedForwardVector.x * this->cbreak, -speedForwardVector.y * this->cbreak);
	else
		ftraction = sf::Vector2f(currentEngineForce * forwardVector.x, currentEngineForce * forwardVector.y);

	// The sum of these forces
	sf::Vector2f flong = ftraction + fdrag + froll;

	// Acceleration from the sum
	sf::Vector2f acceleration = sf::Vector2f(flong.x / this->mass, flong.y / this->mass);

	// Velocity from acceleration
	this->velocity.x = this->velocity.x + frameDelta * acceleration.x;
	this->velocity.y = this->velocity.y + frameDelta * acceleration.y;

	// Position from velocity
	this->position.x = this->position.x + frameDelta * this->velocity.x;
	this->position.y = this->position.y + frameDelta * this->velocity.y;
	#pragma endregion

	#pragma region Apply position
	carShape.setPosition(this->position);
	#pragma endregion
	
	#pragma region Apply rotation
	// TODO
	#pragma endregion
}