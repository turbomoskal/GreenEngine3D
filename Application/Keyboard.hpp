﻿/*
*		Keyboard codes
*/
#pragma once

// TODO: Check S841 warning. If there is a bug - fix it
namespace KeyCode
{
	enum class Key {
		None = 0x00,	// Nothing is pressed
		LButton,		// Left mouse
		RButton,		// Right mouse
		Cancel,			// ?Cancel
		MButton,		// Middle mouse
		XButton1,		// ?X1 mouse
		XButton2,		// ?X2 mouse
		Backspace = 0x08,
		Tab,
		Clear = 0x0c,
		Enter,
		Shift = 0x10,
		Ctrl,
		Alt,
		Pause,
		Caps,
		Esc = 0x1b,
		Space = 0x20,
		PgUp,
		PgDown,
		End,
		Home,
		Left,
		Up,
		Right,
		Down,
		Insert = 0x2d,
		Delete,
		Help,
		D0,
		D1,
		D2,
		D3,
		D4,
		D5,
		D6,
		D7,
		D8,
		D9,
		A = 0x41,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		LWin,
		RWin,
		Apps,
		Sleep = 0x5f,
		NumPad0,
		NumPad1,
		NumPad2,
		NumPad3,
		NumPad4,
		NumPad5,
		NumPad6,
		NumPad7,
		NumPad8,
		NumPad9,
		Multiply,
		Add,
		Separator,
		Subtract,
		Decimal,
		Divide,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		F16,
		F17,
		F18,
		F19,
		F20,
		F21,
		F22,
		F23,
		F24,
		NumLock = 0x90,
		ScrollLock = 0x91,
		LShiftKey = 0xa0,
		RShiftKey,
		LControlKey,
		RControlKey,
		LAlt,
		RAlt
	};
};