#include "animation.h"

Animation::Animation(float frame_duration, int num_frames)
{
	m_frameDuration = frame_duration;
	m_animDuration = frame_duration * num_frames;
	m_numFrames = num_frames;
	m_frames.reserve(m_numFrames);
}

void Animation::addFrame(ALLEGRO_BITMAP *frame)
{
	m_frames.push_back(frame);
	assert(m_frames.size() <= m_numFrames);
}

void Animation::addFrames(std::vector<ALLEGRO_BITMAP *> frames)
{
	m_frames.insert(m_frames.begin(), frames.begin(), frames.end());
}

void Animation::updateData(AnimationData &data)
{
	while( data.timer > m_animDuration )
	{
		data.timer -= m_animDuration;
	}

	int frame_index = floor(data.timer / m_frameDuration);
	data.currentFrame = m_frames[frame_index];
}


void AnimationData::reset()
{
	timer = 0;
}


void AnimationData::update(double t)
{
	timer += t;
}


void AnimationData::render(float x, float y)
{
	al_draw_bitmap(currentFrame, x, y, 0);
}
