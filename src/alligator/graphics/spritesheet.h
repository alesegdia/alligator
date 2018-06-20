#pragma once

#include <allegro5/allegro.h>
#include <vector>
#include <memory>

class Spritesheet
{
public:

	typedef std::shared_ptr<Spritesheet> SharedPtr;

	/**
	 * @brief Spritesheet
	 * @param width in tiles
	 * @param height in tiles
	 * @param bitmap
	 */
	explicit Spritesheet( size_t width, size_t height, ALLEGRO_BITMAP* bitmap );

	~Spritesheet()
	{
		for( ALLEGRO_BITMAP* bm : m_frames )
		{
			al_destroy_bitmap(bm);
		}
	}

	/**
	 * @brief retrieves a frame by its index
	 * @param num_frame frame index
	 * @return the sub bitmap associated to the index
	 */
	ALLEGRO_BITMAP* getFrame( size_t num_frame );

	/**
	 * @brief retrieves a frame by its coordinate
	 * @param x_frame the x coordinate
	 * @param y_frame the y coordinate
	 * @return the sub bitmap in specified coordinate
	 */
	ALLEGRO_BITMAP* getFrame( size_t x_frame, size_t y_frame );

	std::vector<ALLEGRO_BITMAP*> getFrames(size_t start, size_t end );
	std::vector<ALLEGRO_BITMAP*> getAllFrames()
	{
		return getFrames(0, m_frames.size() - 1);
	}

private:

	/**
	 * @brief resets spritesheet internals to store a new spritesheet data
	 * @param width in tiles of the spritesheet
	 * @param height in tiles of the spritesheet
	 * @param bitmap the whole spritesheet
	 */
	void reset( size_t width, size_t height, ALLEGRO_BITMAP* bitmap );

	/**
	 * @brief translates a 2D cartesian coordinate to vector index
	 * @param x coordinate
	 * @param y coordinate
	 * @return the index
	 */
	size_t coordToIndex(size_t x, size_t y );

	std::vector<ALLEGRO_BITMAP*> m_frames;
	ALLEGRO_BITMAP* m_bitmap;

	int m_height, m_width;

};
