#include "cGame.h"
#include "Globals.h"
#include "cVoladorEstatico.h"


cGame::cGame(void)
{
	offsetCamera = 0;
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
	bool res=true;

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
		Scene.tilesFila = 16; //porque el texture mide 512 y caben 16 tiles de 32
		Scene.BACK_HEIGHT = 512;
		Scene.BACK_WIDTH_DRAW = 2560; //tamano en horizontal dl background
		//[numRafaga][0-3], 0 = x, 1 = y, 2 = tipo, 3 = numBichos
		numRafagas = 3;
		rafagasBichos.resize(numRafagas, vector<int>(4)); //3 rafagas, cada rafaga tiene 4 atributos (x,y,tipo,num)
		rafagasBichos[0] = { 10, 10, 0, 2 }; //primera rafaga
		rafagasBichos[1] = { 20, 10, 0, 2 }; //2a rafaga
		rafagasBichos[2] = { 30, 10, 0, 2 }; //3 rafaga

		/*cBicho* p = new cVoladorEstatico();
		bichos.push_back(p);
		bichos[0]->SetWidthHeight(46, 50);
		bichos[0]->SetTile(6, 8);*/
		/*
		foo = new (nothrow) int [5];
		if (foo == nullptr) {
		  // error assigning memory. Take measures.
		}*/
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

	return res;
}

bool cGame::Loop()
{
	bool res=true;
	double t1, t2;

	t1 = glutGet(GLUT_ELAPSED_TIME);
	if (offsetCamera < Scene.BACK_WIDTH_DRAW - GAME_WIDTH) ++offsetCamera;
	else Player.endLevel = true;
	
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
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
}

//Process
bool cGame::Process()
{
	bool res=true;
	
	//Process Input
	if(keys[27])	res=false;
	
	if(keys[GLUT_KEY_UP])			Player.Jump(Scene.GetMap());
	else if (keys[GLUT_KEY_DOWN])	Player.MoveDown(Scene.GetMap());
	else Player.setMoving(false);
	if(keys[GLUT_KEY_LEFT])			Player.MoveLeft(Scene.GetMap());
	else if(keys[GLUT_KEY_RIGHT])	Player.MoveRight(Scene.GetMap());
	//Si no hay nada aparetado, para el player
	if (!keys[GLUT_KEY_UP]
		&& !keys[GLUT_KEY_DOWN] 
		&&!keys[GLUT_KEY_LEFT] 
		&&!keys[GLUT_KEY_RIGHT]) Player.Stop();
	
	

	//logic to add monsters
	if ((rafagaQueToca < numRafagas) && ((offsetCamera + GAME_WIDTH) / TILE_SIZE > rafagasBichos[rafagaQueToca][0])) {
		bichos.push_back(new cVoladorEstatico());
		bichos.back()->SetWidthHeight(46, 50);
		bichos.back()->SetTile(rafagasBichos[rafagaQueToca][0], rafagasBichos[rafagaQueToca][1]);
		rafagaQueToca++;
	}


	//Game Logic
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
	for (cBicho* b : bichos) b->Draw(&Data);
	//bichos[0]->Draw(&Data);
	Player.Draw(Data.GetID(IMG_PLAYER));

	glutSwapBuffers();
}
