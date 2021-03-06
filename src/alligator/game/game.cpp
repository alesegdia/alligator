#include <stdio.h>

#include "game.h"


#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <alligator/util/rng.h>

Game::Game( int screen_width, int screen_height )
	: m_screenWidth(screen_width), m_screenHeight(screen_height)
{

}

Game::~Game()
{

}

int Game::init(int argc, char** argv) {
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
		return -1;
	}

	if(!al_init_image_addon()) {
		fprintf(stderr, "failed to initialize image addon!\n");
		return -1;
	}

	if(!al_init_primitives_addon()) {
		fprintf(stderr, "failed to initialize primitives addon!\n");
		return -1;
	}

	if(!al_init_acodec_addon()) {
	   fprintf(stderr, "failed to initialize audio codecs!\n");
	   return -1;
	}

	if(!al_install_audio()) {
		fprintf(stderr, "failed to initialize audio!\n");
		return -1;
	}

	al_init_font_addon();

	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to initialize ttf addon!\n");
		return -1;
	}

	m_display = al_create_display(m_screenWidth, m_screenHeight);
	if(!m_display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	al_clear_to_color(al_map_rgb(255, 0, 255));
	al_set_target_bitmap(al_get_backbuffer(m_display));

	m_eventQueue = al_create_event_queue();
	if(!m_eventQueue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(m_display);
		return -1;
	}

	if (!al_reserve_samples(3)){
	   fprintf(stderr, "failed to reserve samples!\n");
	   return -1;
	}

    al_register_event_source(m_eventQueue, al_get_display_event_source(m_display));
	al_register_event_source(m_eventQueue, al_get_keyboard_event_source());
	al_register_event_source(m_eventQueue, al_get_mouse_event_source());

	al_clear_to_color(al_map_rgb(0,0,0));

	al_set_target_bitmap(al_get_backbuffer(m_display));

    al_set_new_display_option(ALLEGRO_VSYNC, 2, 1000);

	RNG::Initialize(time(NULL));
	Input::Initialize();

	uint32_t version = al_get_allegro_version();
	int major = version >> 24;
	int minor = (version >> 16) & 255;
	int revision = (version >> 8) & 255;
	int release = version & 255;
	printf("Allegro %d.%d.%d.%d\n", major, minor, revision, release);


	return create(argc, argv);
}

void Game::handleEvent(ALLEGRO_EVENT& ev)
{
    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	{
		m_doexit = true;
	}
	else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		this->notifyKeyDown(ev.keyboard.keycode);
	}
	else if(ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		this->notifyKeyUp(ev.keyboard.keycode);
	}
	else if( ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN )
	{
		this->notifyMouseButtonDown(ev.mouse.button);
	}
}

void Game::render()
{
	m_currentScreen->render();
}

void Game::update(double delta)
{
	m_currentScreen->update(delta);
}

void Game::notifyKeyUp(int key)
{
	Input::NotifyKeyUp(key);
}

void Game::notifyKeyDown(int key)
{
	Input::NotifyKeyDown(key);
}

void Game::notifyMouseButtonDown(int button)
{
	Input::NotifyMouseButtonDown(button);
}

void Game::grabMouse()
{
	al_grab_mouse(m_display);
}

void Game::ungrabMouse()
{
	al_ungrab_mouse();
}

void Game::setScreen(IScreen::Ptr screen)
{
	if( m_currentScreen != nullptr )
	{
		m_currentScreen->hide();
	}

	m_currentScreen = screen;
	m_currentScreen->show();
}

void Game::setUpdateFPS(int fps)
{
    m_updateFPS = 1.0 / double(fps);
}

void Game::setRenderFPS(int fps)
{
    m_renderFPS = 1.0 / double(fps);
}

void Game::close()
{
    m_doexit = true;
}

ALLEGRO_DISPLAY *Game::display()
{
    return m_display;
}

int Game::exec(int argc, char** argv) {
	int retcode = init(argc, argv);
	if( retcode != 0 ) return retcode;

	double now, then;
	now = then = al_get_time();
    double accum[2] = { 0, 0 };
    double title_accum = 0;

    int current_fps = 0 ;

	while(!m_doexit) {

		ALLEGRO_EVENT ev;
		while( al_get_next_event(m_eventQueue, &ev) )
		{
			handleEvent(ev);
		}

		now = al_get_time();
		double delta = now - then;

        accum[0] += delta;
        accum[1] += delta;

		then = now;

        if( m_showTitleFPS )
        {
            title_accum += delta;
            current_fps++;
            if( title_accum >= 1 ) {
                title_accum = 0;
                current_fps = 0;
                char buffer[16];
                sprintf_s(buffer, "%.6f", 1.0 / delta);
                al_set_window_title(m_display, buffer);
            }
        }

        // render
        if( accum[0] > m_renderFPS )
		{
            accum[0] -= m_renderFPS;
			al_set_target_bitmap(al_get_backbuffer(m_display));
			render();
			al_flip_display();
		}

        // update
        while( accum[1] > m_updateFPS )
        {
            accum[1] -= m_updateFPS;
            Input::PreUpdate();
            update(m_updateFPS);
            //std::cout << "update delta: " << m_updateFPS << std::endl;
            Input::Update();
        }
	}

	dispose();
	Input::Dispose();

	al_destroy_display(m_display);
	al_shutdown_image_addon();
	al_shutdown_primitives_addon();
	al_shutdown_ttf_addon();
	al_shutdown_font_addon();
	al_uninstall_audio();
	al_uninstall_keyboard();
	al_uninstall_mouse();

	return 0;

}


