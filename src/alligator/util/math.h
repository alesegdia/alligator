
#pragma once

#include <algorithm>

template <typename T>
class Vec2 {
public:
	Vec2() : m_x(0), m_y(0) {}
	Vec2(T x, T y) : m_x(x), m_y(y) {}
	Vec2(const Vec2<T>& other) : Vec2(other.m_x, other.m_y) {}

	void x( T newx )
	{
		m_x = newx;
	}

	void y( T newy )
	{
		m_y = newy;
	}

	T x() const
	{
		return m_x;
	}

	T y() const
	{
		return m_y;
	}

	void set( T x, T y )
	{
		m_x = x; m_y = y;
	}

	bool operator== ( const Vec2<T>& other ) const
	{
		return other.m_x == m_x && other.m_y == m_y;
	}

	bool operator != ( const Vec2<T>& other ) const
	{
		return !(other == *this);
	}

private:
	T m_x, m_y;
};

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;

template <typename T>
class Rect
{
public:
	Rect( T x, T y, T w, T h )
		: m_position(x, y),
		  m_size(w, h)
	{

	}

	Rect( const Vec2<T> pos, const Vec2<T> size )
		: m_position(pos), m_size(size)
	{

	}

	Rect( const Rect<T>& other )
		: m_position(other.x(), other.y()), m_size(other.w(), other.h())
	{

	}

	Rect()
	{

	}

	Vec2<T> min() const
	{
		return m_position;
	}

	Vec2<T> max() const
	{
		return m_position + m_size;
	}

	void position( Vec2f new_pos )
	{
		m_position = new_pos;
	}

	void x( T new_x )
	{
		m_position.x(new_x);
	}

	void y( T new_y )
	{
		m_position.y(new_y);
	}

	T x() const
	{
		return m_position.x();
	}

	T y() const
	{
		return m_position.y();
	}

	T w() const
	{
		return m_size.x();
	}

	T h() const
	{
		return m_size.y();
	}

private:
	Vec2<T> m_position, m_size;
};

typedef Rect<float> Rectf;

template <typename T>
float clamp(T v, T min, T max )
{
	return std::max(std::min(v, max), min);
}

template <typename T>
Rect<T> clamp( Rect<T> container, Rect<T> contained )
{
	Rect<T> rect;
	rect.x( clamp<T>(contained.x(), container.x(), container.x() + container.w() - contained.w()) );
	rect.y( clamp<T>(contained.y(), container.y(), container.y() + container.w() - contained.w()) );
	return rect;
}