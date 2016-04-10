#pragma once

#include <allegro5/allegro.h>
#include <vector>
#include <memory>

class Spritesheet
{
public:

	typedef std::shared_ptr<Spritesheet> SharedPtr;

	explicit Spritesheet( size_t width, size_t height, ALLEGRO_BITMAP* bitmap );

	/**
	 * @brief retrieves a frame by its index
	 * @param num_frame frame index
	 * @return the sub bitmap associated to the index
	 */
	ALLEGRO_BITMAP* getFrame( int num_frame );

	/**
	 * @brief retrieves a frame by its coordinate
	 * @param x_frame the x coordinate
	 * @param y_frame the y coordinate
	 * @return the sub bitmap in specified coordinate
	 */
	ALLEGRO_BITMAP* getFrame( int x_frame, int y_frame );

	std::vector<ALLEGRO_BITMAP*> getFrames( int start, int end );

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
	int coordToIndex( int x, int y );

	std::vector<ALLEGRO_BITMAP*> m_frames;
	ALLEGRO_BITMAP* m_bitmap;

	int m_height, m_width;

};
