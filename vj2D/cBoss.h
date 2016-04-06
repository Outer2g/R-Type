#pragma once
#include "cEnemigo.h"
#include "cPlayer.h"
#include "cScene.h"

#define STATE_MOVING_RAYO 0
#define STATE_STACIONARY 1
#define STATE_MOVING_RAYO2 2
using namespace std;
class cBoss :
	public cEnemigo
{
public:
	cBoss();
	cBoss(set<cProyectil*> & pewpews);
	~cBoss();
	virtual void Draw(cData* dat);
	void attackBasic(set<cProyectil*>& pewpews,cPlayer * Player);
	void shootRayo();
	void shootSomething(set<cProyectil*>& pewpews, cPlayer* Player);

	virtual void Logic(int *map);

	double getrayoShotTimer();
	int getDelayRayo();
	
private:
	void moveToPosition(int x, int y);
	set<cProyectil*> * pewpews;
	cProyectil* rayo;
	double stateTimer,rayoShotTimer; //lastShoot viene de cEnemigo
	int delayState1, delayState2,delayRayo;
	bool rayoShot;
};

