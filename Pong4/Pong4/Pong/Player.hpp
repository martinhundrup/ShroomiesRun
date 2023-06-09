#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <ctime>

class Player : public sf::RectangleShape
{
public:
	Player(sf::Vector2f& newSize, const sf::Vector2f& newPos)
	{
		this->setFillColor(sf::Color::White);
		this->setSize(newSize);
		this->setPosition(newPos);

		jumpFile.loadFromFile("jump.wav");
		jumpSFX.setBuffer(jumpFile);
	};

	double getVelocity(); 
	bool jumpActive();
	void updateMovement(bool &isTouchingGround);
private:
	double fallVelocity = 0;
	const double fallSpeed = 0.35;
	const double jumpSpeed = -8.5;
	clock_t jumpTime = NULL;
	const int maxJumpTime = 30;
	const int maxFallVelocity = 10;

	// jumping stuff
	bool hasJumped = false; // for making sure the sfx only plays once
	///jump file
	sf::SoundBuffer jumpFile;
	/// jump sound
	sf::Sound jumpSFX;
	

};