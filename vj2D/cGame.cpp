#include "cGame.h"
#include "Globals.h"
#include "cVoladorEstatico.h"
#include "cVoladorMariposa.h"


cGame::cGame(int type)
{
	offsetCamera = 0;
	this->type = 1;
	Player.setID(1);
	if (type == 1)Player2.setID(2);
	srand(time(0));
	level = 1;
}

cGame::~cGame(void)
{
}



inline void render_info(int p1, int p2, int offset,int type =0) //dberiamos pasarle el string
{
	//glEnable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_2D);

	std::string pl1 = "";
	char str[20];
	pl1 += "PLAYER 1 - ";
	pl1 += _itoa(p1, str, 10);
	int j = pl1.length();


	glColor3f(0, 1, 1);
	glRasterPos2f(40 + offset, 480); //mientras el texto este visible en pantalla, se muestra, si se va a cortar un trozo deja de pintarlo
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, pl1[i]);
	}
	if (type == 1) {
		std::string pl2 = "";
		pl2 += "PLAYER 2 - ";
		pl2 += _itoa(p2, str, 10);
		j = pl2.length();
		glColor3f(0, 1, 1);
		glRasterPos2f(480 + offset, 480); //mientras el texto este visible en pantalla, se muestra, si se va a cortar un trozo deja de pintarlo
		for (int i = 0; i < j; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, pl2[i]);
		}
	}

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	//delete sstring;
}





bool cGame::Init()
{
	
	bool res=true;
	offsetCamera = 0;
	rafagaQueToca = 0;
	Player.setID(1);
	if (type == 1) Player2.setID(2);
	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);
	
	level ; //nos lo pasaran desde el menu de escoger partida

	//Scene initialization
	//res = Data.LoadImage(IMG_BLOCKS,"blocks.png",GL_RGBA);
	//if(!res) return false;
	if (level == 1) {
		bool res = true;
		res = Data.LoadImage(IMG_PARED, "backTiles1.png", GL_RGBA);
		if (!res) return false;
		res = Data.LoadImage(IMG_BACK, "back1.png", GL_RGBA);
		if (!res) return false;
		res =  loadResources(1);
		if (!res) return false;
		Scene.tilesFila = 16; //porque el texture mide 512 y caben 16 tiles de 32
		Scene.BACK_HEIGHT = 512;
		Scene.BACK_WIDTH_DRAW = 2560; //tamano en horizontal dl background
		//[numRafaga][0-3], 0 = tile x, 1 = y, 2 = tipo, 3 = numBichos
		numRafagas = 6;
		rafagasBichos.resize(numRafagas, vector<int>(4)); //3 rafagas, cada rafaga tiene 4 atributos (x,y,tipo,num)
		rafagasBichos[0] = { 25, 10, 0, 2 }; //primera rafaga
		rafagasBichos[1] = { 33, 10, 1, 3 }; //3 rafaga
		rafagasBichos[2] = { 45, 10, 0, 2 }; //2a rafaga
		rafagasBichos[3] = { 55, 8, 1, 5 }; //3 rafaga
		rafagasBichos[4] = { 65, 8, 1, 3 }; //3 rafaga
		rafagasBichos[5] = { 70,8,2,1 };
	}
	else if (level != 1) {
		bool res = true;
		res = Data.LoadImage(IMG_PARED, "backTiles2.png", GL_RGBA);
		if (!res) return false;
		res = Data.LoadImage(IMG_BACK, "back2.png", GL_RGBA);
		if (!res) return false;
		res = loadResources(2);
		if (!res) return false;
		Scene.tilesFila = 16; //porque el texture mide 512 y caben 16 tiles de 32
		Scene.BACK_HEIGHT = 512;
		Scene.BACK_WIDTH_DRAW = 2880; //tamano en horizontal dl background
									  //[numRafaga][0-3], 0 = tile x, 1 = y, 2 = tipo, 3 = numBichos
		numRafagas = 12;
		rafagasBichos.resize(numRafagas, vector<int>(4)); //3 rafagas, cada rafaga tiene 4 atributos (x,y,tipo,num)
		rafagasBichos[0] = { 20, 10, 0, 6 }; //primera rafaga
		rafagasBichos[1] = { 27, 10, 1, 6 }; //3 rafaga
		rafagasBichos[2] = { 31, 10, 0, 7 }; //2a rafaga
		rafagasBichos[3] = { 35, 8, 1, 17 }; //3 rafaga
		rafagasBichos[4] = { 42, 10, 0, 4 }; //primera rafaga
		rafagasBichos[5] = { 50, 10, 1, 16 }; //3 rafaga
		rafagasBichos[6] = { 54, 10, 0, 3 }; //2a rafaga
		rafagasBichos[7] = { 60, 8, 0, 6 }; //3 rafaga*/
		rafagasBichos[8] = { 63, 8, 1, 4 }; //3 rafaga*/
		rafagasBichos[9] = { 65, 8, 0, 4 }; //3 rafaga*/
		rafagasBichos[10] = { 71, 8, 1, 5 }; //3 rafaga*/
		rafagasBichos[11] = { 76, 2, 2, 1 }; 
	}


	res = Scene.LoadLevel(level);
	if(!res) return false;

	
	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"naves.png",GL_RGBA);
	if(!res) return false;
	Player.SetWidthHeight(64,32);
	Player.SetTile(1,8);
	Player.SetState(STATE_CENTER);

	if (type == 1) {
		res = Data.LoadImage(IMG_PLAYER2, "navesp2.png", GL_RGBA);
		if (!res) return false;
		Player2.SetWidthHeight(64, 32);
		Player2.SetTile(1, 10);
		Player2.SetState(STATE_CENTER);
	}
	
	//PlaySound(TEXT("forest.mid"), NULL, SND_FILENAME);
	res = Screen.Init(&type);
	return res;
}







