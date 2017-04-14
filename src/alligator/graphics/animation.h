#pragma once

#include <allegro5/allegro.h>
#include <memory>
#include <cmath>
#include "spritesheet.h"

struct AnimationData
{
	void reset();

	void update( double t );

	void render(float x, float y);

    double timer = 0;
	ALLEGRO_BITMAP* currentFrame;
};

class Animation
{
public:

	typedef std::shared_ptr<Animation> SharedPtr;

	Animation(float frame_duration, int num_frames);
	Animation(float frame_duration, int num_frames, std::vector<ALLEGRO_BITMAP*> frames);

	/**
	 * @brief adds a frame to the animation
	 * @param frame the frame to add
	 */
	void addFrame( ALLEGRO_BITMAP* frame );

	void addFrames( std::vector<ALLEGRO_BITMAP*> frames );

	/**
	 * @brief updates frame and fix timer to data
	 * @param data the animation data to be updated
	 */
	void updateData( AnimationData& data );

private:
	std::vector<ALLEGRO_BITMAP*> m_frames;
	float m_frameDuration;
	float m_animDuration;
	int m_numFrames;

};
