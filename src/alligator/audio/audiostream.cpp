
#include "audiostream.h"


AudioStream::AudioStream(const char *path, ALLEGRO_PLAYMODE playmode)
{
	// load stream from file
	m_stream = al_load_audio_stream(path, 4, 2048);
	assert(m_stream);

	// create voice for the stream
	m_voice = al_create_voice(44100, al_get_audio_stream_depth(m_stream), ALLEGRO_CHANNEL_CONF_2);


	al_attach_audio_stream_to_voice(m_stream, m_voice);

	this->playmode(playmode);

	//al_detach_voice(m_voice);
	//assert(m_stream != 0);
}

AudioStream::~AudioStream()
{
	//al_set_audio_stream_playing(m_stream, false);
	al_detach_audio_stream(m_stream);
	al_destroy_audio_stream(m_stream);
	al_destroy_voice(m_voice);
}

void AudioStream::playmode(ALLEGRO_PLAYMODE playmode)
{
	al_set_audio_stream_playmode(m_stream, playmode);
}

void AudioStream::play()
{
	al_set_audio_stream_playing(m_stream, true);
	al_set_voice_playing(m_voice, true);
}

void AudioStream::pause()
{
	al_set_audio_stream_playing(m_stream, false);
	m_lastPause = al_get_audio_stream_position_secs(m_stream);
}

void AudioStream::resume()
{
	al_set_audio_stream_playing(m_stream, true);
	assert(al_seek_audio_stream_secs(m_stream, m_lastPause));
}

bool AudioStream::playing()
{
	return al_get_audio_stream_playing(m_stream);
}

bool AudioStream::rewind()
{
	al_seek_audio_stream_secs(m_stream, 0);
	return al_rewind_audio_stream(m_stream);
}

