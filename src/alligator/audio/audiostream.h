#pragma once

#include <allegro5/allegro_audio.h>

#include <memory>
#include <fstream>


class AudioStream
{
public:

	typedef std::shared_ptr<AudioStream> SharedPtr;

	AudioStream(const char* path);

	~AudioStream();

	void play();

private:
	ALLEGRO_AUDIO_STREAM* m_stream;
	ALLEGRO_VOICE* m_voice;

};
