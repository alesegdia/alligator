#pragma once

#include <allegro5/allegro5.h>
#include "math.h"

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


class Scroller
{
public:
	virtual ~Scroller() = 0 ;

	void operator()(Camera& cam);

	virtual Vec2f scroll( float current_x, float current_y ) = 0 ;

};


class FixedScroller : public Scroller
{
public:

	FixedScroller( Rectf outer, Rectf inner, Rectf character, Vec2f viewport )
		: m_outer(outer), m_inner(inner), m_character(character) {}

	Vec2f scroll(float current_x, float current_y) override
	{
		Rectf campos(clamp(m_inner, m_outer));
		return campos.min();
	}

private:
	Rectf m_outer;
	Rectf m_inner;
	Rectf m_character;
};


