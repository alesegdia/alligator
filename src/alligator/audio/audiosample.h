#pragma once

#include <memory>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class AudioSample
{
public:

	typedef std::shared_ptr<AudioSample> SharedPtr;

	AudioSample( const char* path );

	~AudioSample();

	void play(float volume = 1.f);

	void rewind();

private:
	ALLEGRO_SAMPLE* m_sample;
	ALLEGRO_SAMPLE_ID m_id;

};
