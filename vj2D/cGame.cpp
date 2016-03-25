#include "cGame.h"
#include "Globals.h"
#include "cVoladorEstatico.h"
#include "cVoladorMariposa.h"


cGame::cGame(void)
{
	offsetCamera = 0;
	Player.setID(1);
	Player2.setID(2);
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
	bool res=true;
	offsetCamera = 0;
	rafagaQueToca = 0;
	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	int level = 1; //nos lo pasaran desde el menu de escoger partida

	//Scene initialization
	//res = Data.LoadImage(IMG_BLOCKS,"blocks.png",GL_RGBA);
	//if(!res) return false;
	if (level == 1) {
		res = Data.LoadImage(IMG_PARED, "backTiles1.png", GL_RGBA);
		if (!res) return false;
		res = Data.LoadImage(IMG_BACK, "back1.png", GL_RGBA);
		if (!res) return false;
		res = Data.LoadImage(IMG_ESTATIC, "enemyEstatico.png", GL_RGBA);
		if (!res) return false;
		res = Data.LoadImage(IMG_MARIP, "enemyEstatico.png", GL_RGBA);
		if (!res) return false;
		res = Data.LoadImage(IMG_BULLET_VOLADOR, "bulletVolador.png", GL_RGBA);
		if (!res) return false;

		res = Data.LoadImage(IMG_BUB, "bub.png", GL_RGBA);
		if (!res) return false;
		Scene.tilesFila = 16; //porque el texture mide 512 y caben 16 tiles de 32
		Scene.BACK_HEIGHT = 512;
		Scene.BACK_WIDTH_DRAW = 2560; //tamano en horizontal dl background
		//[numRafaga][0-3], 0 = x, 1 = y, 2 = tipo, 3 = numBichos
		numRafagas = 4;
		rafagasBichos.resize(numRafagas, vector<int>(4)); //3 rafagas, cada rafaga tiene 4 atributos (x,y,tipo,num)
		rafagasBichos[0] = { 10, 10, 0, 2 }; //primera rafaga
		rafagasBichos[1] = { 15, 10, 1, 2 }; //3 rafaga
		rafagasBichos[2] = { 30, 10, 0, 2 }; //2a rafaga
		rafagasBichos[3] = { 50, 10, 0, 2 }; //3 rafaga
	}
	else if (level != 1) {
		res = Data.LoadImage(IMG_PARED, "backTiles1.png", GL_RGBA);
		if (!res) return false;
		res = Data.LoadImage(IMG_BACK, "back1.png", GL_RGBA);
		if (!res) return false;
		Scene.tilesFila = 16; //porque el texture mide 512 y caben 16 tiles de 32
		Scene.BACK_HEIGHT = 512;
		Scene.BACK_WIDTH_DRAW = 2560; //tamano en horizontal dl background
	}


	res = Scene.LoadLevel(level);
	if(!res) return false;

	
	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"naves.png",GL_RGBA);
	if(!res) return false;
	Player.SetWidthHeight(64,32);
	Player.SetTile(1,8);
	Player.SetState(STATE_CENTER);

	Player2.SetWidthHeight(64, 32);
	Player2.SetTile(1, 10);
	Player2.SetState(STATE_CENTER);
	return res;
}

bool cGame::Loop()
{
	bool res=true;
	double t1, t2;

	t1 = glutGet(GLUT_ELAPSED_TIME);
	if (offsetCamera < Scene.BACK_WIDTH_DRAW - GAME_WIDTH) ++offsetCamera;
	else { Player.endLevel = true; Player2.endLevel = true; }
	
	res = Process();
	if(res) Render();

	//1000/20 = 50fps
	do {
		t2 = glutGet(GLUT_ELAPSED_TIME);
	} while (t2 - t1 < 20);

	return res;
}

void cGame::Finalize()
{
	//version cutre
	Player =cPlayer();
	for (void* x : bichos) delete x;
	for (void* x : pewpews) delete x;
	for (void* x : powerUps) delete x;

	bichos = set<cEnemigo*>();
	pewpews = set<cProyectil*>();
	powerUps = set<cPowerUp*>();
}

