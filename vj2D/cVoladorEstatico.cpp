#include "cVoladorEstatico.h"
#include "cScene.h"
#include "Globals.h"

cVoladorEstatico::cVoladorEstatico(void)
{
	seq=0;
	delay=0;
}
cVoladorEstatico::~cVoladorEstatico(void){}

cVoladorEstatico::cVoladorEstatico(int posx,int posy,int width,int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
}


void cVoladorEstatico::Draw(int texId) {
	float xo, yo, xf, yf;
	xo = 0.1796875f * GetFrame(); //cada uno son 46*50 y la imagen es de 256*64
	yo = 0.78125f;
	NextFrame(4);
	/*switch(GetState())
	{
	//1
	case STATE_CENTER:		xo = 0.5f; //SI METEMOS ANIMACION A LA NAVE, LA PONEMOS DEBAJO Y CAMBIAMOS EL 1
	break;
	case STATE_DOWN_FAST: xo = 0.125f; break;
	//4
	case STATE_LOOKRIGHT:	xo = 0.25f;	yo = 1.f;
	break;
	//1..3
	case STATE_WALKLEFT:	xo = 0.0f;	yo = 1.f; // PARA ANIMACION: + (GetFrame()*0.25f);
	//NextFrame(3);
	break;
	//4..6
	case STATE_WALKRIGHT:	xo = 0.25f; yo = 1.f;// +(GetFrame()*0.25f);
	//NextFrame(3);
	break;
	}*/
	//coord textur: xo,yo
	xf = xo + 0.1796875f;//1/8 da el 0.125
	yf = 0.f; //xk la nave ocupa toda la altura d la textura

	DrawRect(texId, xo, yo, xf, yf);
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

void cVoladorEstatico::NextFrame(int max)
{
	delay++;
	if(delay == FRAME_DELAY)
	{
		seq++;
		seq%=max;
		delay = 0;
	}
}
int cVoladorEstatico::GetFrame()
{
	return seq;
}
int cVoladorEstatico::GetState()
{
	return state;
}
void cVoladorEstatico::SetState(int s)
{
	state = s;
}