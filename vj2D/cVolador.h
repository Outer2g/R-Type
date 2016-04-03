#pragma once

#include "cEnemigo.h"
#include "cProyectil.h"
#include <math.h>
#include <set>

/*#define STATE_LOOKLEFT		0
#define STATE_LOOKRIGHT		1
#define STATE_WALKLEFT		2
#define STATE_WALKRIGHT		3*/

using namespace std;
class cVolador : public cEnemigo
{
public:
	cVolador();
	~cVolador();

	virtual void MoveRight(int *map);
	virtual void MoveLeft(int *map);
	virtual void MoveDown(int *map);
	virtual void Jump(int *map);
	virtual void Stop();
	virtual void Logic(int *map);

	virtual void NextFrame(int max);
	virtual void setShootChance(int shootingChance);
	virtual int getShootChance();

	void setShoot(bool b);
	bool getShoot();
	//virtual void Draw();
protected:
	double moveDelay,lastShootDec;
};
