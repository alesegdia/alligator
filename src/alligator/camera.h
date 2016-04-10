#pragma once

#include <allegro5/allegro5.h>
#include "geometry.h"

class Camera
{
public:

	Camera( Vec2f viewport )
		: m_viewport(viewport)
	{

	}

	void bind();

	void position( Vec2f new_position );

	float x();

	float y();

	void position( float x, float y );

	void move( float x, float y );

	void scale( float x, float y );

private:
	ALLEGRO_TRANSFORM m_transform;

	// cache last (position, scale) if performance issues
	Vec2f m_scale = Vec2f(0,0);
	Vec2f m_position = Vec2f(0,0);
	float m_rotation = 0;

	Vec2f m_viewport;

};

};
