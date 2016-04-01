#include "cBoom.h"



cBoom::cBoom()
{
	boomTime = glutGet(GLUT_ELAPSED_TIME);
	this->type = ENEMY_BOOM;
}

cBoom::cBoom(int type)
{
	boomTime = glutGet(GLUT_ELAPSED_TIME);
	this->type = type;
}


cBoom::~cBoom()
{
}

void cBoom::Draw(cData * dat)
{
	float xo, yo, xf, yf;
	xo = 0.2f *GetFrame(); //cada uno son 46*50 y la imagen es de 256*64
	yo = 1.0f;
	NextFrame(5);
	//coord textur: xo,yo
	xf = xo + 0.2f;//1/8 da el 0.125
	yf = 0.f; //xk la nave ocupa toda la altura d la textura

	if (type == ENEMY_BOOM) DrawRect(dat->GetID(IMG_ENEMY_BOOM), xo, yo, xf, yf);
	else DrawRect(dat->GetID(IMG_NAVE_BOOM), xo, yo, xf, yf);
}

void cBoom::NextFrame(int max)
{
		delay++;
		if (delay == 3)
		{
			seq++;
			seq %= max;
			delay = 0;
		}
	
}

double cBoom::getCreationTime()
{
	return boomTime;
}

void cBoom::resetCreationTime()
{
	boomTime = glutGet(GLUT_ELAPSED_TIME);
}

void cBoom::setType(int type)
{
	this->type = type;
}

int cBoom::getType()
{
	return type;
}
