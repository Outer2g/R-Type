#include "cEnemigo.h"
#include <math.h>



cEnemigo::cEnemigo()
{
}


cEnemigo::~cEnemigo()
{
}

void cEnemigo::MoveRight(int * map)
{
}

void cEnemigo::MoveLeft(int * map)
{
}

void cEnemigo::MoveDown(int * map)
{
}

void cEnemigo::Jump(int * map)
{
}

void cEnemigo::Stop()
{
}

void cEnemigo::Logic(int * map)
{
}

void cEnemigo::shootBoi(set<cProyectil*>& pewpews, int posxNave, int posyNave)
{
	cProyectil* pewpew = new cProyectil(3,1);
	pewpew->SetWidthHeight(13, 12);
	int Ax = -(x - posxNave);
	int Ay = y - posyNave;
	int maxim = max(Ax, Ay);
	if (maxim > 0) {
		pewpew->setSpeed((Ax / maxim * 3), (Ay / maxim * 3));
		pewpew->SetPosition(x - this->w, y);
		pewpews.insert(pewpew);
	}
	/*FORMA XULA DE DISPARAR
	pewpew->SetWidthHeight(13, 12);
	int a = x - posx;
	int z = y - posy;
	if (z!=0) {
		double angle = atan(a / z);
		double angle2 = atan(z / a);
		pewpew->setSpeed(3*cos(angle2), 3*sin(angle2));
	}
	else {
		pewpew->setSpeed(3, 0);
	}
	pewpew->SetPosition(x - this->w, y);
	pewpews.insert(pewpew);*/
}

void cEnemigo::setShootChance(int shootingChance)
{
}

int cEnemigo::getShootChance()
{
	return 0;
}
