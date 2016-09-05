#include "input.h"
#include <algorithm>
#include <iostream>

Input* Input::instance = nullptr;

void Input::Initialize()
{
	instance = new Input();
}

void Input::Dispose()
{
	delete instance;
}

bool Input::IsKeyDown(int key)
{
	return instance->m_keyStates[key];
}

bool Input::IsKeyJustPressed(int key)
{
	return key == instance->m_lastPressed;
}

bool Input::Update()
{
	instance->m_lastPressed = ALLEGRO_KEY_MAX;
	if( instance->m_lastMouseButtonPressed != 0 )
	{
		instance->m_lastMouseButtonPressed = 0;
	}
	instance->m_mousePos.set( instance->m_mouseState.x, instance->m_mouseState.y );
}

bool Input::PreUpdate()
{
	al_get_mouse_state(&instance->m_mouseState);
}

const Vec2i &Input::GetMousePosition()
{
	return instance->m_mousePos;
}

bool Input::IsMouseButtonPressed(int button)
{
	return al_mouse_button_down(&(instance->m_mouseState), button);
}

bool Input::IsMouseButtonJustPressed(int button)
{
	return instance->m_lastMouseButtonPressed == button;
}

Input::Input()
{
	memset( m_keyStates, 0, ALLEGRO_KEY_MAX );
}

void Input::NotifyKeyDown(int key)
{
	instance->m_keyStates[key] = true;
	instance->m_lastPressed = key;

	for( auto processor : instance->m_inputProcessors )
	{
		processor->keyDown(key);
	}
}

void Input::NotifyMouseButtonDown(int button)
{
	instance->m_lastMouseButtonPressed = button;
}

void Input::NotifyKeyUp(int key)
{
	instance->m_keyStates[key] = false;

	for( auto processor : instance->m_inputProcessors )
	{
		processor->keyUp(key);
	}
}

void Input::AddInputProcessor(IInputProcessor::Ptr inputProcessor)
{
	instance->m_inputProcessors.push_back(inputProcessor);
	instance->m_inputProcessors.shrink_to_fit();
}
