
#include "cPlayer.h"
#include "cScene.h"
using namespace std;

cPlayer::cPlayer() {
	moving = false;
	endLevel = false;
	//cuanto menos, mas
	this->shootingDelay = 30;
	this->bulletType = BULLET_SIMPLE;
	this->godMode = false;
	this->invis = false;
	this->score = 0;
	this->shield = false;
	this->vidas = 2;
}
cPlayer::~cPlayer(){}

void cPlayer::Draw(cData *dat)
{
	drawNormal(dat);
	if (shield) drawShield(dat);
}

void cPlayer::DrawRectangleShield(int tex_id, float xo, float yo, float xf, float yf)
{
	int screen_x, screen_y;
	int wa = w +30;
	int ha = h + 10;

	screen_x = x + SCENE_Xo - 15;
	screen_y = y + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE) - 5;

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(xo, yo);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(xf, yo);	glVertex2i(screen_x + wa, screen_y);
	glTexCoord2f(xf, yf);	glVertex2i(screen_x + wa, screen_y + ha);
	glTexCoord2f(xo, yf);	glVertex2i(screen_x, screen_y + ha);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}



void cPlayer::MoveDown(int * map)
{
	//copy paste from move jump(copypasted from moveLeft) swapping from x to y
	int xaux;

	//Whats next tile?
	if ((y % TILE_SIZE) <= 0)
	{
		xaux = y;
		y -= STEP_LENGTH;

		if (CollidesMapFloor(map))
		{
			y = xaux;
			state = STATE_CENTER;
		}
	}
	//Advance, no problem
	else
	{
		y -= STEP_LENGTH + STEP_LENGTH/2;
		state = STATE_DOWN_FAST;
		moving = true;
		if (state != STATE_CENTER)
		{
			state = STATE_DOWN_FAST;
			seq = 0;
			delay = 5;
		}
	}
}
void cPlayer::MoveLeft(int *map)
{
	int xaux;

	//Whats next tile?
	if ((x % TILE_SIZE) <= 1)
	{
		xaux = x;
		if (!endLevel) x -= STEP_LENGTH + STEP_LENGTH;
		else x -= STEP_LENGTH;

		if (CollidesMapWall(map, false))
		{
			x = xaux;
		}
	}
	//Advance, no problem
	else
	{
		if (!endLevel) x -= STEP_LENGTH + STEP_LENGTH;
		else x -= STEP_LENGTH;
		if (!moving) state = STATE_CENTER;
		if (state != STATE_CENTER)
		{
			seq = 0;
			delay = 0;
		}
	}
}

void cPlayer::MoveRight(int *map)
{
	int xaux;

	//Whats next tile?
	if ((x % TILE_SIZE) <= 1)
	{
		xaux = x;
		x += STEP_LENGTH;

		if (CollidesMapWall(map, true))
		{
			x = xaux;
			state = STATE_CENTER;
		}
	}
	//Advance, no problem
	else
	{
		x += STEP_LENGTH;
		if(!moving) state = STATE_CENTER;
		if (state != STATE_CENTER)
		{
			seq = 0;
			delay = 0;
		}
	}
}
void cPlayer::Jump(int *map)
{
	//copy paste from move LEFT swapping from x to y
	int xaux;

	//Whats next tile?
	if ((y % TILE_SIZE) == 0)
	{
		xaux = y;
		y += STEP_LENGTH + STEP_LENGTH/2;

		if (CollidesMapWall(map,false))
		{
			y = xaux;
			state = STATE_CENTER;
		}
	}
	//Advance, no problem
	else
	{
		y += STEP_LENGTH + STEP_LENGTH / 2;
		state = STATE_UP_FAST;
		moving = true;
		if (state != STATE_CENTER)
		{
			seq = 0;
			delay = 0;
		}
	}

}
void cPlayer::Stop()
{
	moving = false;
	state = STATE_CENTER;
}
void cPlayer::Logic(int * map)
{
	if (!endLevel) this->MoveHalfRight(map);
}

void cPlayer::shoot(set<cProyectil*> & pewpews)
{
	double t1;
	if (this->delayShoot == NULL) {
		this->delayShoot = glutGet(GLUT_ELAPSED_TIME);
		t1 = this->delayShoot * 20 + 1;
	}
	else t1 = glutGet(GLUT_ELAPSED_TIME);
	if (t1 - this->delayShoot > 20*this->shootingDelay) {
		this->delayShoot = glutGet(GLUT_ELAPSED_TIME);
		switch (this->bulletType) {
		case BULLET_SIMPLE:
			proyectSimple(pewpews);
			break;
		case BULLET_DOBLE:
			proyectDoble(pewpews);
		}
	}
}

void cPlayer::setPowerUp(int power)
{
	if (power <= 4)	this->bulletType = power;
	else if (power == POWER_SHIELD) this->shield = true;
}

int cPlayer::getBullet()
{
	return this->bulletType;
}

void cPlayer::setMoving(bool b)
{
	this->moving = b;
}

bool cPlayer::getMoving()
{
	return this->moving;
}

void cPlayer::enableGodMode()
{
	this->godMode = true;
	this->invis = true;
}

