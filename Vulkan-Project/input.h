#pragma once
#include <array>

enum Key {
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S, 
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,

	MAX_KEYS
};

enum KeyState {
	KEY_IDLE,
	KEY_PRESS,
	KEY_DOWN,
	KEY_RELEASE
};

struct Input {
	std::array<KeyState, Key::MAX_KEYS> keys;

	bool getKeyDown(Key key) {
		return keys[key] == KEY_PRESS || keys[key] == KEY_DOWN;
	}

	bool getKeyPress(Key key) {
		return keys[key] == KEY_PRESS;
	}

	bool getKeyRelease(Key key) {
		return keys[key] == KEY_RELEASE;
	}

	void preUpdate() {
		for (auto& key : keys) {
			switch (key)
			{
			case KEY_PRESS:		key = KEY_DOWN; break;
			case KEY_RELEASE:	key = KEY_IDLE; break;
			default: break;
			}
		}
	}
};