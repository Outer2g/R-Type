#pragma once
#include "cEnemigo.h"
#include "cPlayer.h"
class cBoss :
	public cEnemigo
{
public:
	cBoss();
	~cBoss();
	virtual void draw(cData* dat);
	void attackBasic(set<cProyectil*>& pewpews,cPlayer * Player);
	void attackSpecial(set<cProyectil*>& pewpews);
	void shootSomething(set<cProyectil*>& pewpews, cPlayer* Player);
	
private:
	double lastSpecial; //lastShoot viene de cEnemigo
	int delaySpecial;
};

