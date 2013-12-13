#include "TestStuff.h"
//hi just a test to make sure github is working // its working Jake
Gun* gunz[19];
int gunzCount;
int weaponSelected;

void incrementCounter(int index, string text) {
	weaponSelected = 4+index;
	int needed = (weaponSelected - 4) / 3 * 1000;

	if (true) {
		controlState++;
		mode = PLAY;
	} else {
		stringstream ss;
		ss << "You need ";
		ss << needed;
		ss << " points to obtain this gun. You currently have ";
		ss << totalScore;
		ss << " points.";

		MessageBox(NULL, ss.str().c_str(), "Not There Yet, Bud", MB_OK);
	}
}
void endGameNow(int a, string b){
	PostQuitMessage(0);
}

TestStuff::TestStuff()
{
	this->load();

	for(int i =0; i <10; i++)
	{
		doneAchievements[i]=false;
	}
	recentAchievement="No achievements yet";          


	totalScore = 0;
	
	gameTime = 180;
	currentLevel=0;
	endGame = false;
	infiniteTime = false;
	score = 0;
	controlState = 1;
	numLevels = 3;
	currentLevel=0;
	levels = new LMap*[this->numLevels];
	mode = MENU;

//Turret Gun
	gunz[0] = new Gun(1, 300, 500, 2000, 1000, 0, 0, 0.01, 0, ONE);
	//AI weapons
	gunz[1] = new Gun(10, 10*60, 500, 1000, 1000, 0, 15, 0.01, 0, ONE);
	gunz[2] = new Gun(20, 5*60, 500, 1500, 1000, 0, 10, 0.01, 1, ONE);
	gunz[3] = new Gun(15, 5*60*60, 500, 600, 1000, 0, 20, 1.5, 0, ONE);
	//Tear 1 weapons
	gunz[4] = new Gun(1, 10*60, 500, 1000, 1000, 0, 15, 0.01, 0, ONE);
	gunz[5] = new Gun(2, 15*60, 500, 1500, 1000, 0, 10, 0.01, 1, ONE);
	gunz[6] = new Gun(1, 5*60*60, 500, 600, 1000, 0, 20, 0.5, 0, ONE);
	//Tear 2 weapons
	gunz[7] = new Gun(15, 10*60, 500, 1000, 1000, 0, 15, 0.01, 0, ONE);
	gunz[8] = new Gun(25, 15*60, 500, 1500, 1000, 0, 10, 0.01, 1, ONE);
	gunz[9] = new Gun(7, 10*60*60, 500, 600, 1000, 0, 20, 0.5, 0, ONE);
	//Tear 3 weapons
	gunz[10] = new Gun(2, 120*60, 500, 600, 1400, 0, 15, 0.01, 0, ONE);
	gunz[11] = new Gun(23, 50*60, 500, 1000, 1300, 0, 4, 0.01, 7, ONE);
	gunz[12] = new Gun(9, 15*60*60, 500, 600, 1000, 0, 20, 0.4, 0, ONE);
	//Tear 4 weapons
	gunz[13] = new Gun(110, 3*60, 500, 1000, 1500, 0, 5, 0.01, 0, ONE);
	gunz[14] = new Gun(301, 1*60, 500, 2000, 2500, 0, 0, 0.01, 1, ONE);
	gunz[15] = new Gun(30, 20*60*60, 300, 400, 1200, 0, 10, 1.0, 20, ONE);
	//Tear 5 weapons
	gunz[16] = new Gun(5, 10*60*60, 500, 2000, 2000, 0, 15, 0.01, 0, ONE);
	gunz[17] = new Gun(5, 10*60*60, 500, 2000, 300, 0, 180, 0.01, 0, ONE);
	gunz[18] = new Gun(200, 40*60, 500, 2000, -1400, 0, 3, 0.01, 0, ONE);

	gunzCount = 19;

}

TestStuff::~TestStuff()
{
	if(testMag > 0)
	{
		//delete testMag;
	}
	if(testProjectile > 0)
	{
		//delete testProjectile;
	}
	delete levels[numLevels-1];
	for(int i(0); i < gunzCount; i++)
	{
		delete gunz[i];
	}
}

void TestStuff::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

