#pragma once

#include <memory>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class AudioSample
{
public:

	typedef std::shared_ptr<AudioSample> SharedPtr;

	AudioSample( const char* path )
	{
		m_sample = al_load_sample(path);
		assert(m_sample);
	}

	~AudioSample()
	{
		al_destroy_sample(m_sample);
	}

	void play()
	{
		al_play_sample(m_sample, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, &m_id);
	}

	void rewind()
	{
		al_stop_sample(&m_id);
	}

private:
	ALLEGRO_SAMPLE* m_sample;
	ALLEGRO_SAMPLE_ID m_id;

};
