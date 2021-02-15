#include "Car.h"
#include <iostream>

Car::Car(Player& player, sf::RectangleShape& carShape) : carShape(carShape), player(player)
{
	this->player = player;
	this->carShape = carShape;
	this->position[0] = carShape.getPosition().x;
	this->position[1] = carShape.getPosition().y;
}

void Car::physicsUpdate(double frameDelta)
{
	this->angularVelocity += this->player.right * frameDelta;
	this->velocity[0] += sin(angle) * this->power * this->player.forward * frameDelta;
	this->velocity[1] += cos(angle) * this->power * this->player.forward * frameDelta;


	this->position[0] += this->velocity[0];
	this->position[1] += this->velocity[1];

	this->velocity[0] *= this->drag;
	this->velocity[1] *= this->drag;

	this->angle += this->angularVelocity;

	this->angularVelocity *= this->angularDrag;
	

	this->carShape.setPosition(this->position[0], this->position[1]);
	this->carShape.setRotation(this->angle * -180 / 3.14159265358979323846);

	//std::cout << player.forward << " " << player.right << std::endl;
}