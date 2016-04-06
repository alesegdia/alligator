#pragma once

#include <memory>

class IScreen
{
public:
	typedef std::shared_ptr<IScreen> Ptr;
	virtual ~IScreen() = 0 ;

	/**
	 * @brief called every time the screen is put to active
	 */
	virtual void show() = 0 ;

	/**
	 * @brief called every time the screen is removed from current active
	 */
	virtual void hide() = 0 ;

	/**
	 * @brief for game logic
	 * @param delta time between current and last frames
	 */
	virtual void update(double delta) = 0 ;

	/**
	 * @brief called in a fixed rate, for rendering
	 */
	virtual void render() = 0 ;

};
