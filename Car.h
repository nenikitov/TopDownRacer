#pragma once
#include "Player.h"
#include <SFML\Graphics\RectangleShape.hpp>

class Car
{
	public:
		/// <summary>
		/// Initialize new car object
		/// </summary>
		/// <param name="player">The reference to the player that will control the car</param>
		/// <param name="carShape">The reference to the rectangle shape that represents the car</param>
		/// <returns>Initialized car</returns>
		Car(Player& player, sf::RectangleShape& carShape);
		/// <summary>
		/// Take player controls, update the car physics and move the shape
		/// </summary>
		/// <param name="frameDelta">The difference between frames (in seconds) so the physics are untied from the framerate</param>
		void physicsUpdate(double frameDelta);
	private:
		// References
		/// <summary>
		/// The reference to the player
		/// </summary>
		Player& player;
		/// <summary>
		/// The reference to the rendered object
		/// </summary>
		sf::RectangleShape& carShape;

		// Variables that will be updated each tick during phisics simulation
		/// <summary>
		/// The angle of the car in radians
		/// </summary>
		double angle = 0;
		/// <summary>
		/// The position of the car in world space
		/// </summary>
		sf::Vector2f position = sf::Vector2f(0, 0);
		/// <summary>
		/// The velocity of the car in the world space
		/// </summary>
		sf::Vector2f velocity = sf::Vector2f(0, 0);
		/// <summary>
		/// Velocity of the car in local space
		/// </summary>
		sf::Vector2f velocityLocal = sf::Vector2f(0, 0);
		/// <summary>
		/// Acceleration of the car in the world space
		/// </summary>
		sf::Vector2f acceleration = sf::Vector2f(0, 0);
		/// <summary>
		/// Acceleration of the car in the local space
		/// </summary>
		sf::Vector2f accelerationLocal = sf::Vector2f(0, 0);
		/// <summary>
		/// The scalar that represents the velocity
		/// </summary>
		double velocityScalar = 0;
		/// <summary>
		/// The velocity of the rotation of the car in radians
		/// </summary>
		double angularVelocity = 0;
		/// <summary>
		/// The steer of the wheels in radians
		/// </summary>
		double steer = 0;

		// Car parameters
		const double GRAVITY = 9.81;
		const double MASS = 1400;
		const double INERTIA = 1;
		const double HALF_WIDTH = carShape.getSize().x / 2;
		const double CG_TO_FRONT = carShape.getSize().y / 1.8;
		const double CG_TO_BACK = CG_TO_FRONT;
		const double CG_TO_FRONT_AXLE = carShape.getSize().y / 1.5;
		const double CG_TO_BACK_AXLE = carShape.getSize().y / 1.5;
		const double CG_HEIGHT = 10;
		const double WHEEL_RADIUS = 5;
		const double TYPE_GRIP = 1.5;
		const double LOCK_GRIP = 0.7;
		const double ENGINE_FORCE = 8000;
		const double BRAKE_FORCE = 12000;
		const double E_BRAKE_FORCE = BRAKE_FORCE / 2.5;
		const double WEIGHT_TRANSFER_VALUE = 0.3;
		const double MAX_STEER = 0.5;
		const double CORNER_STIFFNESS_FRONT = 5;
		const double CORNER_STIFFNESS_BACK = 5;
		const double AIR_RESISTANCE = 2.5;
		const double ROLL_RESISTANCE = 8;
};