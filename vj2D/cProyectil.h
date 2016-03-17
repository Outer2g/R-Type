#pragma once
#include "cBicho.h"
#include "Globals.h"

//tipos proyectil
#define BULLET_SIMPLE 1
#define BULLET_DOBLE 2
class cProyectil :	public cBicho
{
public:
	cProyectil();
	cProyectil(int id);
	~cProyectil();

	virtual void Logic(int *map);

	virtual void Draw(cData *dat);

	void setSpeed(int x, int y);
	void getSpeed(int* x, int* y);
	void setId(int id);
	int getId();
	int getDamage();
private:
	int dmg;
	int speedX, speedY;
	// id == 1 : player1; id == 2 : player2; id ==3 :enemy
	int id;
};

