#include "Player.h"
#include <iostream>

/// <summary>
/// Gets the key that was pressed/releases and updates the movement direction
/// </summary>
/// <param name="key">The key that was pressed/released</param>
/// <param name="pressed">If the key was pressed (true) or released (false)</param>
void Player::keyEvent(sf::Keyboard::Key key, bool pressed)
{
	if (key == sf::Keyboard::W)
		this->controlKeysPressed[0] = pressed;
	if (key == sf::Keyboard::S)
		this->controlKeysPressed[1] = pressed;
	if (key == sf::Keyboard::A)
		this->controlKeysPressed[2] = pressed;
	if (key == sf::Keyboard::D)
		this->controlKeysPressed[3] = pressed;
	if (key == sf::Keyboard::Space)
		this->controlKeysPressed[4] = pressed;

	updateMovementDirections();
}

/// <summary>
/// Updates the movement direction variables using the array of movement keys pressed
/// </summary>
void Player::updateMovementDirections()
{
	this->forward = this->controlKeysPressed[0] - this->controlKeysPressed[1]; // 1 - Forward, 0 - Neutral, -1 - Backward 
	this->right = this->controlKeysPressed[3] - this->controlKeysPressed[2]; // 1 - Right, 0 - Neutral, -1 - Left
	this->stop = this->controlKeysPressed[4];
}
