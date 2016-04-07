#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG		28

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
#define IMG_SHIELD_POWER 12
#define IMG_BULLET_POWER 13
#define IMG_PLAYER_BULLETS 14
#define IMG_PROPULSIONES 15
#define IMG_BOSS_ENTITY 16
#define IMG_BOSS_RAYO 17
#define IMG_BACK_MAIN 18
#define BT_PLAY1 19
#define BT_PLAY1_FOC 20
#define BT_PLAY2 21
#define BT_PLAY2_FOC 22
#define BT_HELP 23
#define BT_HELP_FOC 24
#define BT_CREDITS 25
#define BT_CREDITS_FOC 26
#define IMG_PLAYER_HEARTS 27
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
