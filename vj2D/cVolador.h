#pragma once

#include "cBicho.h"


/*#define STATE_LOOKLEFT		0
#define STATE_LOOKRIGHT		1
#define STATE_WALKLEFT		2
#define STATE_WALKRIGHT		3*/


class cVolador : public cBicho
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

	//virtual void Draw();
protected:
	double moveDelay;
};
