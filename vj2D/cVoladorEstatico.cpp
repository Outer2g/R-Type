#include "cVoladorEstatico.h"
#include "cScene.h"
#include "Globals.h"

cVoladorEstatico::cVoladorEstatico()
{
	this->health = 100;
}
cVoladorEstatico::~cVoladorEstatico(){}



void cVoladorEstatico::Draw(cData * dat) {
	float xo, yo, xf, yf;
	xo = 0.1796875f * GetFrame(); //cada uno son 46*50 y la imagen es de 256*64
	yo = 0.78125f;
	NextFrame(4);
	//coord textur: xo,yo
	xf = xo + 0.1796875f;//1/8 da el 0.125
	yf = 0.f; //xk la nave ocupa toda la altura d la textura

	DrawRect(dat->GetID(IMG_ESTATIC), xo, yo, xf, yf);
}


void cVoladorEstatico::Stop()
{
	switch(state)
	{
		case STATE_CENTER:	state = STATE_CENTER;		break; //xk si queremos que tire fuego, aqui djara de tirarlo
		default:	state = STATE_CENTER;	break; //aqui en realidad no tendria k ir al centro directamente, tendria k haber
			//una transicion
	}
}

void cVoladorEstatico::Logic(int *map)
{
}