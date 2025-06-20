//Alexander Young
//Maze Game
#include "SpriteSheet.h"

//This is a constructor for the Sprite class
//Takes no parameters
//No return
Sprite::Sprite()
{
	image=NULL;
}

//This is a deconstructor for the sprite class
//Takes no parameters
//No return
Sprite::~Sprite()
{
	al_destroy_bitmap(image);
}

//This function spawns the sprite in the display
//Takes two integers representing the display width and height
//No return
void Sprite::InitSprites(int width, int height)
{
	x = 40;
	y = 120;


	maxFrame = 4;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 64;
	frameHeight = 64;
	animationColumns = 4;
	animationRows = 4;
	animationDirection = 1;

	image = al_load_bitmap("guy2.png");
	al_convert_mask_to_alpha(image, al_map_rgb(255,0,255));
}

//Setter for the x variable
//Takes a float as a parameter
//No return
void Sprite::setX(float f) {
	x = f;
}

//Setter for the y variable
//Takes a float as a parameter
//No return
void Sprite::setY(float f) {
	y = f;
}

//This function updates a sprite's location and animation sequence on a screen
//Takes two integers representing the display width and height and an integer representing the direction
//No return
void Sprite::UpdateSprites(int width, int height, int dir)
{
	int oldx = x;
	int oldy = y;

	if(dir == 1){ //right key
		animationDirection = 1;
		animationRows = 2;
		x+=4; 
		if (++frameCount > frameDelay)
		{
			frameCount=0;
			if (++curFrame > 11)
				curFrame=8;
		}
	} else if (dir == 0){ //left key
		animationDirection = 0; 
		animationRows = 1;
		x-=4; 
		if (++frameCount > frameDelay)
		{
			frameCount=0;
			if (++curFrame > 7)
				curFrame=4;
		}
	}
	else if (dir == 2) { //Down key
		animationDirection = 2;
		animationRows = 0;
		y += 4;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > 3)
				curFrame = 0;
		}
	}
	else if (dir == 3) {
		animationDirection = 3;
		animationRows = 3;
		y -= 4;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > 15)
				curFrame = 12;
		}
	}
	else {
		animationDirection = dir;
	}
	//check for collided with foreground tiles
	if (animationDirection==0)
	{ 
		if (collided(x + frameWidth/2, y + frameHeight)) { //collision detection to the left
			x = oldx; 
			y= oldy;
		}

	}
	else if (animationDirection ==1)
	{ 
		if (collided(x + frameWidth/2, y + frameHeight)) { //collision detection to the right
			x = oldx; 
			y= oldy;
		}
	}
	else if (animationDirection == 2) {
		if (collided(x + frameHeight/2, y + frameHeight)) {
			x = oldx;
			y = oldy;
		}
	}
	else if (animationDirection == 3) {
		if (collided(x + frameHeight/2, y)) {
			x = oldx;
			y = oldy;
		}
	}
}

//This function detects if a sprite collides with an endblock
//Takes no parameters
//Returns a boolean
bool Sprite::CollisionEndBlock()
{
	if (endValue(x + frameWidth , y + frameHeight/2))
		return true;
	else
		return false;
}

//This function draws a sprite at the x and y position on the display at the current animaton sequence
//Takes two integers representing the x and y offset
//No return
void Sprite::DrawSprites(int xoffset, int yoffset)
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = animationRows * frameHeight;

	if (animationDirection==1){
		al_draw_bitmap_region(image, fx, fy, frameWidth,frameHeight, x-xoffset, y-yoffset, 0);
	}
	else if (animationDirection == 0 ){
		al_draw_bitmap_region(image, fx, fy, frameWidth,frameHeight, x-xoffset, y-yoffset, 0);
	}
	else if (animationDirection == 2 ) {
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
	else if (animationDirection == 3 ) {
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
	else if (animationDirection == 4 ){
		al_draw_bitmap_region(image,0,0,frameWidth,frameHeight,  x-xoffset, y-yoffset, 0);

	}
}