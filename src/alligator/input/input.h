#pragma once

#include <allegro5/allegro.h>
#include <memory>
#include <vector>

#include "../util/math.h"

#include "iinputprocessor.h"

class Input
{
public:

	static void Initialize();
	static void Dispose();

	static bool IsKeyDown( int key );
	static bool IsKeyJustPressed( int key );
	static bool Update();
	static bool PreUpdate();

	static const Vec2i& GetMousePosition();
	static bool IsMouseButtonPressed(int button);
	static bool IsMouseButtonJustPressed(int button);

	static void NotifyKeyDown( int key );
	static void NotifyMouseButtonDown(int button );

	static void NotifyKeyUp( int key );

	static void AddInputProcessor( IInputProcessor::Ptr inputProcessor );
	static void RemoveInputProcessor( IInputProcessor::Ptr inputProcessor );

private:
	Input();

	static Input* instance;

	std::vector<IInputProcessor::Ptr> m_inputProcessors;
	int m_lastPressed;
	int m_lastMouseButtonPressed;
	Vec2i m_mousePos;
	ALLEGRO_MOUSE_STATE m_mouseState;
	bool m_keyStates[ALLEGRO_KEY_MAX];
};
