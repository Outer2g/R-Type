#include "cGame.h"
#include "Globals.h"


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

	//Scene initialization
	res = Data.LoadImage(IMG_BLOCKS,"blocks.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_PARED, "backTiles1.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_BACK, "back1.png", GL_RGBA);
	if (!res) return false;


	Scene.tilesFila = 16; //porque el texture mide 512 y caben 16 tiles de 32
	res = Scene.LoadLevel(10);
	if(!res) return false;

	Scene.BACK_HEIGHT = 512;
	Scene.BACK_WIDTH_DRAW = 2560; //tamano en horizontal dl background
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
	++offsetCamera;
	
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
	else if (keys[GLUT_KEY_DOWN])	Player.Jump(Scene.GetMap());
	if(keys[GLUT_KEY_LEFT])			Player.MoveLeft(Scene.GetMap());
	else if(keys[GLUT_KEY_RIGHT])	Player.MoveRight(Scene.GetMap());
	else Player.Stop();
	
	
	//Game Logic
	Player.Logic(Scene.GetMap());

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
	Player.Draw(Data.GetID(IMG_PLAYER));

	glutSwapBuffers();
}
