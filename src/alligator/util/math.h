
#pragma once

#include <algorithm>
#include <iostream>
#include <cmath>

template <typename T>
class Vec2 {
public:
	Vec2() : m_x(0), m_y(0) {}
	Vec2(T x, T y) : m_x(x), m_y(y) {}
	Vec2(const Vec2<T>& other) : Vec2(other.m_x, other.m_y) {}

	static float Distance( const Vec2<T>& a, const Vec2<T>& b )
	{
		float dx = ((float)a.x()) - ((float)b.x());
		float dy = ((float)a.y()) - ((float)b.y());
		return sqrtf( dx * dx + dy * dy );
	}

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

	Vec2<T> operator+( const Vec2<T>& other ) const
	{
		return Vec2<T>(m_x + other.m_x, m_y + other.m_y);
	}

	bool operator== ( const Vec2<T>& other ) const
	{
		return other.m_x == m_x && other.m_y == m_y;
	}

	bool operator != ( const Vec2<T>& other ) const
	{
		return !(other == *this);
	}

	Vec2& operator*= ( float p )
	{
		m_x *= p;
		m_y *= p;
		return *this;
	}

private:
	T m_x, m_y;
};

template <typename T>
std::ostream &operator<<( std::ostream& os, const Vec2<T>& v )
{
	os << "(" << v.x() << "," << v.y() << ")";
	return os;
}

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

	void position( float x, float y )
	{
		m_position.set(x, y);
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

template <typename T>
Vec2<T> ortho_to_iso( const Vec2<T>& ortho )
{
	int x, y;
	x = ortho.x();
	y = ortho.y();
	return Vec2i( x - y, (x + y) / 2 );
}

template <typename T>
Vec2<T> iso_to_ortho( const Vec2<T>& iso )
{
	int x, y;
	x = iso.x();
	y = iso.y();
	return Vec2<T>( 2 * y + x, 2 * y - x );
}

float lerp(float v0, float v1, float t);

template <typename T>
Vec2<T> lerp( const Vec2<T>& v0, const Vec2<T>& v1, float t )
{
	return Vec2<T>( lerp(v0.x(), v1.x(), t ), lerp(v0.y(), v1.y(), t ) );
}
