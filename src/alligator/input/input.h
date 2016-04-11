#pragma once

#include <allegro5/allegro.h>
#include <memory>

#include "iinputprocessor.h"

class Input
{
public:

	static void Initialize();
	static void Dispose();

	static bool IsKeyDown( int key );
	static bool IsKeyJustPressed( int key );
	static bool Update();

	static void NotifyKeyDown( int key );
	static void NotifyKeyUp( int key );

	static void SetInputProcessor( IInputProcessor::Ptr inputProcessor );

private:
	Input();

	static Input* instance;

	IInputProcessor::Ptr m_inputProcessor = nullptr;
	int m_lastPressed;

	bool m_keyStates[ALLEGRO_KEY_MAX];
};
