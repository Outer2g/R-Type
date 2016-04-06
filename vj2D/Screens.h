#pragma once
#include "cData.h"
#include "cGame.h"


class Screens
{
public:
	Screens();
	~Screens();

	bool Init();
	bool Loop();
	//Process
	bool Process();
	//Output
	void Render();
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadKeySpecialBoard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);

private:
	cData Data;
	bool tratarKeys();
	unsigned char keys[256];
	unsigned char sKeys[256]; //109 se supone
};

