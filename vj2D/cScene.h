#pragma once

#include "cTexture.h"

#define SCENE_Xo		0//(2*TILE_SIZE)
#define SCENE_Yo		0//TILE_SIZE
#define SCENE_WIDTH		90 //640 width / 64 tamano //TODO ACTUALIZAR SIZE
#define SCENE_WIDTH_2	90 //640 width / 64 tamano //TODO ACTUALIZAR SIZE
#define SCENE_HEIGHT	16

#define FILENAME		"level"
#define FILENAME_EXT	".txt"

#define TILE_SIZE		32 
#define BLOCK_SIZE		32

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	bool LoadLevel(int level);
	void Draw(int tex_id);
	void DrawBackground(int tex_id);
	int *GetMap(int level);
	int BACK_HEIGHT, BACK_WIDTH_DRAW;
	int tilesFila;

private:
	int map[SCENE_WIDTH * SCENE_HEIGHT];	//scene
	int map2[SCENE_WIDTH_2 * SCENE_HEIGHT];
	int id_DL;								//actual level display list
	//int SCENE_WIDTH;
};
