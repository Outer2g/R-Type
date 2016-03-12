#pragma once

#include "cBicho.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2


#define STATE_DOWN_SLOW		0
#define STATE_DOWN_FAST		1
#define STATE_UP_SLOW		2
#define STATE_UP_FAST		3

class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();

	void Draw(int tex_id);

	virtual void MoveRight(int *map);
	//virtual void MoveHalfRight(int *map);
	virtual void MoveLeft(int *map);
	virtual void MoveDown(int *map);
	virtual void Jump(int *map);
	virtual void Stop();
	virtual void Logic(int *map);
	void setMoving(bool b);
	bool getMoving();
private:
	bool moving;
};
