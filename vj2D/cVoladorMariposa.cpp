#include "cVoladorMariposa.h"
#include "cScene.h"
#include "Globals.h"

cVoladorMariposa::cVoladorMariposa(void)
{
	this->health = 100;
	this->speed = 7;
	moveDelay = glutGet(GLUT_ELAPSED_TIME);
	angle = 0;
	srand(time(0));
	double t = glutGet(GLUT_ELAPSED_TIME);
	lastShootDec = t;
	shootChance = 35;
}
cVoladorMariposa::~cVoladorMariposa() {}


void cVoladorMariposa::Draw(cData *dat) {
	float xo, yo, xf, yf;
	xo = 0.08984375f * GetFrame(); //cada uno son 46*50 y la imagen es de 256*64
	yo = 0.71875f;
	NextFrame(6);
	//coord textur: xo,yo
	xf = xo + 0.08984375f;//1/8 da el 0.125
	yf = 0.f; //xk la nave ocupa toda la altura d la textura

	DrawRect(dat->GetID(IMG_MARIP), xo, yo, xf, yf);
}

void cVoladorMariposa::dropPowerup(set<cPowerUp*>& powerups)
{
	cPowerUp* powah = new cPowerUp(POWER_SHIELD);
	powah->SetPosition(x,y);
	powah->SetWidthHeight(32, 32);
	powerups.insert(powah);
}


void cVoladorMariposa::NextFrame(int max)
{
	delay++;
	if (delay == FRAME_DELAY-2)
	{
		seq++;
		seq %= max;
		delay = 0;
	}
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

	if (t1 - lastShootDec > shootChance * 50) {
		int prob = rand();// % 4;
		prob = fmod(prob, 2);
		if (prob == 0) {
			shoot = true;
		}
		else shoot = false;

		lastShootDec = t1;
	}
}
