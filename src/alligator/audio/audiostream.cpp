
#include "audiostream.h"


std::basic_ifstream<char>::pos_type filesize(const char *filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

AudioStream::AudioStream(const char *path, ALLEGRO_EVENT_QUEUE *queue)
{
	// load stream from file
	m_stream = al_load_audio_stream(path, 4, 2048);
	assert(m_stream);

	// create voice for the stream
	m_voice = al_create_voice(44100, al_get_audio_stream_depth(m_stream), ALLEGRO_CHANNEL_CONF_2);


	al_register_event_source(queue, al_get_audio_stream_event_source(m_stream));

	al_attach_audio_stream_to_voice(m_stream, m_voice);

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

void AudioStream::play()
{
	al_set_audio_stream_playing(m_stream, true);
	al_set_voice_playing(m_voice, true);
}

