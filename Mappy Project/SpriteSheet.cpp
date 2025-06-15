#include "SpriteSheet.h"

Sprite::Sprite()
{
	image=NULL;
}
Sprite::~Sprite()
{
	al_destroy_bitmap(image);
}
void Sprite::InitSprites(int width, int height)
{
	x = 30;
	y = 80;


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

void Sprite::UpdateSprites(int width, int height, int dir)
{
	int oldx = x;
	int oldy = y;

	if(dir == 1){ //right key
		animationDirection = 1;
		animationRows = 2;
		x+=2; 
		if (++frameCount > frameDelay)
		{
			frameCount=0;
			if (++curFrame > 11)
				curFrame=8;
		}
	} else if (dir == 0){ //left key
		animationDirection = 0; 
		animationRows = 1;
		x-=2; 
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
		y += 2;
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
		y -= 2;
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
		if (collided(x + frameWidth/3, y + frameHeight)) { //collision detection to the left
			x = oldx; 
			y= oldy;
		}

	}
	else if (animationDirection ==1)
	{ 
		if (collided(x + frameWidth - (frameWidth/3), y + frameHeight)) { //collision detection to the right
			x = oldx; 
			y= oldy;
		}
	}
	else if (animationDirection == 2) {
		if (collided(x + frameWidth / 2, y + frameHeight)) {
			x = oldx;
			y = oldy;
		}
	}
	else if (animationDirection == 3) {
		if (collided(x + frameWidth / 2, y)) {
			x = oldx;
			y = oldy;
		}
	}
}

bool Sprite::CollisionEndBlock()
{
	if (endValue(x + frameWidth/2, y + frameHeight + 5))
		return true;
	else
		return false;
}

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