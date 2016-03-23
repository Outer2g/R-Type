#pragma once
#include "cBicho.h"
#include "cProyectil.h"
#include <set>
using namespace std;
class cEnemigo :
	public cBicho
{
public:
	cEnemigo();
	~cEnemigo();

	virtual void MoveRight(int *map);
	virtual void MoveLeft(int *map);
	virtual void MoveDown(int *map);
	virtual void Jump(int *map);
	virtual void Stop();
	virtual void Logic(int *map);


	virtual void shootBoi(set<cProyectil*> &pewpews, int posx, int posy);
};

