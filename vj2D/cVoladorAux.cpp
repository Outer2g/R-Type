#include "cVoladorAux.h"



cVoladorAux::cVoladorAux()
{
}


cVoladorAux::~cVoladorAux()
{
}

void cVoladorAux::Draw(int tex_id)
{
	float xo, yo, xf, yf;
	xo = 0.125 * 3;
	yo = 1.f;

	xf = xo + 0.125f;//1/8 da el 0.125
	yf = yo - 1.f; //xk la nave ocupa toda la altura d la textura

	DrawRect(tex_id, xo, yo, xf, yf);
}
