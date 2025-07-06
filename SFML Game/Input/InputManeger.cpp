	#include "InputManeger.h"
	#include <iostream>
	InputManeger::InputManeger()
	{
		
	}

	
	void InputManeger::handleEvent(const sf::Event& event) {
		if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
			sf::Keyboard::Scancode code = keyPressed->scancode;
			

			/*for (auto& [action, key] : keyMap) {
				if (key == code) {
					auto it = actionCallbacks.find(action);
					if (it != actionCallbacks.end() && it->second.onPressed)
						it->second.onPressed();
				}
			}*/
			keyStates[code] = true;
		}
		else if (const auto* keyReleased = event.getIf<sf::Event::KeyReleased>()) {
			sf::Keyboard::Scancode code = keyReleased->scancode;
			

			/*for (auto& [action, key] : keyMap) {
				if (key == code) {
					auto it = actionCallbacks.find(action);
					if (it != actionCallbacks.end() && it->second.onReleased)
						it->second.onReleased();
				}
			}*/
			keyStates[code] = false;
		}
		else if (const auto* mouse=event.getIf<sf::Event::MouseMoved>())
		{
			mousePosition.x = mouse->position.x;
			mousePosition.y = mouse->position.y;

		}
		
	}

	void InputManeger::bind(PlayerAction action, sf::Keyboard::Scancode key, const std::function<void()>& onPressed, const std::function<void()>& onReleased)
	{
		keyMap[action] = key;
		//actionCallbacks[action] = { onPressed, onReleased };
	}

	

	

	