void cGame::reset()
{
	Finalize();
	Init();
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void cGame::ReadKeySpecialBoard(unsigned char key, int x, int y, bool press)
{
	sKeys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
}

inline void cGame::monsterndBulletLogic(set<void*>& toDelete) {
	for (cEnemigo* monster : this->bichos) {
		int tx, ty; Player.GetPosition(&tx, &ty);
		monster->shootBoi(pewpews, tx, ty);
		monster->Logic(Scene.GetMap());
		for (cProyectil* pewpew : this->pewpews) {
			if (pewpew->CollidesBicho(monster)) {
				//luz fuego destruccion
				toDelete.insert(pewpew);
				monster->dealDamage(pewpew->getDamage());
				if (monster->getHealth() <= 0) {
					toDelete.insert(monster);
					cPowerUp* powah = new cPowerUp(BULLET_DOBLE);
					int tx, ty; monster->GetTile(&tx, &ty);
					powah->SetTile(tx, ty);
					powah->SetWidthHeight(32, 32);
					this->powerUps.insert(powah);
				}
				//Comprobacion si nave choca con monstruo para hacerlo mas eficiente(aka sidoso)
			}
		}
		//si bicho choca con las naves
		bool b = monster->CollidesBicho(&Player);
		if (b && !Player.getMode()) {
			Player.enableGodMode();
			godModeTimer = glutGet(GLUT_ELAPSED_TIME);
		}
		b = monster->CollidesBicho(&Player2);
		if (b && !Player2.getMode()) {
			Player2.enableGodMode();
			godModeTimer2 = glutGet(GLUT_ELAPSED_TIME);
		}
	}
}
//Process
bool cGame::Process()
{
	bool res = true;
	res = tratarKeys();
	//Logica proyectiles + colisiones Proyectiles
	for (cProyectil* pewpew : this->pewpews)
		pewpew->Logic(Scene.GetMap());
	set<void*> toDelete;
	monsterndBulletLogic(toDelete);
	
	//gestion godtimers
	double t1 = glutGet(GLUT_ELAPSED_TIME);
	//si ha pasado 200 frames, desactiva el godmode
	if (t1 - godModeTimer > 200 * 20) Player.disableGodMode();
	if (t1 - godModeTimer2 > 200 * 20) Player2.disableGodMode();
	//Gestion powers
	for (cPowerUp* powah : this->powerUps) {
		if (Player.CollidesBicho((cBicho*)powah)) {
			toDelete.insert(powah);
			int bType = powah->getType();
			Player.setBullet(bType);
		}
		if (Player2.CollidesBicho((cBicho*)powah)) {
			toDelete.insert(powah);
			int bType = powah->getType();
			Player2.setBullet(bType);
		}
	}
	for (void* x : toDelete) {
		pewpews.erase((cProyectil*)x);
		bichos.erase((cEnemigo*)x);
		powerUps.erase((cPowerUp*) x);
		delete x;
	}


	logicToAddMonsters();


	//Nave Logic + colisiones
	//Move with the camera boi
	int playerTileX, playerTileY;
	Player.GetTile(&playerTileX, &playerTileY);
	int cameraTile = offsetCamera / TILE_SIZE;
	int windowTile = (GAME_WIDTH + offsetCamera) / TILE_SIZE;
	if (cameraTile >= playerTileX) {
		Player.MoveRight(Scene.GetMap());
		Player.MoveRight(Scene.GetMap());
		Player.MoveHalfRight(Scene.GetMap());
	}
	else if (windowTile-2 <= playerTileX) {
		Player.MoveLeft(Scene.GetMap());
	}
	else Player.Logic(Scene.GetMap());

	//Logic player2
	Player2.GetTile(&playerTileX, &playerTileY);
	if (cameraTile >= playerTileX) {
		Player2.MoveRight(Scene.GetMap());
		Player2.MoveRight(Scene.GetMap());
		Player2.MoveHalfRight(Scene.GetMap());
	}
	else if (windowTile - 2 <= playerTileX) {
		Player2.MoveLeft(Scene.GetMap());
	}
	else Player2.Logic(Scene.GetMap());
	//si choca con enemigo hazte pupa por eficiencia, esta con los proyectiles

	return res;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(offsetCamera, GAME_WIDTH + offsetCamera, 0, GAME_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);

	Scene.DrawBackground(Data.GetID(IMG_BACK));
	Scene.Draw(Data.GetID(IMG_PARED));
	for (cEnemigo* b : bichos) b->Draw(&Data);
	//bichos[0]->Draw(&Data);
	Player.Draw(Data.GetID(IMG_PLAYER));
	Player2.Draw(Data.GetID(IMG_PLAYER));
	//Proyectiles
	for (cProyectil* pewpew : this->pewpews) pewpew->Draw(&Data);
	//PowerUps
	for (cPowerUp* powah : this->powerUps) powah->Draw(&Data);
	glutSwapBuffers();
}

inline bool cGame::tratarKeys()
{
	bool res = true;
	/////////////////////////////////////////////
	//Process Input
	if (sKeys[27])	res = false;
	if (sKeys[GLUT_KEY_UP])			Player.Jump(Scene.GetMap());
	else if (sKeys[GLUT_KEY_DOWN])	Player.MoveDown(Scene.GetMap());
	else Player.setMoving(false);
	if (sKeys[GLUT_KEY_LEFT])			Player.MoveLeft(Scene.GetMap());
	else if (sKeys[GLUT_KEY_RIGHT])	Player.MoveRight(Scene.GetMap());
	//Si no hay nada aparetado, para el player
	if (!sKeys[GLUT_KEY_UP]
		&& !sKeys[GLUT_KEY_DOWN]
		&& !sKeys[GLUT_KEY_LEFT]
		&& !sKeys[GLUT_KEY_RIGHT]) Player.Stop();
	// enter = 13, shooting for player 1
	if (keys[13])
		Player.shoot(this->pewpews);
	//Player 2 controls
	//w = 119, a = 97, s = 115, d= 100, D =68, q= 113
	if (keys[KEY_W])			Player2.Jump(Scene.GetMap());
	else if (keys[KEY_S])	Player2.MoveDown(Scene.GetMap());
	else Player2.setMoving(false);
	if (keys[KEY_A])			Player2.MoveLeft(Scene.GetMap());
	else if (keys[KEY_D])	Player2.MoveRight(Scene.GetMap());
	//Si no hay nada aparetado, para el player
	if (!keys[KEY_W]
		&& !keys[KEY_S]
		&& !keys[KEY_A]
		&& !keys[KEY_D]) Player2.Stop();
	// enter = 13, shooting for player 1
	if (keys[KEY_Q])
		Player2.shoot(this->pewpews);
	//TESTING BUTTONS
	if (sKeys[GLUT_KEY_F1]) Player.setBullet(BULLET_SIMPLE);
	if (sKeys[GLUT_KEY_F2]) Player.setBullet(BULLET_DOBLE);
	if (sKeys[GLUT_KEY_F3]) Player.enableGodMode();
	if (sKeys[GLUT_KEY_F4]) reset();

	return res;
}


inline void cGame::logicToAddMonsters() {
	//logic to add monsters
	if ((rafagaQueToca < numRafagas) && ((offsetCamera + GAME_WIDTH + TILE_SIZE) / TILE_SIZE > rafagasBichos[rafagaQueToca][0])) {
		cEnemigo* bicho;
		switch (rafagasBichos[rafagaQueToca][2]) {
		case 0:
			for (int i = 0; i < rafagasBichos[rafagaQueToca][3]; i++) {
				bicho = new cVoladorEstatico();
				bicho->SetWidthHeight(46, 50);
				bicho->SetTile(rafagasBichos[rafagaQueToca][0] + i*2, rafagasBichos[rafagaQueToca][1]-i);
				bichos.insert(bicho);
			}
			break;
		case 1:
			for (int i = 0; i < rafagasBichos[rafagaQueToca][3]; i++) {
				bicho = new cVoladorMariposa();
				bicho->SetWidthHeight(46, 50);
				bicho->SetTile(rafagasBichos[rafagaQueToca][0] + i, rafagasBichos[rafagaQueToca][1]);
				bichos.insert(bicho);
			}
			break;
		}

		++rafagaQueToca;
	}
}
