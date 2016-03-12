#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "cVolador.h"

#define FRAME_DELAY		8
#define STEP_LENGTH		2
#define JUMP_STEP		4


#define STATE_CENTER		4


class cVoladorMariposa : public cVolador
{
public:
	cVoladorMariposa();
	~cVoladorMariposa();

	virtual void Stop();
	virtual void Logic(int *map);
	virtual void Draw(int texId);
	
};
