#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "cVolador.h"


#define FRAME_DELAY		8


#define STATE_CENTER		4
#define PI 3.14159265

class cVoladorMariposa : public cVolador
{
public:
	cVoladorMariposa();
	~cVoladorMariposa();

	virtual void Stop();
	virtual void Logic(int *map);
	virtual void Draw(cData *dat);

private:
	int speed;
	double angle;
};
