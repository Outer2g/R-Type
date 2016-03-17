#pragma once
#include "cBicho.h"
#include "cProyectil.h"
class cPowerUp : public cBicho
{
public:
	cPowerUp();
	cPowerUp(int type);
	~cPowerUp();

	virtual void Draw(cData* dat);

	void setType(int type);
	int getType();
private:
	int type;
};

