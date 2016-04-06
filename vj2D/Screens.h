#pragma once
#include "cData.h"
#include <string>
#include "cScene.h"

#define GAME_WIDTH	640
#define GAME_HEIGHT 512


class Screens
{
public:
	Screens();
	~Screens();

	bool Init();
	//Process
	bool Process();
	//Output
	void Render();
	int screenToRender;
	void DrawRect(int tex_id, int xo, int yo);

private:
	cData Data;
	cScene Scene;
};

