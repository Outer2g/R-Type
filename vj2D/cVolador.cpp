#include "cVolador.h"
#include "cScene.h"
#include "Globals.h"

cVolador::cVolador(void)
{
	seq=0;
	delay=0;

}
cVolador::~cVolador(void){}

cVolador::cVolador(int posx,int posy,int width,int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
}

void cVolador::Draw(int texId){}

void cVolador::MoveLeft(int *map)
{
	int xaux;
	
	//Whats next tile?
	if( (x % TILE_SIZE) <= 1)
	{
		xaux = x;
		x -= STEP_LENGTH;

		if(CollidesMapWall(map,false))
		{
			x = xaux;
			state = STATE_CENTER;
		}
	}
	//Advance, no problem
	else
	{
		x -= STEP_LENGTH - STEP_LENGTH;
		if(state != STATE_CENTER)
		{
			state = STATE_CENTER;
			seq = 0;
			delay = 0;
		}
	}
}
void cVolador::MoveDown(int * map)
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
		y -= STEP_LENGTH;
		if (state != STATE_CENTER)
		{
			state = STATE_CENTER;
			seq = 0;
			delay = 0;
		}
	}
}
void cVolador::MoveRight(int *map)
{
	int xaux;

	//Whats next tile?
	if( (x % TILE_SIZE) <= 1)
	{
		xaux = x;
		x += STEP_LENGTH;

		if(CollidesMapWall(map,true))
		{
			x = xaux;
			state = STATE_CENTER;
		}
	}
	//Advance, no problem
	else
	{
		x += STEP_LENGTH;

		if(state != STATE_CENTER)
		{
			state = STATE_CENTER;
			seq = 0;
			delay = 0;
		}
	}
}

void cVolador::Stop()
{
	switch(state)
	{
		case STATE_CENTER:	state = STATE_CENTER;		break; //xk si queremos que tire fuego, aqui djara de tirarlo
		default:	state = STATE_CENTER;	break; //aqui en realidad no tendria k ir al centro directamente, tendria k haber
			//una transicion
	}
}
void cVolador::Jump(int *map)
{
	//copy paste from move LEFT swapping from x to y
	int xaux;

	//Whats next tile?
	if ((y % TILE_SIZE) == 0)
	{
		xaux = y;
		y += STEP_LENGTH;

		if (CollidesMapWall(map, false))
		{
			y = xaux;
			state = STATE_CENTER;
		}
	}
	//Advance, no problem
	else
	{
		y += STEP_LENGTH;
		if (state != STATE_CENTER)
		{
			state = STATE_CENTER;
			seq = 0;
			delay = 0;
		}
	}

}
void cVolador::Logic(int *map)
{
}
void cVolador::NextFrame(int max)
{
	delay++;
	if(delay == FRAME_DELAY)
	{
		seq++;
		seq%=max;
		delay = 0;
	}
}
int cVolador::GetFrame()
{
	return seq;
}
int cVolador::GetState()
{
	return state;
}
void cVolador::SetState(int s)
{
	state = s;
}