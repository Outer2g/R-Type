#pragma once
#include "cBicho.h"
class cBoom :
	public cBicho
{
public:
	cBoom();
	~cBoom();

	virtual void Draw(cData* dat);
	virtual void NextFrame(int max);

	double getCreationTime();
	void resetCreationTime();
private:
	double boomTime;
};

