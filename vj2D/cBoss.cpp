#include "cBoss.h"



cBoss::cBoss()
{
	lastSpecial = glutGet(GLUT_ELAPSED_TIME);
	delaySpecial = 200;
	srand(time(0));
}


cBoss::~cBoss()
{
}

void cBoss::draw(cData * dat)
{
	float xo, yo, xf, yf;
	xo = 0.25f; //cada uno son 46*50 y la imagen es de 256*64
	yo = 0.25f * 3;
	//coord textur: xo,yo
	xf = xo + 0.25f;//1/8 da el 0.125
	yf = yo + 0.25f; //xk la nave ocupa toda la altura d la textura

	DrawRect(dat->GetID(IMG_BUB), xo, yo, xf, yf);
}

void cBoss::attackBasic(set<cProyectil*>& pewpews, cPlayer * Player)
{
	//Shoot for default
	int tx, ty; Player->GetPosition(&tx,&ty);
	shootBoi(pewpews,tx,ty);
}

void cBoss::attackSpecial(set<cProyectil*>& pewpews)
{
	//Rayo magico de la muerte
	lastSpecial = glutGet(GLUT_ELAPSED_TIME);
}

void cBoss::shootSomething(set<cProyectil*>& pewpews, cPlayer * Player)
{
	//decide cuando dispara
	double t1 = glutGet(GLUT_ELAPSED_TIME);
	bool canSpecial = false;
	if (t1 - lastSpecial > 20 * delaySpecial) canSpecial = true;
	int r = rand();
	if (r % 4 == 0) attackSpecial(pewpews);
	else attackBasic(pewpews, Player);
}
