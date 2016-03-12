#pragma once
#include "cBicho.h"
class cVoladorAux :public cBicho
{
public:
	cVoladorAux();
	~cVoladorAux();

	virtual void Draw(int tex_id);
};

