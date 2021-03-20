#include "Car.h"
#include <iostream>
#include "MoreMath.h"

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

void Car::physicsUpdate(double frameDelta)
{
	#pragma region Sync car angle and position
	this->position = carShape.getPosition();
	this->angle = carShape.getRotation() / -180 * 3.14159265358979323846;
	#pragma endregion

	#pragma region Interpret player controls
	this-> steer = this->player.right;

	double brake = std::min((this->player.forward < 0) * this->BRAKE_FORCE, this->player.stop * this->E_BRAKE_FORCE);
	double throttle = this->player.forward * this->ENGINE_FORCE;
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
	double yawSpeedFront = this->CG_TO_FRONT_AXLE * this->angularVelocity;
	double yawSpeedBack = -this->CG_TO_BACK_AXLE * this->angularVelocity;
	#pragma endregion

	#pragma region Slip angles
	double slipAngleFront = atan2(this->velocityLocal.y + yawSpeedFront,
		abs(this->velocityLocal.x) - MoreMath::sign(this->velocityLocal.x) * this->steer);
	double slipAngleBack = atan2(this->velocityLocal.y + yawSpeedBack,
		abs(this->velocityLocal.x));

	double tyreGripFront = this->TYPE_GRIP;
	double tyreGripBack = this->TYPE_GRIP * (1.f - this->player.stop * (1.f - this->LOCK_GRIP));
	
	double firctionFront = MoreMath::clamp(-this->CORNER_STIFFNESS_FRONT * slipAngleFront, -tyreGripFront, tyreGripFront) * frontWeight;
	double firctionBack = MoreMath::clamp(-this->CORNER_STIFFNESS_FRONT * slipAngleFront, -tyreGripBack, tyreGripBack) * backWeight;
	#pragma endregion

	#pragma region Resulting force (local)
	sf::Vector2f tractrionForce_l = sf::Vector2f(
		throttle - brake * MoreMath::sign(this->velocityLocal.x),
		0);
	sf::Vector2f dragForce_l = sf::Vector2f(
		-this->ROLL_RESISTANCE * this->velocityLocal.x - this->AIR_RESISTANCE * this->velocityLocal.x * abs(this->velocityLocal.x),
		-this->ROLL_RESISTANCE * this->velocityLocal.y - this->AIR_RESISTANCE * this->velocityLocal.y * abs(this->velocityLocal.x));
	#pragma endregion

	#pragma region Total force
	sf::Vector2f totalForce_l = sf::Vector2f(
		dragForce_l.x + tractrionForce_l.x,
		dragForce_l.y + tractrionForce_l.y + cos(steer) * firctionFront + firctionBack);
	#pragma endregion

	#pragma region Acceleration
	this->accelerationLocal = sf::Vector2f(
		totalForce_l.x - sinAngle * this->MASS,
		totalForce_l.y + cosAngle * this->MASS);

	this->acceleration = sf::Vector2f(
		cosAngle * this->accelerationLocal.x - sinAngle * this->accelerationLocal.y,
		sinAngle * this->accelerationLocal.x + cosAngle * this->accelerationLocal.y);
	#pragma endregion


	#pragma region Apply position
	carShape.setPosition(this->position);
	#pragma endregion
	
	#pragma region Apply rotation
	// TODO
	#pragma endregion
}

