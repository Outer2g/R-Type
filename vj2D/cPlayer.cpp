
#include "cPlayer.h"
#include "cScene.h"

cPlayer::cPlayer() {
	moving = false;
}
cPlayer::~cPlayer(){}

void cPlayer::Draw(int tex_id)
{	
	float xo,yo,xf,yf;
	xo = 0.125 * GetState();
	yo = 1.f;
	/*switch(GetState())
	{
		//1
		case STATE_CENTER:		xo = 0.5f; //SI METEMOS ANIMACION A LA NAVE, LA PONEMOS DEBAJO Y CAMBIAMOS EL 1
								break;
		case STATE_DOWN_FAST: xo = 0.125f; break;
		//4
		case STATE_LOOKRIGHT:	xo = 0.25f;	yo = 1.f;
								break;
		//1..3
		case STATE_WALKLEFT:	xo = 0.0f;	yo = 1.f; // PARA ANIMACION: + (GetFrame()*0.25f);
								//NextFrame(3);
								break;
		//4..6
		case STATE_WALKRIGHT:	xo = 0.25f; yo = 1.f;// +(GetFrame()*0.25f);
								//NextFrame(3);
								break;
	}*/
	//coord textur: xo,yo
	xf = xo + 0.125f;//1/8 da el 0.125
	yf = yo - 1.f; //xk la nave ocupa toda la altura d la textura

	DrawRect(tex_id,xo,yo,xf,yf);
}



void cPlayer::MoveDown(int * map)
{
	//copy paste from move jump(copypasted from moveLeft) swapping from x to y
	int xaux;

	//Whats next tile?
	if ((y % TILE_SIZE) <= 1)
	{
		xaux = y;
		y -= STEP_LENGTH;

		if (CollidesMapWall(map, false))
		{
			y = xaux;
			state = STATE_CENTER;
		}
	}
	//Advance, no problem
	else
	{
		y -= STEP_LENGTH + STEP_LENGTH/2;
		state = STATE_DOWN_FAST;
		moving = true;
		if (state != STATE_CENTER)
		{
			state = STATE_DOWN_FAST;
			seq = 0;
			delay = 5;
		}
	}
}
void cPlayer::MoveLeft(int *map)
{
	int xaux;

	//Whats next tile?
	if ((x % TILE_SIZE) <= 1)
	{
		xaux = x;
		x -= STEP_LENGTH + STEP_LENGTH;

		if (CollidesMapWall(map, true))
		{
			x = xaux;
		}
	}
	//Advance, no problem
	else
	{
		x -= STEP_LENGTH + STEP_LENGTH;
		if (!moving) state = STATE_CENTER;
		if (state != STATE_CENTER)
		{
			seq = 0;
			delay = 0;
		}
	}
}

void cPlayer::MoveRight(int *map)
{
	int xaux;

	//Whats next tile?
	if ((x % TILE_SIZE) <= 1)
	{
		xaux = x;
		x += STEP_LENGTH;

		if (CollidesMapWall(map, true))
		{
			x = xaux;
			state = STATE_CENTER;
		}
	}
	//Advance, no problem
	else
	{
		x += STEP_LENGTH;
		if(!moving) state = STATE_CENTER;
		if (state != STATE_CENTER)
		{
			seq = 0;
			delay = 0;
		}
	}
}
void cPlayer::Jump(int *map)
{
	//copy paste from move LEFT swapping from x to y
	int xaux;

	//Whats next tile?
	if ((y % TILE_SIZE) == 0)
	{
		xaux = y;
		y += STEP_LENGTH + STEP_LENGTH/2;

		if (CollidesMapWall(map,false))
		{
			y = xaux;
			state = STATE_CENTER;
		}
	}
	//Advance, no problem
	else
	{
		y += STEP_LENGTH + STEP_LENGTH / 2;
		state = STATE_UP_FAST;
		moving = true;
		if (state != STATE_CENTER)
		{
			seq = 0;
			delay = 0;
		}
	}

}
void cPlayer::Stop()
{
	moving = false;
	state = STATE_CENTER;
}
void cPlayer::Logic(int * map)
{
	 this->MoveHalfRight(map);
}

void cPlayer::setMoving(bool b)
{
	this->moving = b;
}

bool cPlayer::getMoving()
{
	return this->moving;
}