//Create the menu
	menu = new Menu(this, graphics);

	//Teir 1
	gunList.push_back(MenuItem("Broken Old Reliable (Auto) - Fire Rate: 10 rps, Damage: 1, Accuracy: Low", menuNS::ALIGN_CENTER, true, incrementCounter));
	gunList.push_back(MenuItem("Damagaed Little Awesome (Semi) - Fire Rate: 15 rps, Damage: 2, Accuracy: Medium", menuNS::ALIGN_CENTER, incrementCounter));
	gunList.push_back(MenuItem("Deceased Schrodinger Shotgun (Auto) - Pellets: 5, Damage: 1, Accuracy: Very Low", menuNS::ALIGN_CENTER, incrementCounter));
	//Teir 2
	gunList.push_back(MenuItem("Old Reliable (Auto) - Fire Rate: 10 rps, Damage: 15, Accuracy: Low", menuNS::ALIGN_CENTER, incrementCounter));
	gunList.push_back(MenuItem("Little Awesome (Semi) - Fire Rate: 15 rps, Damage: 25, Accuracy: Medium", menuNS::ALIGN_CENTER, incrementCounter));
	gunList.push_back(MenuItem("Schrodinger Shotgun (Auto) - Pellets: 10, Damage: 7, Accuracy: Very Low", menuNS::ALIGN_CENTER, incrementCounter));
	//Teir 3
	gunList.push_back(MenuItem("The Destructinator (Auto) - Fire Rate: 120 rps, Damage: 2, Accuracy: Low", menuNS::ALIGN_CENTER, incrementCounter));
	gunList.push_back(MenuItem("The Nemesis (Burst 7) - Fire Rate: 50 rps, Damage: 23, Accuracy: High", menuNS::ALIGN_CENTER, incrementCounter));
	gunList.push_back(MenuItem("The Hole Punch (Auto) - Pellets: 15, Damage: 9, Accuracy: Very Low", menuNS::ALIGN_CENTER, incrementCounter));
	//Teir 4
	gunList.push_back(MenuItem("Doom Rhino (Auto) - Fire Rate: 3 rps, Damage: 110, Accuracy: High", menuNS::ALIGN_CENTER, incrementCounter));
	gunList.push_back(MenuItem("Galloping Slinger (Semi) - Fire Rate: 1 rps, Damage: 333, Accuracy: Very High", menuNS::ALIGN_CENTER, incrementCounter));
	gunList.push_back(MenuItem("Mama's Salt Shaker (Semi) - Pellets: 20, Damage: 30, Accuracy: Very Low", menuNS::ALIGN_CENTER, incrementCounter));
	//Teir 5
	gunList.push_back(MenuItem("Meteor Shower (Auto) - Fire Rate: 600 rps, Damage: 5, Accuracy: Low", menuNS::ALIGN_CENTER, incrementCounter));
	gunList.push_back(MenuItem("Super Nova (Auto) - Fire Rate: 600 rps, Damage: 5, Accuracy: DNE", menuNS::ALIGN_CENTER, incrementCounter));
	gunList.push_back(MenuItem("Moonwalker (Auto) - Fire Rate: 40 rps, Damage: 200, Accuracy: High", menuNS::ALIGN_CENTER, incrementCounter));


	MenuCol items;
	items.push_back(MenuItem("Play", menuNS::ALIGN_CENTER, true, gunList));
	items.push_back(MenuItem("Exit", menuNS::ALIGN_CENTER, endGameNow));

	menu->initialize(items);

//Create the animated background
	background = new Background(this, graphics);
	background->initialize(180.0);

//Create the health bar
	healthBar = new HealthBar(this, graphics);
	healthBar->initialize();

