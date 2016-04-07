#include "Screens.h"



Screens::Screens()
{
	play1 = 19;
	play2 = 21;
	help = 23;
	credits = 25;
	screenToRender = 0;//0 = main, 1 = instr, 2 = credits, 3 = game, 4 = gameover
}


Screens::~Screens()
{
}


bool Screens::Init(int* gam)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);

	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);
	this->gam = gam;
	bool res = true;
	res = Data.LoadImage(IMG_BACK_MAIN, "startBackground.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(BT_PLAY1, "btnPlay1.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(BT_PLAY1_FOC, "btnPlay1Focus.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(BT_PLAY2, "btnPlay2.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(BT_PLAY2_FOC, "btnPlay2Focus.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(BT_HELP, "btnHelp.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(BT_HELP_FOC, "btnHelpFocus.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(BT_CREDITS, "credits.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(BT_CREDITS_FOC, "creditsFocus.png", GL_RGBA);
	if (!res) return false;
	return res;
}


inline void Screens::Collides(int state, int x, int y)
{
	//check if it is on buttons bounds
	if (x > 250 && x < 250 + 144 &&
		y < 380 && y > 200 - 47) {
		if ((y < 380) && (y > 380 - 47)) {
			if (state == 0) play1 = 20;
			else {
				//*gam = 0;
				screenToRender = 3;
			}
			//else play1--;
		}
		/*else if ((y < 320) && (y > 320 - 47)) {
			if (state == 0) play2 = 22;
			else {
				*gam = 1;
				screenToRender = 3;
			}
			//else play1--;
		}*/
	}
}



bool Screens::Process(int state, int x, int y)
{
	bool res = true;
	if (state != -1) {
		Collides(state, x, 512-y);
		if (state == 1) {
			play1 = 19;
			play2 = 21;
			help = 23;
			credits = 25;
		}
		
	}
	return res;
}

void Screens::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);//no s para que sirve pero no hace falta

	Scene.DrawBackgroundNormal(Data.GetID(IMG_BACK_MAIN));
	if (screenToRender == 0) {
		DrawRect(play1, 250, 380);
		DrawRect(play2, 250, 320);
		DrawRect(help, 250, 260);
		DrawRect(credits, 250, 200);
	}
	//render_info();
	glutSwapBuffers();
}




void Screens::DrawRect(int tex_id, int xo, int yo)
{

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);	glVertex2i(xo,yo);
	glTexCoord2f(0, 1);	glVertex2i(xo , yo-47);
	glTexCoord2f(1, 1);	glVertex2i(xo+144, yo-47);
	glTexCoord2f(1, 0);	glVertex2i(xo+144, yo );
	glEnd();

	glDisable(GL_TEXTURE_2D);
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