#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "cVolador.h"
#include <cstdlib>
#include <ctime>

#define FRAME_DELAY		8
#define STEP_LENGTH		2
#define JUMP_STEP		4


#define STATE_CENTER		4


class cVoladorEstatico : public cVolador
{
public:
	cVoladorEstatico();
	~cVoladorEstatico();

	virtual void Stop();
	virtual void Logic(int *map);

	virtual void Draw(cData * dat);
	
private:
	int speed;
	int random_variable;
	double moveDelaySteering;
};
