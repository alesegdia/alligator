#pragma once

#include <allegro5/allegro_audio.h>

#include <memory>
#include <fstream>


class AudioStream
{
public:

	typedef std::shared_ptr<AudioStream> SharedPtr;

	AudioStream(const char* path, ALLEGRO_PLAYMODE playmode = ALLEGRO_PLAYMODE_ONCE);

	~AudioStream();

	void playmode( ALLEGRO_PLAYMODE playmode );

	void play();

	void pause();

	void resume();

	bool playing();

	bool rewind()
	{
		return al_rewind_audio_stream(m_stream);
	}

private:
	ALLEGRO_AUDIO_STREAM* m_stream;
	ALLEGRO_VOICE* m_voice;

	double m_lastPause = 0;

};
