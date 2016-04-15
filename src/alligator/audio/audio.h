#pragma once

#include <allegro5/allegro5.h>

#include "audiostream.h"

class Audio
{
public:

	static void Initialize(ALLEGRO_EVENT_QUEUE* queue)
	{
		m_queue = queue;
	}

	static void Dispose()
	{

	}

	static AudioStream::SharedPtr NewStream(const char* path)
	{
		return AudioStream::SharedPtr(new AudioStream(path, Audio::m_queue));
	}

private:
	static Audio* instance;

	static ALLEGRO_EVENT_QUEUE* m_queue;
};
