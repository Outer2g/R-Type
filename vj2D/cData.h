#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG		12

//Image identifiers
#define IMG_BLOCKS	0
#define IMG_PLAYER	1
#define IMG_PARED	2
#define IMG_BACK	3
#define IMG_MARIP	4
#define IMG_ESTATIC	5
#define IMG_BULLET_VOLADOR	6
#define IMG_BUB		7
#define IMG_PLAYER2	8
#define IMG_ENEMY_BOOM 9
#define IMG_SHIELD 10
#define IMG_NAVE_BOOM 11
/*
#define IMG_ENEMY1	2
#define IMG_ENEMY2	3
#define IMG_SHOOT	4
...
*/

class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	void GetSize(int img,int *w,int *h);
	bool LoadImage(int img,char *filename,int type = GL_RGBA);

private:
	cTexture texture[NUM_IMG];
};
