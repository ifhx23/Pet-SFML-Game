#pragma once
#include "Game.h"
#include <random>
#include <iostream>

Game::Game():livesText(font)
{
	LoadAllTextures();
	livesText.setFont(font);
	livesText.setFillColor(sf::Color::White);
	livesText.setCharacterSize(24);
	livesText.setPosition({100,100});

	window.create(sf::VideoMode({ 1920, 1080 }), "Test");
	window.setFramerateLimit(60);
	input.bind(PlayerAction::MoveUp, sf::Keyboard::Scancode::W);

	input.bind(PlayerAction::MoveDown, sf::Keyboard::Scancode::S);

	input.bind(PlayerAction::MoveLeft, sf::Keyboard::Scancode::A);

	input.bind(PlayerAction::MoveRight, sf::Keyboard::Scancode::D);

	input.bind(PlayerAction::Shot, sf::Keyboard::Scancode::Space);
	gameState = Game::GameState::Menu;
}

void Game::ProcessEvents()
{
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
		if (event->is<sf::Event::KeyPressed>() && gameState == GameState::Menu)
		{
			Game::gameState = GameState::Running;
		}
		if (event->is<sf::Event::KeyPressed>() && gameState == GameState::GameOver)
		{
			Game::gameState = GameState::Menu;
		}

		input.handleEvent(*event);
	}

}

void Game::Update(float deltaTime)
{
	switch (gameState)
	{
	case Game::GameState::Menu:
		world.ResetWorld();
		if (player == nullptr)
		{
			player = std::make_shared<Player>(input, world,GetTexture(TextureID::PlayerHead),GetTexture(TextureID::PlayerBody));
			player->isEnable = false;
			
		}

		break;
	case Game::GameState::Running:




		if (player->isEnable)
		{

			if (world.GetEnemyCount() == 0)
			{
				level++;
				int enemyCount = 0;
				float enemySpeed = 0.0f;
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_real_distribution<> dist(0.0, window.getSize().x);

				switch (level)
				{
				case 1:
					enemyCount = 1;
					enemySpeed = 100.0f;
					break;
				case 2:
					enemyCount = 4;
					enemySpeed = 150.0f;
					break;
				case 3:
					enemyCount = 8;
					enemySpeed = 170.0f;
					break;
				case 4:
					enemyCount = 10;
					enemySpeed = 200.0f;
					break;

				default:
					enemyCount = 12;
					enemySpeed = 250.0f;

				}

				for (size_t i = 0; i < enemyCount; i++)
				{
					float num = dist(gen);
					std::shared_ptr<Enemy> e;
					do {
						num = dist(gen);

						e = std::make_shared<Enemy>
							(world,
								player,
								sf::Vector2f{ num,100 },
								enemySpeed,
								GetTexture(TextureID::Enemy));

					} while (world.IsEntityCollideWithOthers(e));

					world.AddEntity(std::move(e));

				}

			}
			livesText.setString("Lives: " + std::to_string(player->GetLives()));
		}
		else {
			player->isEnable = true;
			world.AddEntity(player);
		}

		if (player.get()->GetLives() == 0)
		{
			gameState = GameState::GameOver;
		}

		world.Update(deltaTime);
		break;

	case Game::GameState::GameOver:

		level = 0;
		player.reset();


		break;
	default:
		break;
	}



}

void Game::Render()
{
	window.clear(sf::Color(38, 69, 0));
	window.draw(world);
	window.draw(livesText);
	window.display();
}

void Game::StartLevel()
{

}

void Game::Run()
{

	sf::Clock deltaTime;

	while (window.isOpen())
	{
		ProcessEvents();
		Update(deltaTime.restart().asSeconds());
		Render();
	}
}

