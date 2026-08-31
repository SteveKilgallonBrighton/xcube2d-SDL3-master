#include "EventEngine.h"

//EventEngine::EventEngine() : running(true) {
//EventEngine::EventEngine() : running(true), window(nullptr) {
EventEngine::EventEngine() : running(true), event(), window(nullptr) {
	for (int i = 0; i < Key::LAST; ++i) {
		keys[i] = false;
	}

	buttons[Mouse::BTN_LEFT] = false;
	buttons[Mouse::BTN_RIGHT] = false;
}

EventEngine::~EventEngine() {}

void EventEngine::pollEvents() {
	while (SDL_PollEvent(&event)) {
		if ((event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) && event.key.repeat == 0) {
			updateKeys(event.key.key, event.type == SDL_EVENT_KEY_DOWN);
		}

		if (event.type == SDL_EVENT_QUIT) {
			keys[QUIT] = true;
		}

		/*buttons[Mouse::BTN_LEFT]  = (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_LMASK) != 0;
		buttons[Mouse::BTN_RIGHT] = (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_RMASK) != 0;*/

		if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				buttons[Mouse::BTN_LEFT] = true;
			}
			else if (event.button.button == SDL_BUTTON_RIGHT) {
				buttons[Mouse::BTN_RIGHT] = true;
			}
		}
		else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				buttons[Mouse::BTN_LEFT] = false;
			}
			else if (event.button.button == SDL_BUTTON_RIGHT) {
				buttons[Mouse::BTN_RIGHT] = false;
			}
		}
		// Remove the previous SDL_GetMouseState calls for buttons, as they are now event-driven
		// buttons[Mouse::BTN_LEFT]  = (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_LMASK) != 0;
		// buttons[Mouse::BTN_RIGHT] = (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_RMASK) != 0;
	}
	
}

void EventEngine::updateKeys(const SDL_Keycode key, bool keyDown) {
	Key index;

	switch (key) {
		case SDLK_RIGHT:	index = Key::RIGHT; break;
		case SDLK_D:		index = Key::D; break;
		case SDLK_LEFT:		index = Key::LEFT; break; 
		case SDLK_A:		index = Key::A; break;
		case SDLK_UP:		index = Key::UP; break;
		case SDLK_W:		index = Key::W; break;
		case SDLK_DOWN:		index = Key::DOWN; break;
		case SDLK_S:		index = Key::S; break;
		case SDLK_ESCAPE:	index = Key::ESC; break;
		case SDLK_SPACE:	index = Key::SPACE; break;
		default:
			return;	// we don't care about other keys, at least now
	}

	keys[index] = keyDown;
}

void EventEngine::setPressed(Key key) {
    keys[key] = true;
}

void EventEngine::setPressed(Mouse btn) {
    buttons[btn] = true;
}

bool EventEngine::isPressed(Key key) {
	return keys[key];
}

bool EventEngine::isPressed(Mouse btn) {
	return buttons[btn];
}

void EventEngine::setMouseRelative(bool b) {
	//SDL_SetWindowRelativeMouseMode(SDL_GetKeyboardFocus(), b);
	SDL_Window* target = window ? window : SDL_GetKeyboardFocus();
	if (!target) {
#ifdef __DEBUG
		debug("EventEngine::setMouseRelative()", "no window available, skipping");
#endif
		return;
	}
	SDL_SetWindowRelativeMouseMode(target, b);
}

Point2 EventEngine::getMouseDPos() {
	Point2 mouseDPos;
	float x, y;
	SDL_GetRelativeMouseState(&x, &y);
	mouseDPos.x = (int)x;
	mouseDPos.y = (int)y;
	return mouseDPos;
}

Point2 EventEngine::getMousePos() {
	Point2 pos;
	float x, y;
	SDL_GetMouseState(&x, &y);
	pos.x = (int)x;
	pos.y = (int)y;
	return pos;
}
