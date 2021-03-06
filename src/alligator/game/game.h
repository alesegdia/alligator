#pragma once

#include <allegro5/allegro.h>
#include <memory>

#include <alligator/input/input.h>
#include "iscreen.h"

class Game {
public:
	Game ( int screen_width, int screen_height );
	virtual ~Game ();

	int exec(int argc, char** argv);
	ALLEGRO_DISPLAY* display();

	void close();

	void setScreen(IScreen::Ptr screen);

    void setUpdateFPS( int fps );

    void setRenderFPS( int fps );


private:

	int init(int argc, char **argv);

protected:

	void handleEvent(ALLEGRO_EVENT& ev);

	virtual void render();
	virtual void update(double delta);
	virtual int create(int argc, char** argv) = 0 ;
	virtual void dispose() = 0 ;

	virtual void notifyKeyUp( int key );
	virtual void notifyKeyDown( int key );
	virtual void notifyMouseButtonDown( int key );

	void grabMouse();
	void ungrabMouse();

	int m_screenWidth, m_screenHeight;

	ALLEGRO_DISPLAY* m_display = NULL;
	ALLEGRO_EVENT_QUEUE* m_eventQueue = NULL;

	bool m_doexit = false;

    bool m_showTitleFPS = true;

    double m_renderFPS = 1.0 / 120.f;
    double m_updateFPS = 1.0 / 120.f;

	// current screen
	IScreen::Ptr m_currentScreen;

};

