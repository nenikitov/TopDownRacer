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

	this->inertia = this->MASS * this->INERTIA_MULTIPLIER;
	this->wheelBase = this->CG_TO_FRONT_AXLE + this->CG_TO_BACK_AXLE;
	this->weightRatioFront = this->CG_TO_BACK_AXLE / this->wheelBase;
	this->weightRatioBack = this->CG_TO_FRONT_AXLE / this->wheelBase;
}

/// <summary>
/// Returns the sign of a number (-1, 1 or 0)
/// </summary>
/// <param name="value">Number to get the sign of</param>
/// <returns></returns>
int Car::sign(double value)
{
	return (value > 0) - (value < 0);
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
	double controllerSteer = this->player.right;
			
	#pragma endregion

	#pragma region Pre calculate values
	double sinAngle = sin(angle);
	double cosAngle = cos(angle);

	this->velocityLocal.x = cosAngle * this->velocity.x + sinAngle * this->velocity.y;
	this->velocityLocal.y = cosAngle * this->velocity.y - sinAngle * this->velocity.x;
	#pragma endregion

	#pragma region Weigth
	double frontWeight = this->MASS * (this->weightRatioFront * this->GRAVITY
		- this->WEIGHT_TRANSFER_VALUE * this->accelerationLocal.x * this->CG_HEIGHT / this->wheelBase);
	double backWeight = this->MASS * (this->weightRatioBack * this->GRAVITY
		+ this->WEIGHT_TRANSFER_VALUE * this->accelerationLocal.x * this->CG_HEIGHT / this->wheelBase);
	#pragma endregion

	#pragma region Yaw speed
	double yawSpeedFront = this->CG_TO_FRONT_AXLE * controllerSteer;
	double yawSpeedBack = this->CG_TO_BACK_AXLE * controllerSteer;
	#pragma endregion

	#pragma region Slip angles
	double slipAngleFront = atan2(this->velocityLocal.y + yawSpeedFront,
		abs(this->velocityLocal.x) - sign(this->velocityLocal.x) * this->steer);
	double slipAngleBack = atan2(this->velocityLocal.y + yawSpeedBack,
		abs(this->velocityLocal.x));

	double tyreGripFront = this->TYPE_GRIP;
	double tyreGripBack = this->TYPE_GRIP * (1.f - this->player.stop * (1.f - this->LOCK_GRIP));
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

