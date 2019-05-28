#pragma once
#include <SDL.h>
#include <iostream>
using namespace std;

class CEvent {
public:
	CEvent();
	virtual ~CEvent();
	virtual void OnEvent(SDL_Event* Event);
	virtual void OnExit();
	virtual void OnKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode);
	virtual void OnKeyUp(SDL_Keycode sym, Uint16 mod, Uint16 scancode);
	virtual void OnMouseMove(int mx, int my, int relx, int rely, bool Left, bool Right, bool Middle);
	virtual void OnLButtonDown(int mx, int my);
	virtual void OnLButtonUp(int mx, int my);
	virtual void OnRButtonDown(int mx, int my);
	virtual void OnRButtonUp(int mx, int my);
	virtual void OnMButtonDown(int mx, int my);
	virtual void OnMButtonUp(int mx, int my);
	virtual void OnMouseFocus();
	virtual void OnMouseBlur();
	virtual void OnInputFocus();
	virtual void OnInputBlur();
	virtual void OnWindowResized(int data1, int data2);
	virtual void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
	virtual void OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
	virtual void OnJoyHat(Uint8 which, Uint8 hat, Uint8 button);
	virtual void OnJoyButtonDown(Uint8 which, Uint8 button);
	virtual void OnJoyButtonUp(Uint8 which, Uint8 button);
	virtual void OnUser(Uint8 type, int code, void* data1, void* data2);
};

CEvent::CEvent() {}

CEvent::~CEvent() {}

void CEvent::OnEvent(SDL_Event* Event) {
	switch (Event->type)
	{
	case SDL_WINDOWEVENT: {
		switch (Event->window.event)
		{
		case SDL_WINDOWEVENT_ENTER: {
			OnMouseFocus();
			break;
		}
		case SDL_WINDOWEVENT_LEAVE: {
			OnMouseBlur();
			break;
		}
		case SDL_WINDOWEVENT_FOCUS_GAINED: {
			OnInputFocus();
			break;
		}
		case SDL_WINDOWEVENT_FOCUS_LOST: {
			OnInputBlur();
			break;
		}
		case SDL_WINDOWEVENT_SHOWN: {
			break;
		}
		case SDL_WINDOWEVENT_HIDDEN: {
			break;
		}
		case SDL_WINDOWEVENT_EXPOSED: {
			break;
		}
		case SDL_WINDOWEVENT_MOVED: {
			break;
		}
		case SDL_WINDOWEVENT_RESIZED: {
			OnWindowResized(Event->window.data1, Event->window.data2);
			break;
		}
		case SDL_WINDOWEVENT_SIZE_CHANGED: {
			break;
		}
		case SDL_WINDOWEVENT_MINIMIZED: {
			break;
		}
		case SDL_WINDOWEVENT_MAXIMIZED: {
			break;
		}
		case SDL_WINDOWEVENT_RESTORED: {
			break;
		}
		case SDL_WINDOWEVENT_CLOSE: {
			break;
		}
		}
		break;
	}
	case SDL_QUIT: {
		OnExit();
		break;
	}
	case SDL_KEYDOWN: {
		OnKeyDown(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.scancode);
		break;
	}
	case SDL_KEYUP: {
		OnKeyUp(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.scancode);
		break;
	}
	case SDL_MOUSEMOTION: {
		OnMouseMove(Event->motion.x, Event->motion.y, Event->motion.xrel, Event->motion.yrel, (Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT)) != 0, (Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0, (Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
		break;
	}
	case SDL_MOUSEBUTTONDOWN: {
		switch (Event->button.button)
		{
		case SDL_BUTTON_LEFT: {
			OnLButtonDown(Event->button.x, Event->button.y);
			break;
		}
		case SDL_BUTTON_RIGHT: {
			OnRButtonDown(Event->button.x, Event->button.y);
			break;
		}
		case SDL_BUTTON_MIDDLE: {
			OnMButtonDown(Event->button.x, Event->button.y);
			break;
		}
		}
		break;
	}
	case SDL_MOUSEBUTTONUP: {
		switch (Event->button.button)
		{
		case SDL_BUTTON_LEFT: {
			OnLButtonUp(Event->button.x, Event->button.y);
			break;
		}
		case SDL_BUTTON_RIGHT: {
			OnRButtonUp(Event->button.x, Event->button.y);
			break;
		}
		case SDL_BUTTON_MIDDLE: {
			OnMButtonUp(Event->button.x, Event->button.y);
			break;
		}
		}
		break;
	}

	//Star getting things from here man!
	case SDL_JOYAXISMOTION: {
		OnJoyAxis(Event->jaxis.which, Event->jaxis.axis, Event->jaxis.value);
		break;
	}
	case SDL_JOYBALLMOTION: {
		OnJoyBall(Event->jball.which, Event->jball.ball, Event->jball.xrel, Event->jball.yrel);
		break;
	}
	case SDL_JOYHATMOTION: {
		OnJoyHat(Event->jhat.which, Event->jhat.hat, Event->jhat.value);
		break;
	}
	case SDL_JOYBUTTONDOWN: {
		OnJoyButtonDown(Event->jbutton.which, Event->jbutton.button);
		break;
	}
	case SDL_JOYBUTTONUP: {
		OnJoyButtonUp(Event->jbutton.which, Event->jbutton.button);
		break;
	}
	default: {
		OnUser(Event->user.type, Event->user.code, Event->user.data1, Event->user.data2);
		break;
	}
	}
}

void CEvent::OnExit() {}

void CEvent::OnKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode) {}

void CEvent::OnKeyUp(SDL_Keycode sym, Uint16 mod, Uint16 scancode) {}

void CEvent::OnMouseMove(int mx, int my, int relx, int rely, bool Left, bool Right, bool Middle) {}

void CEvent::OnLButtonDown(int mx, int my) {}

void CEvent::OnLButtonUp(int mx, int my) {}

void CEvent::OnRButtonDown(int mx, int my) {}

void CEvent::OnRButtonUp(int mx, int my) {}

void CEvent::OnMButtonDown(int mx, int my) {}

void CEvent::OnMButtonUp(int mx, int my) {}

void CEvent::OnMouseFocus() {}

void CEvent::OnMouseBlur() {}

void CEvent::OnInputFocus() {}

void CEvent::OnInputBlur() {}

void CEvent::OnWindowResized(int data1, int data2) {}

void CEvent::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value) {}

void CEvent::OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel) {}

void CEvent::OnJoyHat(Uint8 which, Uint8 hat, Uint8 button) {}

void CEvent::OnJoyButtonDown(Uint8 which, Uint8 button) {}

void CEvent::OnJoyButtonUp(Uint8 which, Uint8 button) {}

void CEvent::OnUser(Uint8 type, int code, void* data1, void* data2) {}