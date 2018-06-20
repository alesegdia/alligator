#include "spritesheet.h"




Spritesheet::Spritesheet(size_t width, size_t height, ALLEGRO_BITMAP *bitmap)
{
	reset( width, height, bitmap );
}

ALLEGRO_BITMAP *Spritesheet::getFrame(size_t num_frame)
{
	assert( num_frame < m_frames.size() );
	return m_frames[num_frame];
}

ALLEGRO_BITMAP *Spritesheet::getFrame(size_t x_frame, size_t y_frame)
{
	size_t index = coordToIndex(x_frame, y_frame);
	assert( index < m_frames.size() );
	return getFrame(coordToIndex(x_frame, y_frame));
}

std::vector<ALLEGRO_BITMAP *> Spritesheet::getFrames(size_t start, size_t end)
{
	assert( start <= m_frames.size() );
	assert( end <= m_frames.size() );

	std::vector<ALLEGRO_BITMAP*> frames;
	for( size_t i = start; i <= end; i++ )
	{
		frames.push_back(m_frames[i]);
	}

	return frames;
}

void Spritesheet::reset(size_t width, size_t height, ALLEGRO_BITMAP *bitmap)
{
	m_width = width;
	m_height = height;

	size_t num_frames = width * height;
	size_t tw = al_get_bitmap_width(bitmap) / width;
	size_t th = al_get_bitmap_height(bitmap) / height;

	m_frames.clear();
	m_frames.reserve(num_frames);

	for( size_t i = 0; i < height; i++ )
	{
		for( size_t j = 0; j < width; j++ )
		{
			ALLEGRO_BITMAP* frame = al_create_sub_bitmap( bitmap, j * tw, i * th, tw, th );
			m_frames.push_back(frame);
		}
	}
}

size_t Spritesheet::coordToIndex(size_t x, size_t y)
{
	return y * m_width + x;
}
