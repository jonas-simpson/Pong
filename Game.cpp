#include "Game.h"
#include "SFMLSoundProvider.h"
#include "ServiceLocator.h"
#include "AIPaddle.h"


void Game::Start() {
	//Only execute code once
	if (_gameState != Uninitialized) {
		std::cout << "Game already initialized. Aborting..." << std::endl;
		return;
	}

	std::cout << "Above Window" << std::endl;
	_mainWindow.create(sf::VideoMode(1024, 768, 32), "PONG");
	_mainWindow.setFramerateLimit(60);
	std::cout << "Below window" << std::endl;

	SFMLSoundProvider soundProvider;
	ServiceLocator::RegisterServiceLocator(&soundProvider);

	ServiceLocator::GetAudio()->PlaySong("audio/Intergalactic Odyssey.ogg", true);

	//Load player
	PlayerPaddle* player1 = new PlayerPaddle();
	player1->SetPosition((SCREEN_WIDTH/2), (SCREEN_HEIGHT/2)+250);
	_gameObjectManager.Add("Paddle1", player1);

	//Load AI
	AIPaddle* player2 = new AIPaddle();
	player2->SetPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - 250);
	_gameObjectManager.Add("Paddle2", player2);

	//Load ball
	GameBall* ball = new GameBall();
	ball->SetPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - 15);
	_gameObjectManager.Add("Ball", ball);

	_gameState = Game::ShowingSplash;

	std::cout << "Entering game loop" << std::endl;
	while (!IsExiting()) {
		GameLoop();
	}

	std::cout << "Exiting game. Goodbye!" << std::endl;
	_mainWindow.close();
}

sf::Time Game::GetElapsedTime() {
	return _clock.getElapsedTime();
}

sf::RenderWindow& Game::GetWindow() {
	return _mainWindow;
}

GameObjectManager& Game::GetGameObjectManager() {
	return _gameObjectManager;
}

bool Game::IsExiting() {
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop() {
	_clock.restart();
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);

	switch (_gameState) {
		case Game::ShowingMenu:
			ShowMenu();
			break;
		case Game::ShowingSplash:
			ShowSplashScreen();
			break;
		case Game::Playing:
			_mainWindow.clear(sf::Color::Black);
			_gameObjectManager.UpdateAll();
			_gameObjectManager.DrawAll(_mainWindow);
			_mainWindow.display();

			if (currentEvent.type == sf::Event::Closed)
				_gameState = Game::Exiting;
			if (currentEvent.type == sf::Event::KeyPressed) {
				if (currentEvent.key.code == sf::Keyboard::Key::Escape)
					ShowMenu();
			}
			break;
	}
}

void Game::ShowSplashScreen() {
	std::cout << "Entering splash screen" << std::endl;
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu() {
	std::cout << "Entering main menu" << std::endl;
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch (result) {
		case MainMenu::Exit:
			std::cout << "Exiting game" << std::endl;
			_gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			std::cout << "Entering play area" << std::endl;
			_gameState = Game::Playing;
			break;
	}
}

//Instantiate static member variables without constructor
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
sf::Clock Game::_clock;