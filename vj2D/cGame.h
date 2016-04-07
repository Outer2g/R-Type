#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "cData.h"
#include "cBicho.h"
#include "cEnemigo.h"
#include "cPowerUp.h"
#include "cBoom.h"
#include "cBoss.h"
#include <vector>
#include <set>
#include "Screens.h"

//Score defines
#define SCORE_HIT 10
#define SCORE_REKT 50

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_Q 113
using namespace std;

class cGame
{
public:
	cGame(int type =0);
	virtual ~cGame(void);
	int type;
	bool Init();
	bool Loop();
	void Finalize();
	void reset();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadKeySpecialBoard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void Render();
	void logicToAddMonsters();

private:
	bool tratarKeys();
	
	void enterGodMode(cPlayer* p);
	void modificaScore(int id, int amount);
	void monsterndBulletLogic(set<void*>& toDelete);
	void yerDead(cBicho* bicho,int type = ENEMY_BOOM);
	bool loadResources(int level);
	unsigned char keys[256];
	unsigned char sKeys[256]; //109 se supone
	cScene Scene;
	Screens Screen;
	cPlayer Player, Player2;
	cData Data;
	vector<vector<int> > rafagasBichos; //[numRafaga][0-3], 0 = x, 1 = y, 2 = tipo, 3 = numBichos
	long int offsetCamera;
	//vector<cBicho*> bichos;
	set<cEnemigo*> bichos;
	cBoss* boss;
	set<cProyectil*>  pewpews;
	set<cPowerUp*> powerUps;
	set<cBoom*> explosiones;
	int rafagaQueToca = 0, numRafagas;
	double godModeTimer,godModeTimer2,outShieldTimer,outShieldTimer2;
	int level;
};
