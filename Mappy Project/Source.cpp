//Alexander Young
//Maze Game

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "SpriteSheet.h"
#include "mappy_A5.h"
#include <iostream>
using namespace std;

int collided(int x, int y);  //Tile Collision
bool endValue( int x, int y ); //End Block with the User Value = 8

int main(void)
{
	const int WIDTH = 900;
	const int HEIGHT = 480;
	bool keys[] = {false, false, false, false, false};
	enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
	//variables
	bool done = false;
	bool render = false;
	//controller variable for the map
	int count = 0;
	//variable for the time remaining to be printed
	int countdown = 60;
	//Player Variable
	Sprite player;



	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;

	//program init
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if(!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	ALLEGRO_FONT* font = al_load_font("Movistar Text Regular.ttf", 64, 0);
	player.InitSprites(WIDTH,HEIGHT);

	int xOff = 0;
	int yOff = 0;
	if(MapLoad("test.FMP", 1))
		return -5;

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_start_timer(timer);

	//draw the background tiles
	MapDrawBG(xOff,yOff, 0, 0, WIDTH-1, HEIGHT-1);

	//draw foreground tiles
	MapDrawFG(xOff,yOff, 0, 0, WIDTH-1, HEIGHT-1, 0);
	player.DrawSprites(0,0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	while(!done)
	{
		//If the countdown reaches zero, the game ends after a message
		if (countdown == 0) {
			MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);
			MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);
			al_draw_text(font, al_map_rgb(255, 255, 0), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Time is up!");
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_rest(5);
			done = true;
		}
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;
			if (keys[UP])
				player.UpdateSprites(WIDTH, HEIGHT, 3);
			else if (keys[DOWN])
				player.UpdateSprites(WIDTH, HEIGHT, 2);
			else if(keys[LEFT])
				player.UpdateSprites(WIDTH,HEIGHT,0);
			else if(keys[RIGHT])
				player.UpdateSprites(WIDTH,HEIGHT,1);
			else
				player.UpdateSprites(WIDTH,HEIGHT,4);
			//If player touches an endblock, reset the timer and load the next map in the sequence. If it is the last map, show the winning screen
			if (player.CollisionEndBlock()) {
				if (count == 0) {
					al_stop_timer(timer);
					al_set_timer_count(timer, 0);
					countdown = 60;
					al_start_timer(timer);
					MapLoad("test2.FMP", 1);
					MapDrawBG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1);
					MapDrawFG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1, 0);
					player.setX(40);
					player.setY(120);
					player.DrawSprites(0, 0);
					al_flip_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));
					count++;
				}
				else if (count == 1) {
					al_stop_timer(timer);
					al_set_timer_count(timer, 0);
					countdown = 60;
					al_start_timer(timer);
					MapLoad("test3.FMP", 1);
					MapDrawBG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1);
					MapDrawFG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1, 0);
					player.setX(40);
					player.setY(120);
					player.DrawSprites(0, 0);
					al_flip_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));
					count++;
				}
				else if (count == 2 && player.CollisionEndBlock()) {
					MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);
					MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);
					al_draw_text(font, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "You win!");
					al_flip_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_rest(5);
					done = true;
				}
			}
			//Decrement countdown every second
			if (al_get_timer_count(timer) % 60 == 0) {
				countdown--;
			}
			render = true;

		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}
		if(render && al_is_event_queue_empty(event_queue))
		{
			render = false;

			//update the map scroll position
			xOff = player.getX()+player.getWidth() - WIDTH/2 ;
			yOff = player.getY()+player.getHeight()   - HEIGHT/2 ;

			//avoid moving beyond the map edge
			if (xOff < 0) xOff = 0;

			if (xOff > (mapwidth * mapblockwidth - WIDTH))
				xOff = mapwidth * mapblockwidth - WIDTH;
			if (yOff < 0) 
				yOff = 0;
			if (yOff > (mapheight * mapblockheight - HEIGHT)) 
				yOff = mapheight * mapblockheight - HEIGHT;

			//draw the background tiles
			MapDrawBG(xOff,yOff, 0, 0, WIDTH, HEIGHT);

			//draw foreground tiles
			MapDrawFG(xOff,yOff, 0, 0, WIDTH, HEIGHT, 0);
			player.DrawSprites(xOff, yOff);
			MapUpdateAnims();
			al_draw_textf(font, al_map_rgb(255, 255, 0), 0, 0, 0, "%i", countdown);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	MapFreeMem();
	al_destroy_font(font);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}



int collided(int x, int y)
{
	BLKSTR *blockdata;
	blockdata = MapGetBlock(x/mapblockwidth, y/mapblockheight);
	return blockdata->tl;
}

bool endValue( int x, int y )
{

	BLKSTR* data;
	data = MapGetBlock( x/mapblockwidth, y/mapblockheight );

	if( data->user1 == 8 )
	{
		return true;
	}else
		return false;
}