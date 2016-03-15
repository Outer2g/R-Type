#pragma once
#include "cBicho.h"
#include "Globals.h"

class cProyectil :	public cBicho
{
public:
	cProyectil();
	~cProyectil();

	bool CollidesBicho(cBicho* bicho);
	virtual void Logic(int *map);

	virtual void Draw(cData *dat);

	void setSpeed(int x, int y);
	void getSpeed(int* x, int* y);
private:
	float dmg;
	int speedX, speedY;
};

