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
}

Input::Input()
{
	std::fill(std::begin(m_keyStates), std::begin(m_keyStates) + ALLEGRO_KEY_MAX, false);
}

void Input::NotifyKeyDown(int key)
{
	std::cout << "recv keydown: " << key << std::endl;
	instance->m_keyStates[key] = true;
	instance->m_lastPressed = key;

	if( instance->m_inputProcessor != nullptr )
	{
		instance->m_inputProcessor->keyDown(key);
	}
}

void Input::NotifyKeyUp(int key)
{
	std::cout << "recv keyup: " << key << std::endl;

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
