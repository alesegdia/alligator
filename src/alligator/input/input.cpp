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
	instance->update();
}

bool Input::PreUpdate()
{
	instance->preUpdate();
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
	std::fill(std::begin(m_keyStates), std::begin(m_keyStates) + ALLEGRO_KEY_MAX, false);
}

void Input::update()
{
	m_lastPressed = ALLEGRO_KEY_MAX;
	if( m_lastMouseButtonPressed != 0 )
	{
		m_lastMouseButtonPressed = 0;
		std::cout << "CLEAR last mouse button pressed" << std::endl;
	}
	m_mousePos.set( m_mouseState.x, m_mouseState.y );
}

void Input::preUpdate()
{
	al_get_mouse_state(&m_mouseState);
}

void Input::NotifyKeyDown(int key)
{
	instance->m_keyStates[key] = true;
	instance->m_lastPressed = key;

	if( instance->m_inputProcessor != nullptr )
	{
		instance->m_inputProcessor->keyDown(key);
	}
}

void Input::NotifyMouseButtonDown(int button)
{
	std::cout << "SET last mouse button pressed" << std::endl;
	instance->m_lastMouseButtonPressed = button;
}

void Input::NotifyKeyUp(int key)
{
	instance->m_keyStates[key] = false;

	if( instance->m_inputProcessor != nullptr )
	{
		instance->m_inputProcessor->keyUp(key);
	}
}

void Input::SetInputProcessor(IInputProcessor::Ptr inputProcessor)
{
	instance->m_inputProcessor = inputProcessor;
}
