#include "Screens.h"



Screens::Screens()
{
}


Screens::~Screens()
{
}


bool Screens::Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);

	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	bool res = true;
	res = Data.LoadImage(IMG_BACK_MAIN, "startBack.png", GL_RGBA);
	if (!res) return false;
}


bool Screens::Loop()
{
	bool res = true;
	double t1, t2;

	t1 = glutGet(GLUT_ELAPSED_TIME);
	//if (offsetCamera < Scene.BACK_WIDTH_DRAW - GAME_WIDTH) ++offsetCamera;
	//else { Player.endLevel = true; Player2.endLevel = true; }
	res = Process();
	if (res) Render();

	//1000/20 = 50fps
	do {
		t2 = glutGet(GLUT_ELAPSED_TIME);
	} while (t2 - t1 < 20);

	return res;
}


bool Screens::Process()
{
	bool res = true;
	res = tratarKeys();
	return res;
}

void Screens::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);//no s para que sirve pero no hace falta

	//Scene.DrawBackground(Data.GetID(IMG_BACK));
	//Scene.Draw(Data.GetID(IMG_PARED));
	//render_info();
	glutSwapBuffers();
}


inline bool Screens::tratarKeys()
{
	bool res = true;

	return res;
}


//Input
void Screens::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}





void Screens::ReadKeySpecialBoard(unsigned char key, int x, int y, bool press)
{
	sKeys[key] = press;
}





void Screens::ReadMouse(int button, int state, int x, int y)
{
}



inline void render_info(int p1, int p2, int offset) //dberiamos pasarle el string
{
	//glEnable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_2D);

	std::string pl1 = "";
	char str[20];
	pl1 += "PLAYER 1 - ";
	pl1 += _itoa(p1, str, 10);
	int j = pl1.length();


	glColor3f(0, 1, 1);
	glRasterPos2f(80 + offset, 450); //mientras el texto este visible en pantalla, se muestra, si se va a cortar un trozo deja de pintarlo
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, pl1[i]);
	}

	std::string pl2 = "";
	pl2 += "PLAYER 2 - ";
	pl2 += _itoa(p2, str, 10);
	j = pl2.length();

	glColor3f(0, 1, 1);
	glRasterPos2f(400 + offset, 450); //mientras el texto este visible en pantalla, se muestra, si se va a cortar un trozo deja de pintarlo
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, pl2[i]);
	}

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	//delete sstring;
}