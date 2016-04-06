#include <allegro5/allegro.h>
#include <memory>

#include "input.h"
#include "iscreen.h"

class Game {
public:
	Game ( int screen_width, int screen_height );
	virtual ~Game ();

	int exec();
	ALLEGRO_DISPLAY* display();

	void close();

private:

	int init();

protected:

	void handleEvent(ALLEGRO_EVENT& ev);

	virtual void render();
	virtual void update(double delta);
	virtual void create() = 0 ;
	virtual void dispose() = 0 ;

	virtual void notifyKeyUp( int key )
	{
		Input::NotifyKeyUp(key);
	}

	virtual void notifyKeyDown( int key )
	{
		Input::NotifyKeyDown(key);
	}

	void setScreen(IScreen::Ptr screen);


	int m_screenWidth, m_screenHeight;

	const int FPS = 60;

	ALLEGRO_DISPLAY* m_display = NULL;
	ALLEGRO_EVENT_QUEUE* m_eventQueue = NULL;
	ALLEGRO_TIMER* m_timer = NULL;

	bool m_redraw = true;
	bool m_doexit = false;

	// current screen
	IScreen::Ptr m_currentScreen;

};

