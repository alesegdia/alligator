
#include "audiosample.h"

AudioSample::AudioSample(const char *path)
{
	m_sample = al_load_sample(path);
	assert(m_sample);
}

AudioSample::~AudioSample()
{
	al_destroy_sample(m_sample);
}

void AudioSample::play(float volume)
{
	al_play_sample(m_sample, volume, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, &m_id);
}

void AudioSample::rewind()
{
	al_stop_sample(&m_id);
}
