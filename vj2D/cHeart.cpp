#include "cHeart.h"





cHeart::cHeart(int id,int pos)
{
	this->id = id;
	this->pos = pos;

}

cHeart::~cHeart()
{
}

void cHeart::Draw(cData * dat)
{
	float xo, yo, xf, yf;
	xo = 0.2f *GetFrame(); //cada uno son 46*50 y la imagen es de 256*64
	yo = 1.0f;
	NextFrame(5);
	//coord textur: xo,yo
	xf = xo + 0.2f;//1/8 da el 0.125
	yf = 0.f; //xk la nave ocupa toda la altura d la textura

	DrawRect(dat->GetID(IMG_ENEMY_BOOM), xo, yo, xf, yf);

}
