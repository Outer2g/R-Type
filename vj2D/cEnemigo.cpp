#include "cEnemigo.h"



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

void cEnemigo::shootBoi(set<cProyectil*>& pewpews, int posx, int posy)
{
		cProyectil* pewpew = new cProyectil(3, 1);
		pewpew->SetWidthHeight(13, 12);
		int speedX = (x - posx + 20);
		int speedY = (y - posy);
		pewpew->setSpeed(-3, speedY);
		pewpew->SetPosition(x - this->w, y);
		pewpews.insert(pewpew);
}
