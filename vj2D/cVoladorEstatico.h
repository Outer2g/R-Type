#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "cVolador.h"

#define FRAME_DELAY		8
#define STEP_LENGTH		2
#define JUMP_STEP		4


#define STATE_CENTER		4


class cVoladorEstatico : public cVolador
{
public:
	cVoladorEstatico(void);
	cVoladorEstatico(int x,int y,int w,int h);
	~cVoladorEstatico(void);

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
