#pragma once

#include <allegro5/allegro5.h>
#include "geometry.h"

class Camera
{
public:

	void bind()
	{
		al_identity_transform(&m_transform);
		al_build_transform(&m_transform, m_position.x(), m_position.y(), m_scale.x(), m_scale.y(), m_rotation);
		al_use_transform(&m_transform);
	}

	void position( float x, float y )
	{
		m_position.set(x, y);
	}

	void scale( float x, float y )
	{
		m_scale.set(x, y);
	}

private:
	ALLEGRO_TRANSFORM m_transform;

	// cache last (position, scale) if performance issues
	Vec2f m_scale;
	Vec2f m_position;
	float m_rotation;

};
