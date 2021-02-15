#pragma once
#include "Player.h"
#include <SFML\Graphics\RectangleShape.hpp>
class Car
{
	public:
		Car(Player& player, sf::RectangleShape& carShape);
		void physicsUpdate(double frameDelta);
	private:
		Player& player;
		sf::RectangleShape& carShape;

		double position[2] = { 0, 0 };
		double angle = 0;

		double velocity[2] = { 0, 0 };
		double angularVelocity = 0;

		double drag = 0.999;
		double angularDrag = 0.75;
		
		double power = 1;
		double turnSpeed = 10;
};