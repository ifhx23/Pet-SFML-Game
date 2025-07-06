#pragma once
#include <SFML/Graphics.hpp>
#include "../World/World.h"
#include "../World/Player.h"
#include "../World/Enemy.h"
#include <iostream>
enum class TextureID
{
	PlayerBody,
	PlayerHead,
	Enemy,
	
};


class Game
{
	enum class GameState
	{
		Menu,
		Running,
		GameOver
	};
public:
	Game();

	void Run();
	void ProcessEvents();
	void Update(float deltaTime);
	void Render();
	void StartLevel();
	
private:

	bool LoadTexture(TextureID id, const std::string& filename) {
		if (textures.find(id) != textures.end())
			return true; // already loaded

		sf::Texture texture;
		if (!texture.loadFromFile(filename)) {
			std::cout << "Failed to load texture: " << filename << "\n";
			return false;
		}
		textures[id] = std::move(texture);
		return true;
	}

	sf::Texture& GetTexture(TextureID id) {
			return textures.at(id);
	}

	void LoadAllTextures() {
		
		LoadTexture(TextureID::Enemy, "../Assets/Enemy/Enemy.png");
		LoadTexture(TextureID::PlayerHead, "../Assets/Player/Head.png");
		LoadTexture(TextureID::PlayerBody, "../Assets/Player/Body.png");
		if (!font.openFromFile("Assets/Font/RobotoMono-VariableFont_wght.ttf")) {
			std::cout << "Failed to load font!\n";
		}
	}



	int level = 0;
	int score = 0;
	
	sf::Font font;
	sf::Text livesText;

	GameState gameState;

	sf::RenderWindow window;
	InputManeger input;
	World world;
	
	std::shared_ptr<Player> player;
	std::unordered_map<TextureID, sf::Texture> textures;
	
};

