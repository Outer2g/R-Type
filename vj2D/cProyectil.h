#pragma once
#include "cBicho.h"
#include "Globals.h"

//tipos proyectil y powerUps
#define BULLET_SIMPLE 1
#define BULLET_DOBLE 2
#define POWER_SHIELD 5
#define RAYO_BOSS 10
class cProyectil :	public cBicho
{
public:
	cProyectil();
	cProyectil(int id, int tipo);
	~cProyectil();

	virtual void Logic(int *map);

	virtual void Draw(cData *dat);

	void setSpeed(int x, int y);
	void getSpeed(int* x, int* y);
	void setId(int id);
	int getId();
	int getDamage();
private:
	void DrawPEnemigo(cData * dat);
	void DrawPNave(cData* dat);
	void DrawRayo(cData* dat);
	int dmg;
	int speedX, speedY;
	// id == 1 : player1; id == 2 : player2; id ==3 :enemy
	int id;
	int tipo;
};

