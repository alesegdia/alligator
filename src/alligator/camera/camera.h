#pragma once

#include <allegro5/allegro5.h>
#include <alligator/util/math.h>

#include <memory>

class Camera
{
public:

	typedef std::shared_ptr<Camera> SharedPtr;

	Camera( Vec2f viewport = Vec2f(0, 0) );

	void bind();

	void position( Vec2f new_position );

	float x();

	float y();

	Rectf boundary() const;

	void position( float x, float y );

	void move( float x, float y );

	void scale( float x, float y );

private:
	ALLEGRO_TRANSFORM m_transform;

	// cache last (position, scale) if performance issues
    Vec2f m_scale = Vec2f(1, 1);
	Vec2f m_position = Vec2f(0,0);
	float m_rotation = 0;

	Vec2f m_viewport;

};


class Scroller
{
public:
	virtual ~Scroller() = 0 ;

	void operator()(Camera& cam, float x, float y);

	virtual Vec2f scroll( const Camera& cam, Vec2f focus ) = 0 ;

};


class FixedScroller : public Scroller
{
public:

	FixedScroller( Rectf global );

	Vec2f scroll( const Camera& cam, Vec2f focus ) override;

private:
	Rectf m_globalBounds;

};


