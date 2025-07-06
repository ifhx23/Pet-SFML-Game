#pragma once
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>
#include <functional>
#include <SFML/Window/Event.hpp>
#include "../World/World.h"

enum class PlayerAction {
	MoveUp,
	MoveDown,
	MoveLeft,
	MoveRight,
	Shot
};
class InputManeger {

public:
	InputManeger();
	void handleEvent(const sf::Event& event);
	void bind(PlayerAction action, sf::Keyboard::Scancode key,
		const std::function<void()>& onPressed=nullptr,
		const std::function<void()>& onReleased = nullptr);

	bool isKeyHeld(PlayerAction action) const {
		auto itKey = keyMap.find(action);
		if (itKey == keyMap.end()) return false;

		auto itState = keyStates.find(itKey->second);
		if (itState == keyStates.end()) return false;

		return itState->second;
	}
	sf::Vector2f mousePosition;
private:
	struct ActionCallbacks {
		std::function<void()> onPressed;
		std::function<void()> onReleased;
	};


	
	//std::unordered_map<PlayerAction, ActionCallbacks> actionCallbacks;
	std::unordered_map<PlayerAction, sf::Keyboard::Scancode> keyMap;
	std::unordered_map<sf::Keyboard::Scancode, bool> keyStates;
};