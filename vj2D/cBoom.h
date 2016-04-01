#pragma once
#include "cBicho.h"
class cBoom :
	public cBicho
{
public:
	cBoom();
	~cBoom();
	virtual void Draw(cData* dat);
	double getCreationTime();
	void resetCreationTime();
private:
	double boomTime;
};

