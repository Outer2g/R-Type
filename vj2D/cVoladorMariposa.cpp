#include "cVoladorMariposa.h"
#include "cScene.h"
#include "Globals.h"

cVoladorMariposa::cVoladorMariposa(void)
{
}
cVoladorMariposa::~cVoladorMariposa() {}


void cVoladorMariposa::Draw(cData *dat) {
	float xo, yo, xf, yf;
	xo = 0.125 * GetState();
	yo = 1.f;
	//coord textur: xo,yo
	xf = xo + 0.125f;//1/8 da el 0.125
	yf = yo - 1.f; //xk la nave ocupa toda la altura d la textura

	DrawRect(dat->GetID(IMG_MARIP), xo, yo, xf, yf);
}


void cVoladorMariposa::Stop()
{
	switch(state)
	{
		case STATE_CENTER:	state = STATE_CENTER;		break; //xk si queremos que tire fuego, aqui djara de tirarlo
		default:	state = STATE_CENTER;	break; //aqui en realidad no tendria k ir al centro directamente, tendria k haber
			//una transicion
	}
}

void cVoladorMariposa::Logic(int *map)
{
}
