#include <assert.h>
#include <SFML/System.hpp>

#include "PlayerPaddle.h"
#include "Game.h"
#include "ServiceLocator.h"

PlayerPaddle::PlayerPaddle() : _velocity(0), _maxVelocity(10.0f) {
	Load("images/paddle.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2, GetSprite().getGlobalBounds().height / 2);
}

PlayerPaddle::~PlayerPaddle() {}

void PlayerPaddle::Draw(sf::RenderWindow& rw) {
	VisibleGameObject::Draw(rw);
}

float PlayerPaddle::GetVelocity() const {
	return _velocity;
}

void PlayerPaddle::Update(float elapsedTime) {
	//Keyboard input for velocity
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		//std::cout << "Moving left" << std::endl;
		_velocity -= 0.3f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		//std::cout << "Moving right" << std::endl;
		_velocity += 0.30f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		//std::cout << "Moving cancel" << std::endl;
		_velocity = 0.0f;
	}

	//Make sure we aren't moving too fast
	if (_velocity > _maxVelocity)
		_velocity = _maxVelocity;
	if (_velocity < -_maxVelocity)
		_velocity = -_maxVelocity;

	//Move object
	sf::Vector2f pos = this->GetPosition();
	if (pos.x < GetSprite().getGlobalBounds().width / 2 ||
		pos.x > Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width / 2) {
		//Hit edge of screen. Bounce in opposite direction
		_velocity = -_velocity;
		//Play SFX
		ServiceLocator::GetAudio()->PlaySound("audio/bounce_player.wav");
	}

	//std::cout << "elapsed time: " << elapsedTime << " | velocity: " << _velocity << std::endl;
	GetSprite().move(_velocity, 0);

}