#include <assert.h>
#include <random>

#include "GameBall.h"
#include "Game.h"
#include "ServiceLocator.h"

GameBall::GameBall() {
	Load("images/ball.png");
	assert(IsLoaded());

	GetSprite().setOrigin(15, 15);

	srand(time(NULL));
	_angle = (float)(rand() % 360);

	_elapsedTimeSinceStart = 0.0f;
	_velocity = _VELOCITY_START;
}

GameBall::~GameBall() {}

const float GameBall::_VELOCITY_START = 3.0f;
const float GameBall::_VELOCITY_INCREMENT = 0.25f;

void GameBall::Update(float elapsedTime) {
	_elapsedTimeSinceStart += elapsedTime*100.0f;

	//Delay game from starting until 3 seconds have passed
	if (_elapsedTimeSinceStart < 3.0f) {
		//std::cout << "Frame time " << elapsedTime << std::endl;
		std::cout << "Waiting... Current time: " << _elapsedTimeSinceStart << std::endl;
		return;
	}
	//std::cout << "Ball moving!" << std::endl;

	//float moveAmount = _velocity * elapsedTime * 10.0f;
	float moveAmount = _velocity;

	float moveByX = LinearVelocityX(_angle) * moveAmount;
	float moveByY = LinearVelocityY(_angle) * moveAmount;

	//Collide with the left or right side of the screen
	if (GetPosition().x + moveByX <= 0 + GetWidth() / 2 ||
		GetPosition().x + GetWidth() / 2 + moveByX >= Game::SCREEN_WIDTH) {

		//Play SFX
		ServiceLocator::GetAudio()->PlaySound("audio/bounce_wall.wav");

		//Ricochet!
		_angle = 360.f - _angle;

		//Don't let angle get too close to 90 degrees
		if (_angle > 260.0f && _angle < 280.0f)
			_angle += 20.0f;
		if (_angle > 80.0f && _angle < 100.0f)
			_angle += 20.0f;
		moveByX = -moveByX;
	}

	PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1"));
	if (player1 != nullptr) {
		sf::FloatRect p1BB = player1->GetBoundingRect();

		if (p1BB.intersects(GetBoundingRect())) {
			//Colliding with paddle
			_angle = 360.0f - (_angle - 180.0f);
			if (_angle > 360.0f)
				_angle -= 360.0f;

			//Reverse y velocity
			moveByY = -moveByY;

			//Increase speed
			_velocity += _VELOCITY_INCREMENT;

			//Play sound effect
			ServiceLocator::GetAudio()->PlaySound("audio/bounce_paddle.wav");

			//Make sure ball isn't inside paddle
			if (GetBoundingRect().top + GetBoundingRect().height > player1->GetBoundingRect().top) {
				SetPosition(GetPosition().x, player1->GetBoundingRect().top - GetWidth() / 2 - 1);
			}

			//Now change angle based on player velocity
			float playerVelocity = player1->GetVelocity();

			if (playerVelocity < 0) {
				//Player moving left
				_angle -= 20.0f;
				if (_angle < 0)
					_angle = 360.0f - _angle;
			}
			else if (playerVelocity > 0) {
				//Player moving right
				_angle += 20.0f;
				if (_angle > 360.0f) _angle = _angle - 360.0f;
			}
		}

		//Collision with top of screen
		if (GetPosition().y - GetHeight() / 2 <= 0) {
			//Play SFX
			ServiceLocator::GetAudio()->PlaySound("audio/bounce_wall.wav");

			_angle = 180 - _angle;
			moveByY = -moveByY;
		}

		if (GetPosition().y + GetHeight() / 2 + moveByY >= Game::SCREEN_HEIGHT) {
			//Player missed the ball
			//TEMP - move to middle of screen and randomize angle
			// 
			//Play SFX
			ServiceLocator::GetAudio()->PlaySound("audio/bounce_floor.wav");

			GetSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
			srand(time(NULL));
			_angle = (float)(rand() % 360);
			/*_velocity = 3.0f;*/
			_elapsedTimeSinceStart = 0.0f;
			_velocity = _VELOCITY_START;
		}

		GetSprite().move(moveByX, moveByY);
	}
}

float GameBall::LinearVelocityX(float angle) {
	angle -= 90.0f;
	if (angle < 0)
		angle = 360.0f + angle;

	return (float)std::cos(angle * (std::_Pi / 180.0f));
}

float GameBall::LinearVelocityY(float angle) {
	angle -= 90.0f;
	if (angle < 0)
		angle = 360 + angle;

	return (float)std::sin(angle * (std::_Pi / 180.0f));
}