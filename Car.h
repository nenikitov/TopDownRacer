#pragma once
#include "Player.h"
class Car
{
	public:
		Car(Player player);
	private:
		Player player;
		double speed = 10;
		double acceleration;

};