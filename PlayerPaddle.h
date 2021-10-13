#pragma once

#include "VisibleGameObject.h"

class PlayerPaddle : public VisibleGameObject {	//Only derive public members from inherited class
public:
	PlayerPaddle();
	~PlayerPaddle();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);

	float GetVelocity() const;
	
private:
	float _velocity;	//left is negative, right is positive
	float _maxVelocity;
};