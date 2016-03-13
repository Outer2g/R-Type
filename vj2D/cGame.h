#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "cData.h"
#include "cBicho.h"
#include <vector>

#define GAME_WIDTH	640
#define GAME_HEIGHT 512
using namespace std;

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void Render();

private:
	unsigned char keys[256];
	cScene Scene;
	cPlayer Player;
	cData Data;
	vector<vector<int> > rafagasBichos; //[numRafaga][0-3], 0 = x, 1 = y, 2 = tipo, 3 = numBichos
	long int offsetCamera;
	vector<cBicho*> bichos;
	int rafagaQueToca = 0, numRafagas;
};
