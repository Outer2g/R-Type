#include "cBoss.h"



cBoss::cBoss()
{
	delayState1 = 100;
	delayState2 = 30;
	delayState3 = 100;
	delayRayo = 150;
	health = 10000;//10ks
	srand(time(0));
	state = STATE_MOVING_RAYO;
	stateTimer = glutGet(GLUT_ELAPSED_TIME);
}

cBoss::cBoss(set<cProyectil*> & pewpews)
{
	delayState1 = 100;
	delayState2 = 200;
	delayState3 = 100;
	delayState4 = 200;
	delayRayo = 150;
	rayoShot = false;
	health = 10000;//10ks
	srand(time(0));
	state = STATE_MOVING_RAYO;
	stateTimer = glutGet(GLUT_ELAPSED_TIME);
	this->pewpews = &pewpews;
}


cBoss::~cBoss()
{
}

void cBoss::Draw(cData * dat)
{
	float xo, yo, xf, yf;
	xo = 0.375f *GetFrame(); //cada uno son 46*50 y la imagen es de 256*64
	yo = 0.890625f;
	NextFrame(2);
	//coord textur: xo,yo
	xf = xo + 0.375f;//1/8 da el 0.125
	yf = 0.f; //xk la nave ocupa toda la altura d la textura

	DrawRect(dat->GetID(IMG_BOSS_ENTITY), xo, yo, xf, yf);
}

void cBoss::attackBasic(set<cProyectil*>& pewpews, cPlayer * Player)
{
	//Shoot for default
	int tx, ty; Player->GetPosition(&tx,&ty);
	shootBoi(pewpews,tx,ty);
}

void cBoss::shootRayo()
{
	//Rayo magico de la muerte
	cProyectil* pewpew = new cProyectil(3, RAYO_BOSS);
	pewpew->SetWidthHeight(76, 12);
	pewpew->SetPosition(x-w/2, y+h/2);
	pewpew->setSpeed(-STEP_LENGTH, 0);
	rayo = pewpew;
	pewpews->insert(pewpew);
}

void cBoss::shootSomething(set<cProyectil*>& pewpews, cPlayer * Player)
{
	//decide cuando dispara
}

void cBoss::Logic(int * map)
{
	double t1 = glutGet(GLUT_ELAPSED_TIME);
	if (state == STATE_MOVING_RAYO) {
		int scene_height = SCENE_HEIGHT * TILE_SIZE;
		int scene_width = SCENE_WIDTH * TILE_SIZE;
		moveToPosition(x+20, scene_height / 4 );
		if (!rayoShot) { shootRayo(); rayoShot = true; rayoShotTimer = glutGet(GLUT_ELAPSED_TIME); }
		if (t1 - stateTimer > delayState1 * 20) { 
			state = STATE_STACIONARY; 
			stateTimer = glutGet(GLUT_ELAPSED_TIME);
		}
	}
	else if (state == STATE_STACIONARY) {
		rayoShot = false;
		if (t1 - stateTimer > delayState2 * 20) {
			state = STATE_MOVING_RAYO2;
			stateTimer = glutGet(GLUT_ELAPSED_TIME);
		}
	}
	else if (state == STATE_MOVING_RAYO2) {
		int scene_height = SCENE_HEIGHT * TILE_SIZE;
		int scene_width = SCENE_WIDTH * TILE_SIZE;
		moveToPosition(x - 20, scene_height* 3/ 4);
		if (!rayoShot) { shootRayo(); rayoShot = true; rayoShotTimer = glutGet(GLUT_ELAPSED_TIME); }
		if (t1 - stateTimer > delayState3 * 20) {
			state = STATE_STACIONARY2;
			stateTimer = glutGet(GLUT_ELAPSED_TIME);
		}
	}
	else if (state == STATE_STACIONARY2) {
		if (t1 - stateTimer > delayState4 * 20) {
			rayoShot = false;
			state = STATE_MOVING_RAYO;
			stateTimer = glutGet(GLUT_ELAPSED_TIME);
		}
	}
	if (rayo != NULL) {
		int wh, hh; rayo->GetWidthHeight(&wh, &hh);
		rayo->SetPosition(x - wh, y + h / 2);
	}
}

double cBoss::getrayoShotTimer()
{
	return rayoShotTimer;
}

int cBoss::getDelayRayo()
{
	return delayRayo;
}

void cBoss::moveToPosition(int x, int y)
{
	if (this->x - x < 0) this->x += STEP_LENGTH; // mueve derecha
	else this->x -= STEP_LENGTH;
	if (this->y - y > 0) this->y -= STEP_LENGTH; //mueve abajo
	else this->y += STEP_LENGTH;
}
