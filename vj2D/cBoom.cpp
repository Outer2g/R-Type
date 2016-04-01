#include "cBoom.h"



cBoom::cBoom()
{
	boomTime = glutGet(GLUT_ELAPSED_TIME);
}


cBoom::~cBoom()
{
}

void cBoom::Draw(cData * dat)
{
	float xo, yo, xf, yf;
	xo = 0.25f; //cada uno son 46*50 y la imagen es de 256*64
	yo = 0.25f * 3;
	//coord textur: xo,yo
	xf = xo + 0.25f;//1/8 da el 0.125
	yf = yo + 0.25f; //xk la nave ocupa toda la altura d la textura

	DrawRect(dat->GetID(IMG_BUB), xo, yo, xf, yf);
}

double cBoom::getCreationTime()
{
	return boomTime;
}

void cBoom::resetCreationTime()
{
	boomTime = glutGet(GLUT_ELAPSED_TIME);
}