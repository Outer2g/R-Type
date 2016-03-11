#include "cScene.h"
#include "Globals.h"

cScene::cScene(void)
{
}

cScene::~cScene(void)
{
}

bool cScene::LoadLevel(int level)
{
	bool res;
	FILE *fd;
	char file[16];
	int i,j,px,py;
	int tile;
	float coordx_tile, coordy_tile;

	res=true;

	if(level<10) sprintf(file,"%s0%d%s",(char *)FILENAME,level,(char *)FILENAME_EXT);
	else		 sprintf(file,"%s%d%s",(char *)FILENAME,level,(char *)FILENAME_EXT);

	fd=fopen(file,"r");
	if(fd==NULL) return false;

	id_DL=glGenLists(1);
	glNewList(id_DL,GL_COMPILE);
		glBegin(GL_QUADS);
	
			for(j=SCENE_HEIGHT-1;j>=0;j--)
			{
				px=SCENE_Xo;
				py=SCENE_Yo+(j*TILE_SIZE);

				for(i=0;i<SCENE_WIDTH;i++)
				{
					fscanf(fd,"%d",&tile);
					if (tile == 0)
					{
						//fscanf(fd, "%c", &tile);
						//Tiles must be != 0 !!!
						map[(j*SCENE_WIDTH)+i]=0;
					}
					else
					{
						//Tiles = 1,2,3,...
						map[(j*SCENE_WIDTH)+i] = tile;
						coordy_tile = tile < tilesFila ? 0.0f : 0.5f;
						
						coordx_tile = ((tile-1) % (tilesFila)) * 0.125f;

						/*if (tile == 1) {
							coordx_tile = 0.0f;
							coordy_tile = 0.0f;
						}
						else if (tile == 2) {
							coordx_tile = 0.125f;
							coordy_tile = 0.0f;
						}*/
						

						/*
						if(map[(j*SCENE_WIDTH)+i]%2) coordx_tile = 0.0f;
						else						 coordx_tile = 0.125f;
						if(map[(j*SCENE_WIDTH)+i]<3) coordy_tile = 0.0f;
						else						 coordy_tile = 0.5f;*/

						//BLOCK_SIZE = 24, FILE_SIZE = 64
						// 24 / 64 = 0.375
						glTexCoord2f(coordx_tile       ,coordy_tile+0.5f);	glVertex2i(px           ,py           );
						glTexCoord2f(coordx_tile+0.125f,coordy_tile+0.5f);	glVertex2i(px+BLOCK_SIZE,py           );
						glTexCoord2f(coordx_tile+0.125f,coordy_tile       );	glVertex2i(px+BLOCK_SIZE,py+BLOCK_SIZE);
						glTexCoord2f(coordx_tile       ,coordy_tile       );	glVertex2i(px           ,py+BLOCK_SIZE);
					}
					px+=TILE_SIZE;
				}
				//fscanf(fd,"%c",&tile); //pass enter
			}

		glEnd();
	glEndList();

	fclose(fd);

	return res;
}

void cScene::Draw(int tex_id)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glCallList(id_DL);
	glDisable(GL_TEXTURE_2D);
}

void cScene::DrawBackground(int tex_id)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	// Draw a textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1); glVertex3f(0, BACK_HEIGHT, 0);
	glTexCoord2f(1, 1); glVertex3f(BACK_WIDTH_DRAW, BACK_HEIGHT, 0);
	glTexCoord2f(1, 0); glVertex3f(BACK_WIDTH_DRAW, 0, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

int* cScene::GetMap()
{
	return map;
}