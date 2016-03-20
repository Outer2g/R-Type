#include "cVolador.h"
#include "cScene.h"
#include "Globals.h"

using namespace std;
cVolador::cVolador()
{
	shoot = false;
}
cVolador::~cVolador(){}

/*void cVolador::Draw(){
	float xo, yo, xf, yf;
	xo = 0.125 * 3;
	yo = 1.f;

	xf = xo + 0.125f;//1/8 da el 0.125
	yf = yo - 1.f; //xk la nave ocupa toda la altura d la textura

	DrawRect(tex, xo, yo, xf, yf);
}*/

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

void cVolador::setShoot(bool b)
{
	shoot = b;
}

bool cVolador::getShoot()
{
	return shoot;
}

void cVolador::shootBoi(void* &pewpews, int posx, int posy)
{
	cProyectil* pewpew = new cProyectil(3, 1);
	pewpew->SetWidthHeight(13, 12);
	int speedX = (x - posx + 20);
	int speedY = (y - posy);
	pewpew->setSpeed(-speedX, speedY);
	pewpew->SetPosition(x - this->w, y);
	pewpews = pewpew;
}


