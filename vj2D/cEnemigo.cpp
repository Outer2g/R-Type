#include "cEnemigo.h"
#include <math.h>



cEnemigo::cEnemigo()
{
	health = 300;
	this->lastShootTime = glutGet(GLUT_ELAPSED_TIME);
	this->delayShoot = 40;
	shoot = false;
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
	//double t1 = glutGet(GLUT_ELAPSED_TIME);
	//if (t1 - lastShootTime > 20 * delayShoot) {
		cProyectil* pewpew = new cProyectil(3, 1);
		pewpew->SetWidthHeight(13, 12);
		float Ax = -(x - (posxNave+ w * 2));
		float Ay = -(y - posyNave);
		float maxim = max(abs(Ax), abs(Ay));
		if (maxim > 0) {
			pewpew->setSpeed((Ax / maxim * 2), (Ay / maxim * 2));
			pewpew->SetPosition(x, y+h/2);
			pewpews.insert(pewpew);
		}
		shoot = false;
		//lastShootTime = glutGet(GLUT_ELAPSED_TIME);
	//}
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

bool cEnemigo::getShootable()
{
	return shoot;
}

void cEnemigo::dropPowerup(set<cPowerUp*>& powerups)
{

}


