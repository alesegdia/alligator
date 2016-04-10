#pragma once

#include <memory>

class IInputProcessor
{
public:
	typedef IInputProcessor* Ptr;

	virtual void keyUp(int key) = 0 ;
	virtual void keyDown(int key) = 0 ;

};
