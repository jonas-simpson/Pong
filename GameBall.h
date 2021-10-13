#pragma once

#include "VisibleGameObject.h"

class GameBall : public VisibleGameObject {
public:
	GameBall();
	virtual ~GameBall();
	void Update(float);

private:
	float _velocity;
	float _angle;
	float _elapsedTimeSinceStart;

	const static float _VELOCITY_START;
	const static float _VELOCITY_INCREMENT;

	float LinearVelocityX(float angle);
	float LinearVelocityY(float angle);
};