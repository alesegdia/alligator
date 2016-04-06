#pragma once

#include <memory>

class IInputProcessor
{
public:
	typedef std::shared_ptr<IInputProcessor> Ptr;

	virtual void keyUp(int key) = 0 ;
	virtual void keyDown(int key) = 0 ;

};
