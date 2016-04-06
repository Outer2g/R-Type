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
	if (w >= 32) DrawCirculo1(dat, x+w-32);
	if (w >= 64) DrawCirculo2(dat, x + w - 64);
	if (w >= 96) DrawCirculo3(dat, x + w - 96);
}

inline void cProyectil::DrawCirculo1(cData * dat, int posx)
{
	int xaux = x,waux = w,haux = h,yaux = y; 
	w = 20;
	y -= h / 2;
	h = 40;


	x = posx;
	float xo, yo, xf, yf;
	xo = 0.25f; //cada uno son 13*12, la imagen util 52*12 y la imagen es de 64*16
	yo = 0.15625f;
	if (h < 22 && GetFrame() == 0) ++h;
	//coord textur: xo,yo
	xf = 0.359375f;//1/8 da el 0.125
	yf = 0.53125f; //xk la nave ocupa toda la altura d la textura
	DrawRect(dat->GetID(IMG_BOSS_RAYO), xo, yo, xf, yf);
	x = xaux, w = waux, h = haux, y = yaux;
}

void cProyectil::DrawCirculo2(cData * dat, int posx)
{
	int xaux = x, waux = w, haux = h, yaux = y;
	w = 20;
	y = y - h +3 ;
	h = 60;
	x = posx;
	float xo, yo, xf, yf;
	xo = 0.125f; //cada uno son 13*12, la imagen util 52*12 y la imagen es de 64*16
	yo = 0.09375f;
	if (h < 22 && GetFrame() == 0) ++h;
	//coord textur: xo,yo
	xf = 0.25f;//1/8 da el 0.125
	yf = 0.578125f; //xk la nave ocupa toda la altura d la textura
	DrawRect(dat->GetID(IMG_BOSS_RAYO), xo, yo, xf, yf);
	x = xaux, w = waux, h = haux, y = yaux;
}

void cProyectil::DrawCirculo3(cData * dat, int posx)
{
	int xaux = x, waux = w, haux = h, yaux = y;
	w = 20;
	y = y - h -8;
	h = 80;
	x = posx;
	float xo, yo, xf, yf;
	xo = 0.0f; //cada uno son 13*12, la imagen util 52*12 y la imagen es de 64*16
	yo = 0.0f;
	if (h < 22 && GetFrame() == 0) ++h;
	//coord textur: xo,yo
	xf = 0.125f;//1/8 da el 0.125
	yf = 0.6875f; //xk la nave ocupa toda la altura d la textura
	DrawRect(dat->GetID(IMG_BOSS_RAYO), xo, yo, xf, yf);
	x = xaux, w = waux, h = haux, y = yaux;
}
