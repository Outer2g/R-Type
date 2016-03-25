#include "cVoladorMariposa.h"
#include "cScene.h"
#include "Globals.h"

cVoladorMariposa::cVoladorMariposa(void)
{
	this->health = 100;
	this->speed = 7;
	moveDelay = glutGet(GLUT_ELAPSED_TIME);
	angle = 0;
}
cVoladorMariposa::~cVoladorMariposa() {}


void cVoladorMariposa::Draw(cData *dat) {
	float xo, yo, xf, yf;
	xo = 0.1796875f * GetFrame(); //cada uno son 46*50 y la imagen es de 256*64
	yo = 0.78125f;
	NextFrame(4);
	//coord textur: xo,yo
	xf = xo + 0.1796875f;//1/8 da el 0.125
	yf = 0.f; //xk la nave ocupa toda la altura d la textura

	DrawRect(dat->GetID(IMG_ESTATIC), xo, yo, xf, yf);
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
	double t1 = glutGet(GLUT_ELAPSED_TIME);
	if (t1 - moveDelay > 20) {
		int aux = y;
		y += sin(angle) * 4;//30 grados
		angle += 0.1;
		x -= STEP_LENGTH+1;

		//Whats next tile?
		if ((y % TILE_SIZE) <= 1)
		{

			/*y += speedY;
			x += speedX;*/
			//si choca con tile, se autodestruye muy fuerte
			if (CollidesMapWall(map, false)) y = aux; //delete this;
		}
		//Advance, no problem
		else
		{
			/*y += speedY;
			x += speedX;*/
			//TODO: si choca, hace magia
		}
		moveDelay = t1;
	}

	int prob = rand() % 4;
	if (prob == 0) {
		shoot = true;
	}
	else shoot = false;
}