bool cGame::Loop()
{

	bool res=true;
	double t1, t2;

	t1 = glutGet(GLUT_ELAPSED_TIME);
	
	
	if (Screen.screenToRender == 3) {
		if (offsetCamera < Scene.BACK_WIDTH_DRAW - GAME_WIDTH) ++offsetCamera;
		else { Player.endLevel = true; Player2.endLevel = true; }
		int auxt = type;
		//Player.endLevel = true; if(type ==1)Player2.endLevel = true;
		res = Process();
		if (auxt != type) reset();
	}
	else Screen.Process(-1,0,0);
	if (res) Render();

	//1000/20 = 50fps
	do {
		t2 = glutGet(GLUT_ELAPSED_TIME);
	} while (t2 - t1 < 20);

	return res;
}






void cGame::Finalize()
{
	Player =cPlayer();
	if (type ==1)Player2 = cPlayer();
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
	Screen.Process(state, x, y);
}





inline void cGame::modificaScore(int id, int amount) {
	if (id == 1) Player.modifyScore(amount);
	else if(id == 2 && type ==1) Player2.modifyScore(amount);
}




inline void cGame::monsterndBulletLogic(set<void*>& toDelete) {
	for (cEnemigo* monster : this->bichos) {
		
		if (monster->getShootable()) {
			int tx, ty; Player.GetPosition(&tx, &ty);
			int aux = rand();
			if (aux%2 == 1 && type==1) Player2.GetPosition(&tx, &ty);
			int xBicho, yBicho; monster->GetPosition(&xBicho,&yBicho);
			if (xBicho >= tx+TILE_SIZE) monster->shootBoi(pewpews, tx, ty);
		}
		monster->Logic(Scene.GetMap(level));
		for (cProyectil* pewpew : this->pewpews) {
			//luz fuego destruccion al irse de la pantalla
			int tx, ty; pewpew->GetPosition(&tx, &ty);
			bool b = pewpew->getType() == RAYO_BOSS;
			if (b) {
				double t1 = glutGet(GLUT_ELAPSED_TIME);
				if (t1 - boss->getrayoShotTimer() > 20 * boss->getDelayRayo()) {
					toDelete.insert(pewpew);

				}
			}
			if (!b && (tx < offsetCamera || tx > GAME_WIDTH + offsetCamera)) toDelete.insert(pewpew);
			else if (pewpew->getId() != 3 && pewpew->CollidesBicho(monster)) {
				pewpew->SetPosition(tx+10,ty);
				int w, h; pewpew->GetWidthHeight(&w, &h);
				pewpew->SetWidthHeight(w + 8, h + 8);
				yerDead(pewpew);
				//luz fuego destruccion si un proyectil de nave choca con un monstruo
				toDelete.insert(pewpew);
				monster->dealDamage(pewpew->getDamage());
				modificaScore(pewpew->getId(), SCORE_HIT);
				if (monster->getHealth() <= 0) {
					yerDead(monster);
					toDelete.insert(monster);
					modificaScore(pewpew->getId(), SCORE_REKT);
					monster->dropPowerup(powerUps);
				}
			}
			//si choca con una de las dos naves
			else if (pewpew->getId() == 3 && pewpew->CollidesBicho(&(cBicho)Player)) {
				//si proyectil enemigo choca con nave 1, se le resta vida, entra en godmode
				if (!b) toDelete.insert(pewpew);
				yerDead(&Player, NAVE_BOOM);
				enterGodMode(&Player);
			}
			else if (type == 1 && pewpew->getId() == 3 && pewpew->CollidesBicho(&(cBicho)Player2)) {
				if (!b) toDelete.insert(pewpew);
				yerDead(&Player2, NAVE_BOOM);
				enterGodMode(&Player2);
			}
		}
		//si bicho choca con las naves
		bool b = monster->CollidesBicho(&Player);
		if (b) enterGodMode(&Player);
		if (type == 1) {
			b = monster->CollidesBicho(&Player2);
			if (b) enterGodMode(&Player2);
		}
	}
}

