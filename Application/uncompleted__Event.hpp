/*
*		Events
*/
#pragma once
#include "Keyboard.hpp"

class Event {
public:
	Event() = default;
};

class KeyEvent : public Event {
	using uint8 = unsigned int;
	using base = Event;
public:
	enum class KeyState {
		Released = 0,
		Pressed
	};

	KeyEvent(Keyboard _Key, uint8 _Char, KeyState _State, bool _Ctrl, bool _Shift, bool _Alt) :
		Key(_Key),
		Char(_Char),
		State(_State),
		Ctrl(_Ctrl),
		Shift(_Shift),
		Alt(_Alt) {}

	Keyboard	Key;
	uint8		Char;
	KeyState	State;
	bool		Ctrl;
	bool		Shift;
	bool		Alt;
};

class MouseMotionEvent : public Event {
	using base = Event;
public:
	MouseMotionEvent(bool _LButton, bool _RButton, bool _MButton, 
		bool _Ctrl, bool _Shift, bool _Alt, 
		int _PositionX, int _PositionY) :
		LButton(_LButton),
		RButton(_RButton),
		MButton(_MButton),
		Ctrl(_Ctrl),
		Shift(_Shift),
		Alt(_Alt),
		PositionX(_PositionX),
		PositionY(_PositionY) {}

	bool	LButton;
	bool	RButton;
	bool	MButton;
	bool	Ctrl;
	bool	Shift;
	bool	Alt;
	int		PositionX;
	int		PositionY;
	int		RelativeX;
	int		RelativeY;
};

class MouseButtonEvent : public Event {
	using base = Event;
public:
	enum class MouseButton {
		None = 0,
		Left,
		Right,
		Middle
	};
	enum class ButtonState {
		Released = 0,
		Pressed
	};
};

class MouseWheelEvent : public Event {

};

class ResizeEvent : public Event {

};

class UpdateEvent : public Event {

};

class RenderEvent :public Event {

};

class UserEvent : public Event {

};