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

	static void NotifyKeyDown( int key );
	static void NotifyKeyUp( int key );

	static void SetInputProcessor( IInputProcessor::Ptr inputProcessor )
	{
		instance->m_inputProcessor = inputProcessor;
	}

private:
	Input();

	static Input* instance;

	IInputProcessor::Ptr m_inputProcessor;

	bool m_keyStates[ALLEGRO_KEY_MAX];
};
