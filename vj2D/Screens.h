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

	bool Init(int* gam);
	//Process
	bool Process(int state, int x, int y);
	//Output
	void Render();
	int screenToRender;
	void DrawRect(int tex_id, int xo, int yo);
	void Collides(int state, int x, int y);

private:
	inline void render_info();
	cData Data;
	cScene Scene;
	int* gam;
	int play1, play2, help, credits;
};

