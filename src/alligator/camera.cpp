
#include "camera.h"

void Camera::bind()
{
	al_identity_transform(&m_transform);
	al_build_transform(&m_transform, m_position.x(), m_position.y(), m_scale.x(), m_scale.y(), m_rotation);
	al_use_transform(&m_transform);
}

void Camera::position(Vec2f new_position)
{
	m_position = new_position;
}

float Camera::x()
{
	return m_position.x();
}

float Camera::y()
{
	return m_position.y();
}

void Camera::position(float x, float y)
{
	m_position.set(x, y);
}

void Camera::move(float x, float y)
{
	m_position.set(m_position.x() + x, m_position.y() + y);
}

void Camera::scale(float x, float y)
{
	m_scale.set(x, y);
}


void Scroller::operator()(Camera &cam)
{
	Vec2f new_cam_position = scroll(cam.x(), cam.y());
}


Scroller::~Scroller()
{

}
