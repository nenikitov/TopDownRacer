#pragma once
#include <SFML\Window\Event.hpp>
class Player
{
	public:
		// Movement directions (can be -1, 0,  and 1)
		int forward = 0;
		int right = 0;
		bool stop = false;
		void keyEvent(sf::Keyboard::Key key, bool pressed);
	private:
		bool controlKeysPressed[5] = {false, false, false, false, false}; // Forward, Backward, Left, Right, Break
		void updateMovementDirections();
};