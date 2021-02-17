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

		sf::Vector2f position = sf::Vector2f(0, 0);
		sf::Vector2f velocity = sf::Vector2f(0, 0);
		double angle = 0;

		double engineForceFWD = 500000;
		double engineForceBWD = 200000;
		double mass = 1439;
		double cdrag = 0.29;
		double croll = 12.8;
		double cbreak = 400000;
};