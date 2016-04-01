#pragma once
#include "cBicho.h"

#define ENEMY_BOOM 0
#define NAVE_BOOM 1
class cBoom :
	public cBicho
{
public:
	cBoom();
	cBoom(int type);
	~cBoom();

	virtual void Draw(cData* dat);
	virtual void NextFrame(int max);

	double getCreationTime();
	void resetCreationTime();
	void setType(int type);
	int getType();
private:
	double boomTime;
	int type;
};

