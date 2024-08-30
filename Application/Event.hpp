/*
*		Events
*/
#pragma once
#include "Keyboard.hpp"
#include <cstdint>

class EventArgs {
public:
	EventArgs() = default;
};

class KeyEventArgs : public EventArgs {
public:
	using base = EventArgs;
	enum class KeyState {
		Released = 0,
		Pressed
	};

	KeyEventArgs(KeyCode::Key _Key, uint32_t _Char, KeyState _State, bool _Ctrl, bool _Shift, 
		bool _Alt) :
		Key(_Key),
		Char(_Char),
		State(_State),
		Ctrl(_Ctrl),
		Shift(_Shift),
		Alt(_Alt) {}

	KeyCode::Key	Key;
	uint32_t		Char;
	KeyState		State;
	bool			Ctrl;
	bool			Shift;
	bool			Alt;
};

class MouseMotionEventArgs : public EventArgs {
	using base = EventArgs;
public:
	MouseMotionEventArgs(bool _LButton, bool _RButton, bool _MButton,
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

class MouseButtonEventArgs : public EventArgs {
	using base = EventArgs;
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
	MouseButtonEventArgs(MouseButton _ButtonID, ButtonState _ButtonState, bool _LeftButton, 
		bool _RightButton, bool _Control, bool _Shift, int _X, int _Y) :
		Button(_ButtonID),
		State(_ButtonState),
		LeftButton(_LeftButton),
		RightButton(_RightButton),
		Control(_Control),
		Shift(_Shift),
		X(_X),
		Y(_Y) {}
	MouseButton		Button;
	ButtonState		State;
	bool			LeftButton;
	bool			RightButton;
	bool			Control;
	bool			Shift;
	int				X;
	int				Y;
};

class MouseWheelEventArgs : public EventArgs {
public:
	using base = EventArgs;
	MouseWheelEventArgs(float _WheelD, bool _LeftButton, bool _MiddleButton, bool _RightButton,
		bool _Control, bool _Shift, int _X, int _Y) :
		WheelDelta(_WheelD),
		LeftButton(_LeftButton),
		MiddleButton(_MiddleButton),
		RightButton(_RightButton),
		Control(_Control),
		Shift(_Shift),
		X(_X),
		Y(_Y) {}
	float	WheelDelta;
	bool	LeftButton;
	bool	MiddleButton;
	bool	RightButton;
	bool	Control;
	bool	Shift;
	int		X;
	int		Y;
};

class ResizeEventArgs : public EventArgs {
public:
	using base = EventArgs;
	ResizeEventArgs(int _Width, int _Height) :
		Width(_Width),
		Height(_Height) {}
	int		Width;
	int		Height;
};

class UpdateEventArgs : public EventArgs {
public:
	using base = EventArgs;
	UpdateEventArgs(double _DeltaTime, double _TotalTime, uint64_t _FrameNumber) :
		ElapsedTime(_DeltaTime),
		TotalTime(_TotalTime),
		FrameNumber(_FrameNumber) {}
	double		ElapsedTime;
	double		TotalTime;
	uint64_t	FrameNumber;
};

class RenderEventArgs :public EventArgs {
public:
	using base = EventArgs;
	RenderEventArgs(double _DeltaTime, double _TotalTime, uint64_t _FrameNumber) :
		ElapsedTime(_DeltaTime),
		TotalTime(_TotalTime),
		FrameNumber(_FrameNumber) {}
	double		ElapsedTime;
	double		TotalTime;
	uint64_t	FrameNumber;
};

class UserEventArgs : public EventArgs {
public:
	using base = EventArgs;
	UserEventArgs(int code, void* data1, void* data2) :
		Code(code),
		Data1(data1),
		Data2(data2) {}

	int		Code;
	void*	Data1;
	void*	Data2;
};