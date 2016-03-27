#pragma once

#include "cBicho.h"
#include "cProyectil.h"
#include <set>

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2


#define STATE_DOWN_SLOW		0
#define STATE_DOWN_FAST		1
#define STATE_UP_SLOW		2
#define STATE_UP_FAST		3


using namespace std;
class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();

	virtual void Draw(int tex_id);

	virtual void MoveRight(int *map);
	//virtual void MoveHalfRight(int *map);
	virtual void MoveLeft(int *map);
	virtual void MoveDown(int *map);
	virtual void Jump(int *map);
	virtual void Stop();
	virtual void Logic(int *map);

	void shoot(set<cProyectil*> & pewpews);
	void setBullet(int bullet);
	int getBullet();
	void setMoving(bool b);
	bool getMoving();
	void enableGodMode();
	void disableGodMode();
	bool getMode();
	bool endLevel;
	void setID(int id);
	int getID();
	//A : Positivo o negativo
	void modifyScore(int A);
	int getScore();
	void modifyVidas(int A);
	int getVidas();
private:
	//Proyectiles
	void proyectSimple(set<cProyectil*> & pewpews);
	void proyectDoble(set<cProyectil*> & pewpews);
	bool moving,godMode,invis;
	double delayShoot,delayInvis;
	int shootingDelay,bulletType,idPlayer,score,vidas;
};
