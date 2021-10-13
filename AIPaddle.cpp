#include <assert.h>

#include "AIPaddle.h"
#include "Game.h"
#include "GameBall.h"

AIPaddle::AIPaddle() :_velocity(0), _maxVelocity(10.0f) {
	Load("images/paddle.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2, GetSprite().getGlobalBounds().height / 2);
}

AIPaddle::~AIPaddle() {}

void AIPaddle::Draw(sf::RenderWindow& rw) {
	VisibleGameObject::Draw(rw);
}

float AIPaddle::GetVelocity() const {
	return _velocity;
}

void AIPaddle::Update(float elapsedTime) {
	const GameBall* gameBall = static_cast<GameBall*>(Game::GetGameObjectManager().Get("Ball"));
	sf::Vector2f ballPosition = gameBall->GetPosition();

	if (GetPosition().x - 20.0f < ballPosition.x)
		_velocity += 0.3f;
	else if (GetPosition().x + 20.0f > ballPosition.x)
		_velocity -= 0.3f;
	else
		_velocity = 0.0f;

	sf::Vector2f pos = this->GetPosition();

	if (pos.x < GetSprite().getGlobalBounds().width / 2 ||
		pos.x > Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width / 2) {
		_velocity = -_velocity;	//Bounce by current velocity on impact with wall
	}

	//GetSprite().move(_velocity * elapsedTime, 0);
	GetSprite().move(_velocity, 0);
}