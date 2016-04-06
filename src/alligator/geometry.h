
#pragma once

template <typename T>
class Vec2 {
public:
	Vec2() : m_x(0), m_y(0) {}
	Vec2(float x, float y) : m_x(x), m_y(y) {}
	Vec2(const Vec2<T>& other) : Vec2(other.m_x, other.m_y) {}

	void x( T newx )
	{
		m_x = newx;
	}

	void y( T newy )
	{
		m_y = newy;
	}

	T x()
	{
		return m_x;
	}

	T y()
	{
		return m_y;
	}

	void set( float x, float y )
	{
		m_x = x; m_y = y;
	}

	bool operator== ( const Vec2<T>& other )
	{
		return other.m_x == m_x && other.m_y == m_y;
	}

	bool operator != ( const Vec2<T>& other )
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
	Vec2<T> min()
	{
		return m_min;
	}

	Vec2<T> max()
	{
		return m_max;
	}

	void min(Vec2<T> min )
	{
		m_min = min;
	}

	void max( Vec2<T> max )
	{
		m_max = max;
	}

private:
	Vec2<T> m_min, m_max;
};
