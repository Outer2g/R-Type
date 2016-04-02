#include "cPowerUp.h"



cPowerUp::cPowerUp()
{
	this->type = BULLET_DOBLE;
}

cPowerUp::cPowerUp(int type)
{
	this->type = type;
}


cPowerUp::~cPowerUp()
{
}

void cPowerUp::Draw(cData * dat)
{

	float xo, yo, xf, yf;
	xo = 0.25f *GetFrame(); //cada uno son 46*50 y la imagen es de 256*64
	yo = 1.0f;
	NextFrame(4);
	//coord textur: xo,yo
	xf = xo + 0.25f;//1/8 da el 0.125
	yf = 0.f; //xk la nave ocupa toda la altura d la textura

	if (type == POWER_SHIELD) DrawRect(dat->GetID(IMG_SHIELD_POWER), xo, yo, xf, yf);
	else if(type == BULLET_DOBLE) DrawRect(dat->GetID(IMG_BULLET_POWER), xo, yo, xf, yf);
}

void cPowerUp::setType(int type)
{
	this->type = type;
}

int cPowerUp::getType()
{
	return this->type;
}
