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
	//this->player = player;
	//this->carShape = carShape;
	this->position = carShape.getPosition();
	this->angle = carShape.getRotation() / -180 * 3.14159265358979323846;
	std::cout << this->HALF_WIDTH;
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
	/*
	double currentEngineForce;
	if (player.forward == 1)
		currentEngineForce = engineForceFWD;
	else if (player.forward == -1)
		currentEngineForce = -engineForceBWD;
	else
		currentEngineForce = 0;
		*/
	#pragma endregion

	#pragma region Moving in a straight line

	#pragma endregion


	#pragma region Apply position
	carShape.setPosition(this->position);
	#pragma endregion
	
	#pragma region Apply rotation
	// TODO
	#pragma endregion
}