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

	KEY_SPACE,

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

	void updateKey(int key, int action) {
		switch (key) {

		case GLFW_KEY_0: key = KEY_0; break;
		case GLFW_KEY_1: key = KEY_1; break;
		case GLFW_KEY_2: key = KEY_2; break;
		case GLFW_KEY_3: key = KEY_3; break;
		case GLFW_KEY_4: key = KEY_4; break;
		case GLFW_KEY_5: key = KEY_5; break;
		case GLFW_KEY_6: key = KEY_6; break;
		case GLFW_KEY_7: key = KEY_7; break;
		case GLFW_KEY_8: key = KEY_8; break;
		case GLFW_KEY_9: key = KEY_9; break;

		case GLFW_KEY_A: key = KEY_A; break;
		case GLFW_KEY_B: key = KEY_B; break;
		case GLFW_KEY_C: key = KEY_C; break;
		case GLFW_KEY_D: key = KEY_D; break;
		case GLFW_KEY_E: key = KEY_E; break;
		case GLFW_KEY_F: key = KEY_F; break;
		case GLFW_KEY_G: key = KEY_G; break;
		case GLFW_KEY_H: key = KEY_H; break;
		case GLFW_KEY_I: key = KEY_I; break;
		case GLFW_KEY_J: key = KEY_J; break;
		case GLFW_KEY_K: key = KEY_K; break;
		case GLFW_KEY_L: key = KEY_L; break;
		case GLFW_KEY_M: key = KEY_M; break;
		case GLFW_KEY_N: key = KEY_N; break;
		case GLFW_KEY_O: key = KEY_O; break;
		case GLFW_KEY_P: key = KEY_P; break;
		case GLFW_KEY_Q: key = KEY_Q; break;
		case GLFW_KEY_R: key = KEY_R; break;
		case GLFW_KEY_S: key = KEY_S; break;
		case GLFW_KEY_T: key = KEY_T; break;
		case GLFW_KEY_U: key = KEY_U; break;
		case GLFW_KEY_V: key = KEY_V; break;
		case GLFW_KEY_W: key = KEY_W; break;
		case GLFW_KEY_X: key = KEY_X; break;
		case GLFW_KEY_Y: key = KEY_Y; break;
		case GLFW_KEY_Z: key = KEY_Z; break;

		case GLFW_KEY_SPACE: key = KEY_SPACE; break;

		default: return; // key is not mapped in input? skip the rest
		}

		switch (action)
		{
		case GLFW_PRESS:	keys[key] = KEY_PRESS; break;
		case GLFW_RELEASE:	keys[key] = KEY_RELEASE; break;
		default: break;
		}

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