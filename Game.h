#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "SplashScreen.h"
#include "MainMenu.h"
#include "PlayerPaddle.h"
#include "GameObjectManager.h"
#include "GameBall.h"

class Game {
public:
	static void Start();

	static sf::RenderWindow& GetWindow();
	static sf::Time GetElapsedTime();
	static GameObjectManager& GetGameObjectManager();

	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;

private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();

	enum GameState {
		Uninitialized,
		ShowingSplash,
		Paused,
		ShowingMenu,
		Playing,
		Exiting
	};

	//sf::Clock _clock;

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	//static PlayerPaddle _player1;
	static GameObjectManager _gameObjectManager;
	static sf::Clock _clock;
};