void cPlayer::disableGodMode()
{
	this->godMode = false;
	this->invis = false;
}

bool cPlayer::getMode()
{
	return godMode;
}

void cPlayer::setID(int id)
{
	this->idPlayer = id;
}

int cPlayer::getID()
{
	return this->idPlayer;
}

void cPlayer::modifyScore(int A)
{
	score += A;
}

int cPlayer::getScore()
{
	return score;
}

void cPlayer::modifyVidas(int A)
{
	vidas += A;
}

int cPlayer::getVidas()
{
	return vidas;
}

void cPlayer::losePowers()
{
	bulletType = BULLET_SIMPLE;
}

void cPlayer::setShield(bool b)
{
	shield = b;
}

bool cPlayer::getShield()
{
	return shield;
}

bool cPlayer::isjustOutShield()
{
	return justOutShield;
}

void cPlayer::setjustOutShield(bool b)
{
	justOutShield = b;
}

inline void cPlayer::drawNormal(cData * dat)
{
	float xo, yo, xf, yf;
	if (!this->godMode) {
		xo = 0.125 * GetState();
		yo = 1.f;
		//coord textur: xo,yo
		xf = xo + 0.125f;//1/8 da el 0.125
		yf = yo - 1.f; //xk la nave ocupa toda la altura d la textura
	}
	else {
		//delta time management boy estaran 0.5segs en cada estado
		if (this->delayInvis == NULL) this->delayInvis = glutGet(GLUT_ELAPSED_TIME);
		if (invis) {
			xo = 0.125 * 6; //aka espacio blanco
			yo = 1.f;
			xf = xo + 0.125f;
			yf = yo - 1.f;
			double t1 = glutGet(GLUT_ELAPSED_TIME);
			//4frames invis
			if (t1 - delayInvis > 10 * 20) { this->invis = false; this->delayInvis = NULL; }
		}
		else {
			xo = 0.125 * GetState();
			yo = 1.f;
			xf = xo + 0.125f;
			yf = yo - 1.f;
			double t1 = glutGet(GLUT_ELAPSED_TIME);
			//4frames invis
			if (t1 - delayInvis > 10 * 20) { this->invis = true; this->delayInvis = NULL; }
		}
	}
	if (idPlayer == 1)DrawRect(dat->GetID(IMG_PLAYER), xo, yo, xf, yf);
	else DrawRect(dat->GetID(IMG_PLAYER2), xo, yo, xf, yf);
}

inline void cPlayer::drawShield(cData * dat)
{
	float xo, yo, xf, yf;
	xo = 0.5f *GetFrame(); //cada uno son 46*50 y la imagen es de 256*64
	yo = 1.0f;
	NextFrame(2);
	//coord textur: xo,yo
	xf = xo + 0.5f;//1/8 da el 0.125
	yf = 0.f; //xk la nave ocupa toda la altura d la textura

	DrawRectangleShield(dat->GetID(IMG_SHIELD), xo, yo, xf, yf);
}

inline void cPlayer::drawPropulsiones(cData * dat)
{
	float xo, yo, xf, yf;
	xo = 0.536231884057971f; //cada uno son 46*50 y la imagen es de 256*64
	yo = 1.0f;
	//coord textur: xo,yo
	xf = xo + 0.463768115942029f;//1/8 da el 0.125
	yf = 0.f; //xk la nave ocupa toda la altura d la textura

	DrawRectangleProp(dat->GetID(IMG_PROPULSIONES), xo, yo, xf, yf);
}

inline void cPlayer::DrawRectangleProp(int tex_id, float xo, float yo, float xf, float yf)
{
	int screen_x, screen_y;
	int wa = 32;
	int ha = 30;

	screen_x = x + SCENE_Xo - w/2+10;
	screen_y = y + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(xo, yo);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(xf, yo);	glVertex2i(screen_x + wa, screen_y);
	glTexCoord2f(xf, yf);	glVertex2i(screen_x + wa, screen_y + ha);
	glTexCoord2f(xo, yf);	glVertex2i(screen_x, screen_y + ha);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cPlayer::proyectSimple(set<cProyectil*>& pewpews)
{
 	cProyectil* pewpew = new cProyectil(this->idPlayer,1);
	pewpew->SetWidthHeight(15, 15);
	int tx, ty;
	this->GetPosition(&tx, &ty);
	pewpew->SetPosition(tx + this->w, ty);
	pewpew->setSpeed(10, 0);
	pewpews.insert(pewpew);
}

void cPlayer::proyectDoble(set<cProyectil*>& pewpews)
{
	cProyectil* pewpew = new cProyectil(this->idPlayer,0);
	pewpew->SetWidthHeight(15, 15);
	int tx, ty;
	this->GetPosition(&tx, &ty);
	int h2 = this->h / 2;
	pewpew->SetPosition(tx + this->w, ty+h2);
	pewpew->setSpeed(10, 0);
	pewpews.insert(pewpew);
	pewpew = new cProyectil(this->idPlayer,0);
	pewpew->SetWidthHeight(15, 15);
	pewpew->SetPosition(tx + this->w, ty-h2);
	pewpew->setSpeed(10, 0);
	pewpews.insert(pewpew);
}