inline void cGame::yerDead(cBicho * bicho, int type,int delay)
{
	int w, h, tx, ty; bicho->GetWidthHeight(&w, &h); bicho->GetPosition(&tx, &ty);
	cBoom* boom = new cBoom(type);
	boom->SetPosition(tx-7, ty); // offset of the sprite
	boom->SetWidthHeight(w+10,h+5);
	boom->setDelayBoom(delay);
	explosiones.insert(boom);
}

inline bool cGame::loadResources(int level)
{
	bool res = true;
	res = Data.LoadImage(IMG_ESTATIC, "enemyEstatico.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_MARIP, "enemigoMariposa.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_BULLET_VOLADOR, "bulletVolador.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_ENEMY_BOOM, "explosionBicho.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_SHIELD, "escudo.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_NAVE_BOOM, "explosionNave.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_SHIELD_POWER, "shieldPower.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_BULLET_POWER, "bulletPower.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_PLAYER_BULLETS, "proyectilesNave.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_PROPULSIONES, "propulsiones.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_BOSS_ENTITY, "boss1.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_BOSS_RAYO, "balasBoss.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_PLAYER_HEARTS, "corazon.png", GL_RGBA);
	if (!res) return false;

	res = Data.LoadImage(IMG_BUB, "bub.png", GL_RGBA);
	if (!res) return false;
	return res;
}



inline void cGame::enterGodMode(cPlayer* p) {
	if (!p->isjustOutShield() && !p->getMode()) {
		if (!p->getShield()) {
			p->enableGodMode();
			//si entramos en godmode es porque nos han dado => perdemos vida y boosts
			p->modifyVidas(-1);
			yerDead(p, 0, 30);
			if (p->getVidas() <= 0) p->SetPosition(0, 0);
			p->losePowers();
			if (p->getID() == 1) godModeTimer = glutGet(GLUT_ELAPSED_TIME);
			else godModeTimer2 = glutGet(GLUT_ELAPSED_TIME);
		}
		else {
			p->setShield(false); 
			p->setjustOutShield(true);
			if (p->getID() == 1) outShieldTimer = glutGet(GLUT_ELAPSED_TIME);
			else outShieldTimer2 = glutGet(GLUT_ELAPSED_TIME);
		}
	}
}






//Process
bool cGame::Process()
{
	if (type == 1 && Player.getVidas() <= 0 && Player2.getVidas() <= 0) {
		reset(); 
		Screen.t1 = glutGet(GLUT_ELAPSED_TIME);
		Screen.screenToRender = 4;
	}
	else if (type == 0 && Player.getVidas()<=0) {
		reset();
		Screen.t1 = glutGet(GLUT_ELAPSED_TIME);
		Screen.screenToRender = 4;
	}
	if (Player.endLevel && boss->getHealth() <= 0) {
		level = 2;
		reset();
	}
	bool res = true;
	res = tratarKeys();
	//Logica proyectiles + colisiones Proyectiles
	for (cProyectil* pewpew : this->pewpews)
		pewpew->Logic(Scene.GetMap(level));
	set<void*> toDelete;
	monsterndBulletLogic(toDelete);
	
	//gestion godtimers y outshieldtimers
	double t1 = glutGet(GLUT_ELAPSED_TIME);
	//si ha pasado 200 frames, desactiva el godmode
	if (t1 - godModeTimer > 200 * 20) Player.disableGodMode();
	if (type == 1 && t1 - godModeTimer2 > 200 * 20) Player2.disableGodMode();
	if (t1 - outShieldTimer > 100 * 20) Player.setjustOutShield(false);
	if (type == 1 && t1 - outShieldTimer2 > 100 * 20) Player2.setjustOutShield(false);
	//Gestion powers
	for (cPowerUp* powah : this->powerUps) {
		if (Player.CollidesBicho((cBicho*)powah)) {
			toDelete.insert(powah);
			int bType = powah->getType();
			Player.setPowerUp(bType);
		}
		if (type == 1 && Player2.CollidesBicho((cBicho*)powah)) {
			toDelete.insert(powah);
			int bType = powah->getType();
			Player2.setPowerUp(bType);
		}
	}
	//gestion explosiones
	for (cBoom* boom : explosiones) {
		//si ha passat cert temps,elimina
		double t1 = glutGet(GLUT_ELAPSED_TIME);
		//delay explo
		if (t1 - boom->getCreationTime() > 20 * boom->getDelayBoom()) 
			toDelete.insert(boom);
	}
	for (void* x : toDelete) {
		pewpews.erase((cProyectil*)x);
		bichos.erase((cEnemigo*)x);
		powerUps.erase((cPowerUp*) x);
		explosiones.erase((cBoom*)x);
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
		Player.MoveRight(Scene.GetMap(level));
		Player.MoveRight(Scene.GetMap(level));
		Player.MoveHalfRight(Scene.GetMap(level));
	}
	else if (windowTile-2 <= playerTileX) {
		Player.MoveLeft(Scene.GetMap(level));
	}
	else Player.Logic(Scene.GetMap(level));

	//Logic player2
	if (type == 1) {
		Player2.GetTile(&playerTileX, &playerTileY);
		if (cameraTile >= playerTileX) {
			Player2.MoveRight(Scene.GetMap(level));
			Player2.MoveRight(Scene.GetMap(level));
			Player2.MoveHalfRight(Scene.GetMap(level));
		}
		else if (windowTile - 2 <= playerTileX) {
			Player2.MoveLeft(Scene.GetMap(level));
		}
		else Player2.Logic(Scene.GetMap(level));
	}
	//si choca con enemigo hazte pupa por eficiencia, esta con los proyectiles

	return res;
}





