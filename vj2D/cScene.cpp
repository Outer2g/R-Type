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

	int width = (level == 1) ? SCENE_WIDTH : SCENE_WIDTH_2;

	id_DL=glGenLists(1);
	glNewList(id_DL,GL_COMPILE);
		glBegin(GL_QUADS);
	
			for(j=SCENE_HEIGHT-1;j>=0;j--)
			{
				px=SCENE_Xo;
				py=SCENE_Yo+(j*TILE_SIZE);

				for(i=0;i<width;i++)
				{
					fscanf(fd,"%d",&tile);
					if (tile == 0)
					{
						if (level == 1) map[(j*width)+i]=0;
						else map2[(j*width) + i] = 0;
					}
					else
					{
						//PODRIAMOS COMPROBAR ALGUNA TILE EN CONCRETO SI QUEREMOS QUE CIERTOS ID TENGAN ANIMACION
						//TODO
						//Tiles = 1,2,3,...
						float divY = (level == 1) ? 0.25f : 0.125f;
						if (level == 1) map[(j*width)+i] = tile;
						else map2[(j*width) + i] = tile;
						coordy_tile = (tile - 1) / tilesFila * divY;
						
						coordx_tile = ((tile-1) % (tilesFila)) * (float)(1.0f / (float)tilesFila);

						glTexCoord2f(coordx_tile       ,coordy_tile+ divY);	glVertex2i(px           ,py           );
						glTexCoord2f(coordx_tile+ (1.0f/(float)tilesFila),coordy_tile+ divY);	glVertex2i(px+BLOCK_SIZE,py           );
						glTexCoord2f(coordx_tile+ (1.0f / (float)tilesFila),coordy_tile       );	glVertex2i(px+BLOCK_SIZE,py+BLOCK_SIZE);
						glTexCoord2f(coordx_tile       ,coordy_tile       );	glVertex2i(px           ,py+BLOCK_SIZE);
					}
					px+=TILE_SIZE;
				}
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


void cScene::DrawBackgroundNormal(int tex_id)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	// Draw a textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 512, 0);
	glTexCoord2f(0, 1); glVertex3f(0, 0, 0);
	glTexCoord2f(1, 1); glVertex3f(640, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(640, 512, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

int* cScene::GetMap(int level)
{
	return (level == 1) ? map : map2;
}