
#include "cPlayer.h"

cPlayer::cPlayer() {}
cPlayer::~cPlayer(){}

void cPlayer::Draw(int tex_id)
{	
	float xo,yo,xf,yf;
	xo = 0.125 * GetState();
	yo = 1.f;
	/*switch(GetState())
	{
		//1
		case STATE_CENTER:		xo = 0.0f;	yo = 1.f; //SI METEMOS ANIMACION A LA NAVE, LA PONEMOS DEBAJO Y CAMBIAMOS EL 1
								break;
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
	xf = xo + 0.125f;//1/8 da el 0.125
	yf = yo - 1.f; //xk la nave ocupa toda la altura d la textura

	DrawRect(tex_id,xo,yo,xf,yf);
}
