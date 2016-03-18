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
		xo = 0.25f; //cada uno son 46*50 y la imagen es de 256*64
		yo = 0.25f*3;
		//coord textur: xo,yo
		xf = xo + 0.25f;//1/8 da el 0.125
		yf = yo + 0.25f; //xk la nave ocupa toda la altura d la textura

		DrawRect(dat->GetID(IMG_BUB), xo, yo, xf, yf);
}

void cPowerUp::setType(int type)
{
	this->type = type;
}

int cPowerUp::getType()
{
	return this->type;
}
