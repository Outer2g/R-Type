#include "cProyectil.h"
#include "cGame.h"



cProyectil::cProyectil()
{
	this->dmg = 100;
}

cProyectil::cProyectil(int id, int tipo)
{
	this->id = id;
	this->dmg = 100;
	this->tipo = tipo;
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
	if (id == 3 && tipo != RAYO_BOSS) DrawPEnemigo(dat);
	else if (tipo == RAYO_BOSS) DrawRayo(dat);
	else DrawPNave(dat);
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

void cProyectil::setId(int id)
{
	this->id = id;
}

int cProyectil::getId()
{
	return this->id;
}

int cProyectil::getDamage()
{
	return this->dmg;
}

int cProyectil::getType()
{
	return tipo;
}

void cProyectil::setType(int tipo)
{
	this->tipo = tipo;
}

inline void cProyectil::DrawPEnemigo(cData * dat)
{
	float xo, yo, xf, yf;
	xo = 0.203125f * GetFrame(); //cada uno son 13*12, la imagen util 52*12 y la imagen es de 64*16
	yo = 1.f;
	NextFrame(4);
	//coord textur: xo,yo
	xf = xo + 0.203125f;//1/8 da el 0.125
	yf = 0.f; //xk la nave ocupa toda la altura d la textura
	DrawRect(dat->GetID(IMG_BULLET_VOLADOR), xo, yo, xf, yf);

}

inline void cProyectil::DrawPNave(cData * dat)
{
	float xo, yo, xf, yf;
	xo = 0.0141509433962264f; //cada uno son 46*50 y la imagen es de 256*64
	yo = 1.0f;
	//coord textur: xo,yo
	xf = xo + 0.0377358490566038f;//1/8 da el 0.125
	yf = 0.f; //xk la nave ocupa toda la altura d la textura

	DrawRect(dat->GetID(IMG_PLAYER_BULLETS), xo, yo, xf, yf);
}

inline void cProyectil::DrawRayo(cData * dat)
{
	float xo, yo, xf, yf;
	xo = 0.375f; //cada uno son 13*12, la imagen util 52*12 y la imagen es de 64*16
	yo = 0.f + GetFrame()* 0.09375f;
	if (h < 22 && GetFrame() == 0) ++h;
	w += 10;
	NextFrame(2);
	//coord textur: xo,yo
	xf = xo + 0.21875f;//1/8 da el 0.125
	yf = yo + 0.09375; //xk la nave ocupa toda la altura d la textura
	DrawRect(dat->GetID(IMG_BOSS_RAYO), xo, yo, xf, yf);
}
