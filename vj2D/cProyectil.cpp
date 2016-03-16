#include "cProyectil.h"
#include "cGame.h"



cProyectil::cProyectil()
{
	this->dmg = 100;
}


cProyectil::~cProyectil()
{
}


void cProyectil::Logic(int * map)
{
	//Whats next tile?
	if ((y % TILE_SIZE) <= 1)
	{
		y += speedY;
		x += speedX;
		//si choca con tile, se autodestruye muy fuerte
		if (CollidesMapWall(map, false)) delete this;
	}
	//Advance, no problem
	else
	{
		y += speedY;
		x += speedX;
		//TODO: si choca, hace magia
	}
}

void cProyectil::Draw(cData * dat)
{

	float xo, yo, xf, yf;
	xo = 0.1796875f * GetFrame(); //cada uno son 46*50 y la imagen es de 256*64
	yo = 0.78125f;
	NextFrame(4);
	//coord textur: xo,yo
	xf = xo + 0.1796875f;//1/8 da el 0.125
	yf = 0.f; //xk la nave ocupa toda la altura d la textura

	DrawRect(dat->GetID(IMG_ESTATIC), xo, yo, xf, yf);
}

void cProyectil::setSpeed(int x, int y)
{
	this->speedX = x;
	this->speedY = y;
}

void cProyectil::getSpeed(int * x, int * y)
{
	*x = this->speedX;
	*y = this->speedY;
}

int cProyectil::getDamage()
{
	return this->dmg;
}