//Output
void cGame::Render()
{
	if (Screen.screenToRender == 3) {
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(offsetCamera, GAME_WIDTH + offsetCamera, 0, GAME_HEIGHT, 0, 1);
		glMatrixMode(GL_MODELVIEW);//no s para que sirve pero no hace falta

		Scene.DrawBackground(Data.GetID(IMG_BACK));
		Scene.Draw(Data.GetID(IMG_PARED));
		//Proyectiles
		for (cProyectil* pewpew : this->pewpews) pewpew->Draw(&Data);
		for (cEnemigo* b : bichos) b->Draw(&Data);
		//bichos[0]->Draw(&Data);
		Player.Draw(&Data);
		if (type == 1)Player2.Draw(&Data);
		//PowerUps
		for (cPowerUp* powah : this->powerUps) powah->Draw(&Data);
		if (type == 0)
		render_info(Player.getScore(), Player2.getScore(), offsetCamera);
		else
			render_info(Player.getScore(), Player2.getScore(), offsetCamera,1);
		//explosiones
		for (cBoom* boom : explosiones) boom->Draw(&Data);
		glutSwapBuffers();
	}
	else {
		Screen.Render();
	}
}





inline bool cGame::tratarKeys()
{
	bool res = true;
	/////////////////////////////////////////////
	//Process Input
	if (sKeys[27])	res = false;
	if (sKeys[GLUT_KEY_UP])			Player.Jump(Scene.GetMap(level));
	else if (sKeys[GLUT_KEY_DOWN])	Player.MoveDown(Scene.GetMap(level));
	else Player.setMoving(false);
	if (sKeys[GLUT_KEY_LEFT])			Player.MoveLeft(Scene.GetMap(level));
	else if (sKeys[GLUT_KEY_RIGHT])	Player.MoveRight(Scene.GetMap(level));
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
	if (type == 1) {
		if (keys[KEY_W])			Player2.Jump(Scene.GetMap(level));
		else if (keys[KEY_S])	Player2.MoveDown(Scene.GetMap(level));
		else Player2.setMoving(false);
		if (keys[KEY_A])			Player2.MoveLeft(Scene.GetMap(level));
		else if (keys[KEY_D])	Player2.MoveRight(Scene.GetMap(level));
		//Si no hay nada aparetado, para el player
		if (!keys[KEY_W]
			&& !keys[KEY_S]
			&& !keys[KEY_A]
			&& !keys[KEY_D]) Player2.Stop();
		// enter = 13, shooting for player 1
		if (keys[KEY_Q])
			Player2.shoot(this->pewpews);
	}
	//TESTING BUTTONS
	if (sKeys[GLUT_KEY_F1]) Player.setPowerUp(BULLET_SIMPLE);
	if (sKeys[GLUT_KEY_F2]) Player.setPowerUp(BULLET_DOBLE);
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
				bicho = new cVoladorMariposa(i);
				bicho->SetWidthHeight(46, 50);
				bicho->SetTile(rafagasBichos[rafagaQueToca][0] + i*2, rafagasBichos[rafagaQueToca][1]);
				bichos.insert(bicho);
			}
			break;
		case 2:
			if (level != 1) boss = new cBoss(pewpews);
			else boss = new cBoss(pewpews, 1);
			bicho = boss;
			bicho->SetWidthHeight(48*2, 57*2);
			bicho->SetTile(rafagasBichos[rafagaQueToca][0], rafagasBichos[rafagaQueToca][1]);
			bichos.insert(bicho);
		}

		++rafagaQueToca;
	}
}