//Create the HUD
	hud = new Hud(this, graphics);
	hud->initialize();

	audio->playCue(MUSIC);

	if(hudFont.initialize(graphics, 15, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	if(!targetTexture.initialize(graphics,TARGET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing target texture"));

	if(!terrainTexture.initialize(graphics,NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing terrain texture"));

	if (!gunTM.initialize(graphics,"pictures\\AssultRifle(128x32).png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));

	if (!turretTexture.initialize(graphics,NEBULA_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret texture"));

    // Weapon texture
    if (!magTM.initialize(graphics,"pictures\\mag(8x8).png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mag texture"));

    // Projectile textures
    if (!projectileTM.initialize(graphics,"pictures\\projectile(8x8).png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing projectile textures"));

    if (!gunIM.initialize(graphics,0,0,0,&gunTM))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun"));

    if (!magIM.initialize(graphics,0,0,0,&magTM))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mag"));

	if (!projectileIM.initialize(graphics,0,0,0,&projectileTM))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing projectile"));

	//testGun->setX(100);
	//testGun->setY(100);

	/*testTerrain = new StraightPath(5,1000,VECTOR2(100,100));
	if (!testTerrain->initialize(this, &terrainTexture,1))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the terrain object");*/
	TutorialLevel* intro = new TutorialLevel(input,graphics);
	levels[0] = reinterpret_cast<LMap*>(intro);
	ArenaLevel* arena = new ArenaLevel(input,graphics, 20);
	levels[1] = reinterpret_cast<LMap*>(arena);
	BossLevel* boss = new BossLevel(input,graphics);
	levels[2] = reinterpret_cast<LMap*>(boss);
	auto testMap = levels[currentLevel];

	fileNames[0] = "maps//introLevel.txt";
	fileNames[1] = "maps//faceOff.txt";
	fileNames[2] = "maps//boss.txt";
	fileNames[3] = "maps//level4.txt";
	fileNames[4] = "maps//level5.txt";
	currentLevel = 0;
	this->buildFromFile(fileNames[currentLevel]);
	

	for(int i(0); i < gunzCount; i++)
	{
		gunz[i]->initialize(this, 128, 32, entityNS::NONE, &gunTM);
	}
	Character* c = new Character(this,graphics);
	testMap->addCharacter(c);
	/*AI* a = new AI(this,graphics);
	testMap->addCharacter(a);
	a = new AI(this,graphics);
	testMap->addCharacter(a);
	a = new AI(this,graphics);
	testMap->addCharacter(a);
	a = new AI(this,graphics);
	testMap->addCharacter(a);
	a = new AI(this,graphics);
	testMap->addCharacter(a);*/
	testProjectile = new Projectile(&projectileTM, this, 32, 8, entityNS::CIRCLE, 1);
	testMag = new Magazine(30000,5,5,0,0,0,ONE,testProjectile);
	//testProjectile->init
	if (!testMap->initialize(this,0,0,0,&terrainTexture,&targetTexture,&this->turretTexture,testMag))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the LMap object");
	levels[currentLevel]->testProjectile = testProjectile;

	for (int i = 1; i < testMap->totalCharacters; i++) {
		reinterpret_cast<AI*>(testMap->characters[i])->giveInfo(testMap->totalCharacters,testMap->characters,testMap->addedElements,testMap->terrain);
	}
	oldTargets = testMap->activeTargets;

//Add the alides
	slides = new Slides(this, graphics);
	slides->addImage("pictures\\splash.jpg");
	slides->addImage("pictures\\controls.png");
	slides->addImage("pictures\\splash-1.jpg");
	slides->addImage("pictures\\splash-2.jpg");
	slides->addImage("pictures\\splash-3.jpg");
	slides->initialize();
}

void TestStuff::update()
{
	LMap* testMap = levels[currentLevel];
	if(controlState == -1) {
		return;
	}

	if (controlState == 1 || controlState == 3 || controlState == 6 || controlState == 9) {
		menu->update(frameTime);
		return;
	}

	if (controlState == 2 || controlState == 3 || controlState == 5 || controlState == 6 || controlState == 8 || controlState == 9) {
		slides->update(frameTime);
		return;
	}

	if(endGame) {
		controlState = -1;
	}
	background->update(frameTime);
	healthBar->setX(100.0f);
	healthBar->setY(100.0f);
	healthBar->update(frameTime);
	hud->update(frameTime);
	slides->update(frameTime);
	if(!infiniteTime)
		gameTime -= frameTime;
	Character* player = testMap->characters[0];
	Camera* camera = testMap->camera;
	D3DXVECTOR2 mouseRealPos = testMap->camera->getRealPos(player->cursor->getCenterX(), player->cursor->getCenterY());
	//make it change angle for all characters you control
	for(int i = 0; i < 1; i++)
	{
		testMap->characters[i]->aimAngle = atan2(mouseRealPos.y-testMap->characters[i]->getCenterY(), mouseRealPos.x-testMap->characters[i]->getCenterX());
	}
	//testGun->act(frameTime, input->getMouseLButton(), input->getMouseRButton(), false, false, false);

	//bounds mouse
	D3DXVECTOR2 mousePos(camera->getRealPos(input->getMouseX(), input->getMouseY()));
	if(camera->centerPosition.y + (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->height/2) < mousePos.y)
	{
		if(mousePos.y - (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->height/2) < testMap->maxY - (1/camera->zoom)*(camera->height/2))
		{
			camera->centerPosition.y = mousePos.y - (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->height/2);
		}else
		{
			camera->centerPosition.y = testMap->maxY - (1/camera->zoom)*(camera->height/2);
		}
	}
	else if(camera->centerPosition.y - (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->height/2) > mousePos.y)
	{
		//camera->centerPosition.y = player->corners[0].y + (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->height/2);
		if(mousePos.y + (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->height/2) > testMap->minY + (1/camera->zoom)*(camera->height/2))
		{
			camera->centerPosition.y = mousePos.y + (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->height/2);
		}else
		{
			camera->centerPosition.y = testMap->minY + (1/camera->zoom)*(camera->height/2);
		}
	}
	///X Bounds
	if(camera->centerPosition.x + (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->width/2) < mousePos.x)
	{
		if(mousePos.x - (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->width/2) < testMap->maxX - (1/camera->zoom)*(camera->width/2))
		{
			camera->centerPosition.x = mousePos.x - (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->width/2);
		}else
		{
			camera->centerPosition.x = testMap->maxX - (1/camera->zoom)*(camera->width/2);
		}
	}
	else if(camera->centerPosition.x - (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->width/2) > mousePos.x)
	{
		//camera->centerPosition.y = player->corners[0].y + (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->height/2);
		if(mousePos.x + (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->width/2) > testMap->minX + (1/camera->zoom)*(camera->width/2))
		{
			camera->centerPosition.x = mousePos.x + (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->width/2);
		}else
		{
			camera->centerPosition.x = testMap->minX + (1/camera->zoom)*(camera->width/2);
		}
	}

	//The camera boxing
	//int cameraTop(camera->centerPosition.y - (1/camera->zoom)*(camera->height/2));
	//int cameraBottom(camera->centerPosition.y + (1/camera->zoom)*(camera->height/2));
	//Y bound
	if(camera->centerPosition.y + (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->height/2) < player->corners[1].y)
	{
		if(player->corners[1].y - (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->height/2) < testMap->maxY - (1/camera->zoom)*(camera->height/2))
		{
			camera->centerPosition.y = player->corners[1].y - (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->height/2);
		}else
		{
			camera->centerPosition.y = testMap->maxY - (1/camera->zoom)*(camera->height/2);
		}
	}
	else if(camera->centerPosition.y - (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->height/2) > player->corners[0].y)
	{
		//camera->centerPosition.y = player->corners[0].y + (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->height/2);
		if(player->corners[0].y + (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->height/2) > testMap->minY + (1/camera->zoom)*(camera->height/2))
		{
			camera->centerPosition.y = player->corners[0].y + (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->height/2);
		}else
		{
			camera->centerPosition.y = testMap->minY + (1/camera->zoom)*(camera->height/2);
		}
	}
	///X Bounds
	if(camera->centerPosition.x + (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->width/2) < player->corners[2].x)
	{
		if(player->corners[2].x - (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->width/2) < testMap->maxX - (1/camera->zoom)*(camera->width/2))
		{
			camera->centerPosition.x = player->corners[2].x - (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->width/2);
		}else
		{
			camera->centerPosition.x = testMap->maxX - (1/camera->zoom)*(camera->width/2);
		}
	}
	else if(camera->centerPosition.x - (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->width/2) > player->corners[0].x)
	{
		//camera->centerPosition.y = player->corners[0].y + (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->height/2);
		if(player->corners[0].x + (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->width/2) > testMap->minX + (1/camera->zoom)*(camera->width/2))
		{
			camera->centerPosition.x = player->corners[0].x + (1/camera->zoom)*teststuffNS::cameraMinBorder*(camera->width/2);
		}else
		{
			camera->centerPosition.x = testMap->minX + (1/camera->zoom)*(camera->width/2);
		}
	}
	
	/*if(testMap->activeTargets == 0)
	{
		testMap->targetsDestroyed=true;
		testMap->levelDone = true;
	}*/

	testMap->update(frameTime);

	if(gameTime<=0)
	{
		endGame = true;
		return;
	}

	if(testMap->levelDone)
	{
		totalScore+=levels[currentLevel]->levelScore;
		currentLevel++;
		controlState++;
		if(currentLevel >= 3)
		{
			endGame = true;
			addScore(totalScore);
			save();
			controlState = -1;
			return;
		}
		delete testMap;
		
		mode = STORY;
		testMap = levels[currentLevel];
		this->buildFromFile(fileNames[currentLevel]);
		Character* c = new Character(this,graphics);
		testMap->addCharacter(reinterpret_cast<Character*>(c));
		//c->initialize();
		//WeaponStuff
		if(currentLevel == 1)
		{
			testMag = new Magazine(30000, 40000, 40000, 1, 100, 103, ONE, testProjectile); 
			testGun = new Gun(50, 700, 100, 2000, 1000, 100, 5, 2.0, 0, ONE);
			testGun->loadNewMag(testMag);
		}else if(currentLevel == 2){
			testMag = new Magazine(30000, 40000, 40000, 1, 100, 120, ONE, testProjectile); 
			testGun = new Gun(300, 1200, 100, 2000, 1000, 100, 3, 2.0, 7, ONE);
			testGun->loadNewMag(testMag);
		}else if(currentLevel == 3){
			testMag = new Magazine(30000, 40000, 40000, 1, 100, 130, ONE, testProjectile); 
			testGun = new Gun(1000, 3*60, 100, 2000, 2000, 100, 0, 2.0, 1, ONE);
			testGun->loadNewMag(testMag);
		}else if(currentLevel == 4){
			testMag = new Magazine(30000, 40000, 40000, 1, 100, 103, ONE, testProjectile); 
			testGun = new Gun(10, 20*60*60, 100, 2000, 1000, 100, 30, 2.0, 0, ONE);
			testGun->loadNewMag(testMag);
		}

		testGun->initialize(this, 128, 32, entityNS::NONE, &gunTM);

		if(currentLevel==1)
		{
			
			AI* a = new AI(this,graphics);
			testMap->addCharacter(a);
			a = new AI(this,graphics);
			testMap->addCharacter(a);
			a = new AI(this,graphics);
			testMap->addCharacter(a);
			a = new AI(this,graphics);
			testMap->addCharacter(a);
			a = new AI(this,graphics);
			testMap->addCharacter(a);
			if (!testMap->initialize(this,0,0,0,&terrainTexture,&targetTexture,&projectileTM))
				throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the LMap object");
			for (int i = 1; i < testMap->totalCharacters; i++) {
				if(testMap->characters[i]!=0)reinterpret_cast<AI*>(testMap->characters[i])->giveInfo(testMap->totalCharacters,testMap->characters,testMap->addedElements,testMap->terrain);
			}
		}
		if(currentLevel==2)
		{
			AI* boss = new AI(this,graphics,3333);
			testMap->addCharacter(boss);
			reinterpret_cast<AI*>(testMap->characters[1])->giveInfo(testMap->totalCharacters,testMap->characters,testMap->addedElements,testMap->terrain);
			if (!testMap->initialize(this,0,0,0,&terrainTexture,&terrainTexture,&turretTexture,testMag))
				throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the LMap object");
		}
		levels[currentLevel]->testProjectile = testProjectile;
		for(int i = 0; i < testMap->totalCharacters; i++)
		{
			if(testMap->characters[i]!=0)
			{
				testMap->characters[i]->currentWeapon = testGun;
				testMap->characters[i]->currentMag = testMag;
				testMap->mags[i] = testMag;
			}
		}
	}
	if(oldTargets > testMap->activeTargets)
	{
		score += oldTargets-testMap->activeTargets;
		audio->playCue(TARGET_SHATTER);
	}
	oldTargets = testMap->activeTargets;
	this->achievements();
}

void TestStuff::ai()
{}

void TestStuff::collisions()
{
	//testMap->collision();
}

void TestStuff::render()
{
	auto testMap = levels[currentLevel];

	graphics->spriteBegin();
	graphics->setBackColor(graphicsNS::GRAY);
	slides->disable();
	
	if(controlState==-1)
	{
		PostQuitMessage(0);
		return;
	}

//Interrupt for menus and stories
	if (controlState == 1) {
		slides->enable();
		slides->setSlide(0);
		slides->draw();

		menu->draw();
		return;
	}

	if (controlState == 2 || controlState == 3) {
		slides->enable();
		slides->setSlide(controlState - 1);
		slides->draw();

		if (!down && (input->anyKeyPressed() || input->getMouseLButton())) {
			controlState++;
			return;
		}

		if (down && !input->anyKeyPressed() && !input->getMouseLButton()) {
			down = false;
		}

		return;
	}

	if (controlState == 5 || controlState == 6) {
		slides->enable();
		slides->setSlide(3);
		slides->draw();

		if (!down && (input->anyKeyPressed() || input->getMouseLButton()) && controlState == 5) {
			controlState++;
			return;
		}

		if (down && !input->anyKeyPressed() && !input->getMouseLButton()) {
			down = false;
		}

		if (controlState == 6) {
			menu->draw();
		}

		return;
	}

	if (controlState == 8 || controlState == 9) {
		slides->enable();
		slides->setSlide(4);
		slides->draw();

		if (!down && (input->anyKeyPressed() || input->getMouseLButton())) {
			controlState++;
			return;
		}

		if (down && !input->anyKeyPressed() && !input->getMouseLButton()) {
			down = false;
		}

		if (controlState == 9) {
			menu->draw();
		}

		return;
	}

	background->draw();

	testMap->draw();
	hud->setHealth(testMap->characters[0]->healthPoints/300.0);
	hud->setTime(testMap->mapTime/testMap->mapStartTime);
	hud->setReload(1);

	hud->draw();
	std::stringstream tempWords;
	tempWords.str("");
	tempWords << recentAchievement.c_str();
	hudFont.print(tempWords.str().c_str(), 800, 550); 
	if(currentLevel==1)
	{
		tempWords << "Kills: " << levels[currentLevel]->numKills;
		hudFont.print(tempWords.str().c_str(), 500, 550); 
	}

	tempWords.str("");
	tempWords << "Score: " << (totalScore + levels[currentLevel]->levelScore);
 	hudFont.print(tempWords.str().c_str(), 100, 550);
	//healthBar->draw();
	graphics->spriteEnd();
}

void TestStuff::releaseAll()
{
	terrainTexture.onLostDevice();
	Game::releaseAll();
}

void TestStuff::resetAll()
{
	terrainTexture.onResetDevice();
	Game::resetAll();
}

void TestStuff::buildFromFile(std::string fileName)
{
	LMap* testMap = levels[currentLevel];
	fstream fin;
	fin.open(fileName);
	string line = "";
	float zoom;
	getline(fin,line);
	zoom = atof(line.c_str());
	testMap->camera->zoom;
	getline(fin,line);
	int numTerrain = atoi(line.c_str());
	this->terrainNumToPrint = numTerrain;
	getline(fin,line);
	int numSpawn = atoi(line.c_str());
	this->spawnNumToPrint = numSpawn;
	int height = 0, width = 0, x = 0, y = 0;
	double degree = 0;
	DWORD color;
	int i = 1, health = 0;
	getline(fin,line);
	while(!fin.fail() && line != "--")
	{
		//it is reading in terrain spots
		if(i<=numTerrain)
		{
			height = atoi(line.c_str());
			getline(fin,line);
			width = atoi(line.c_str());
			getline(fin,line);
			x = atoi(line.c_str());
			getline(fin,line);
			y = atoi(line.c_str());
			getline(fin,line);
			degree = atof(line.c_str());
			getline(fin,line);
			color = std::strtoul(line.c_str(),0,10);
			TerrainElement* t = new TerrainElement(height,width,VECTOR2(x,y));
			t->setDegrees(degree);
			t->initialize(this,&terrainTexture,0);
			t->color = color;
			t->generateSideEquations();
			testMap->addTerrain(t);		
		}
		else if(i<=numSpawn + numTerrain)
		{
			x = atoi(line.c_str());
			getline(fin,line);
			y = atoi(line.c_str());
			TerrainElement* t = new TerrainElement(50,50,VECTOR2(x,y));
			t->initialize(this,&terrainTexture,0);
			t->color = graphicsNS::RED;
			testMap->addSpawnPoint(t);
		}
		else//assume the rest are targets
		{
			x = atoi(line.c_str());
			getline(fin,line);
			y = atoi(line.c_str());
			getline(fin,line);
			color = std::strtoul(line.c_str(),0,10);
			getline(fin,line);
			health = atoi(line.c_str());
			TerrainElement* t = new TerrainElement(64,64,VECTOR2(x,y));
			t->initialize(this,&targetTexture,0);
			t->setHealth(health);
			t->color = color;
			t->generateSideEquations();
			testMap->addTarget(t);
		}
		getline(fin,line);
		i++;
	}
}

void TestStuff::achievements()
{
	if(!doneAchievements[0] && currentLevel==1)
	{
		this->recentAchievement="Knowedgable: completed tutorial";
		doneAchievements[0]=true;
		totalScore+=500;
	}
	if(!doneAchievements[1] && currentLevel==2)
	{
		this->recentAchievement="Warrior's tale: completed arena";
		doneAchievements[1]=true;
		totalScore+=500;
	}
	if(!doneAchievements[2] && currentLevel==3)
	{
		this->recentAchievement="The End? Beat the champion";
		doneAchievements[2]=true;
		totalScore+=500;
	}
	if(!doneAchievements[3] && levels[currentLevel]->activeTargets==0)
	{
		this->recentAchievement="Grover Achiever: Break all targets";
		doneAchievements[3]=true;
		totalScore+=500;
	}
	if(!doneAchievements[4] && totalScore>9000)
	{
		this->recentAchievement="Dr. Adams: OVER 9000!";
		doneAchievements[4]=true;
		totalScore+=500;
	}
	/*if(!doneAchievements[5] && true)
	{
		this->recentAchievement="12345";
		doneAchievements[5]=true;
		totalScore+=500;
	}
	if(!doneAchievements[6] && true)
	{
		this->recentAchievement="23456";
		doneAchievements[6]=true;
	}
	if(!doneAchievements[7] && true)
	{
		this->recentAchievement="34567";
		doneAchievements[7]=true;
	}
	if(!doneAchievements[8] && true)
	{
		this->recentAchievement="45678";
		doneAchievements[8]=true;
	}
	if(!doneAchievements[9] && true)
	{
		this->recentAchievement="56789";
		doneAchievements[9]=true;
	}*/
}

void TestStuff::consoleCommand()
{
	std::string command = console->getCommand();
	if(command == "")
		return;
	if(command == "skip_level")
	{
		levels[currentLevel]->levelDone = true;
		//controlState++;
		return;
	}
	if(command == "infinite_time")
	{
		infiniteTime=!infiniteTime;
		return;
	}
}

void TestStuff::save()
{
	std::ofstream fout;
	std::stringstream s;
	scoreString = "";
	fout.open("scores.txt");
	for(int i(0); i < 9; i++)
	{
		fout << scores[i] << std::endl;
		if(i == scoreIndex)
		{
			s << "*";
		}
		s << i+1 << ": " <<scores[i] << std::endl;
		
	}
	scoreString = s.str();
	fout.close();
}
void TestStuff::load()
{
	std::ifstream fin;
	fin.open("cowScores.cow");
	if(!fin.fail())
	{
		int temp;
		for(int i(0); i < 10; i++)
		{
			fin >> temp;
			scores[i] = temp;
		}

		fin.close();
	}else{
		fin.close();
		std::ofstream fout;
		fout.open("cowScores.cow");
		for(int i(0); i < 10; i++)
		{
			fout << "0\n";
			scores[i] = 0;
		}
		fout.close();
	}
}
void TestStuff::addScore(int in)
{
	scoreIndex = 11;
	for(int i(0); i < 10; i++)
	{
		if(scores[i] < in)
		{
			if(i < scoreIndex)
			{
				scoreIndex = i;
			}
			std::swap(scores[i], in);
		}
	}
}