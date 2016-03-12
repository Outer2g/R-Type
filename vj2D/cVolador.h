#pragma once

#include "cBicho.h"


/*#define STATE_LOOKLEFT		0
#define STATE_LOOKRIGHT		1
#define STATE_WALKLEFT		2
#define STATE_WALKRIGHT		3*/


class cVolador : public cBicho
{
public:
	cVolador(void);
	cVolador(int x,int y,int w,int h);
	~cVolador(void);

	virtual void MoveRight(int *map);
	virtual void MoveLeft(int *map);
	virtual void MoveDown(int *map);
	virtual void Jump(int *map);
	virtual void Stop();
	virtual void Logic(int *map);

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();
	virtual void Draw(int texId);
	
private:
	int w,h;


protected:
	int x, y;
	int state;

	int seq, delay;
};
