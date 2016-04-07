#include "cHeart.h"





cHeart::cHeart(int id,int pos)
{
	this->id = id;
	this->pos = pos;
	w = 32;
	h = 32;
	x = 40 + pos*w;
	y = 450;
}

cHeart::~cHeart()
{
}

void cHeart::Draw(cData * dat)
{
	float xo, yo, xf, yf;
	xo = 0.0f; //cada uno son 46*50 y la imagen es de 256*64
	yo = 1.0f;
	//coord textur: xo,yo
	xf = 1.f;//1/8 da el 0.125
	yf = 0.f; //xk la nave ocupa toda la altura d la textura

	DrawRect(dat->GetID(IMG_PLAYER_HEARTS), xo, yo, xf, yf);

}
