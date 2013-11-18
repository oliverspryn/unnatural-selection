#include "TestStuff.h"

TestStuff::TestStuff()
{
	gameTime = 180;
	currentLevel=0;
	endGame = false;
	infiniteTime = false;
	score = 0;
	controlState = 1;
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
	delete testMap;
}

void TestStuff::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	audio->playCue(MUSIC);

	if(hudFont.initialize(graphics, 15, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	if(!targetTexture.initialize(graphics,TARGET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing target texture"));

	if(!terrainTexture.initialize(graphics,NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing terrain texture"));

	if (!gunTM.initialize(graphics,"pictures\\AssultRifle(128x32).png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));

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

	testProjectile = new Projectile(&projectileTM, this, 32, 8, entityNS::CIRCLE, 1);

	testMag = new Magazine(30000, 40000, 40000, 1, 100, 103, ONE, testProjectile); 
	testGun = new Gun(32, 16*60*60, 100, 2000, 1000, 100, 10, 2.0, 16, ONE);
	testGun->loadNewMag(testMag);
	testGun->initialize(this, 128, 32, entityNS::NONE, &gunTM);
	//testGun->setX(100);
	//testGun->setY(100);

	/*testTerrain = new StraightPath(5,1000,VECTOR2(100,100));
	if (!testTerrain->initialize(this, &terrainTexture,1))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the terrain object");*/
	testMap = new LMap(input,graphics);

	fileNames[0] = "level1.txt";
	fileNames[1] = "level2.txt";
	fileNames[2] = "level3.txt";
	fileNames[3] = "level4.txt";
	fileNames[4] = "level5.txt";
	currentLevel = 0;
	this->buildFromFile(fileNames[currentLevel]);

	Character* c = new Character(this,graphics);
	testMap->addCharacter(c);

	if (!testMap->initialize(this,0,0,0,&terrainTexture,&targetTexture))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the LMap object");
	if(testMap->characters[0]!=0)
	{
		testMap->characters[0]->currentWeapon = testGun;
		testMap->characters[0]->currentMag = testMag;
		testMap->mags[0] = testMag;
	}
	oldTargets = testMap->activeTargets;

//Crap for the starting stuff
	if (openTM.initialize(graphics, "pictures\\title.jpg") && 
		storyTM.initialize(graphics, "pictures\\story.png") && 
		controlTM.initialize(graphics, "pictures\\controls.png") && 
		endTM.initialize(graphics, "pictures\\endGame.png")) {
			//cool
	} else {
		throw GameError(gameErrorNS::FATAL_ERROR, "Can't find images");
	}

	open.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 0, &openTM);
	story.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 0, &storyTM);
	control.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 0, &controlTM);
	end.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 0, &endTM);
}

void TestStuff::update()
{
	/*if(input->isKeyDown(VK_SPACE))
	{
		audio->playCue(GUN_SHOT);
	}*/
	if (controlState < 4 && controlState!=-1) {
		if(input->wasKeyPressed(VK_SPACE))
			++controlState;

		return;
	}

	if(endGame)
	{
		controlState = -1;
	}
	if(!infiniteTime)
		gameTime -= frameTime;
	Character* player = testMap->characters[0];
	Camera* camera = testMap->camera;
	D3DXVECTOR2 mouseRealPos = testMap->camera->getRealPos(player->cursor->getCenterX(), player->cursor->getCenterY());
	player->aimAngle = atan2(mouseRealPos.y-player->getCenterY(), mouseRealPos.x-player->getCenterX());
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
	
	if(testMap->activeTargets == 0)
		testMap->levelDone = true;

	testMap->update(frameTime);

	if(gameTime<=0)
	{
		endGame = true;
		return;
	}

	if(testMap->levelDone)
	{
		currentLevel++;
		if(currentLevel > 4)
		{
			endGame = true;
			return;
		}
		delete testMap;
		
		
		testMap = new LMap(input,graphics);
		this->buildFromFile(fileNames[currentLevel]);
		Character* c = new Character(this,graphics);
		//c->initialize();
		testMap->addCharacter(c);

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

		if (!testMap->initialize(this,0,0,0,&terrainTexture,&targetTexture))
			throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the LMap object");
		
		if(testMap->characters[0]!=0)
		{
			testMap->characters[0]->currentWeapon = testGun;
			testMap->characters[0]->currentMag = testMag;
			testMap->mags[0] = testMag;
		}
	}
	if(oldTargets > testMap->activeTargets)
	{
		score += oldTargets-testMap->activeTargets;
		audio->playCue(TARGET_SHATTER);
	}
	oldTargets = testMap->activeTargets;
}

void TestStuff::ai()
{}

void TestStuff::collisions()
{
	//testMap->collision();
}

void TestStuff::render()
{
	graphics->spriteBegin();

	if (controlState == 1) {
		open.draw();
		graphics->spriteEnd();
		return;
	}

	if (controlState == 2) {
		story.draw();
		graphics->spriteEnd();
		return;
	}

	if (controlState == 3) {
		control.draw();
		graphics->spriteEnd();
		return;
	}

	if (controlState == -1) {
		end.draw();
		graphics->spriteEnd();
		return;
	}

	//FIX
	testMap->camera->centerPosition = testMap->characters[0]->getCenter();

	graphics->setBackColor(graphicsNS::GRAY);
	testMap->draw();
	std::stringstream tempWords;
	/*tempWords << "Ammo: " << static_cast<Gun*>(testMap->characters[0]->currentWeapon)->mag->ammoCount;
	hudFont.print(tempWords.str().c_str(), 300, 550);*/
	tempWords.str("");
	tempWords << "Time: " << gameTime;
	hudFont.print(tempWords.str().c_str(), 500, 550);
	tempWords.str("");
	tempWords << "Targets Remaining: " << testMap->activeTargets;
	hudFont.print(tempWords.str().c_str(), 700, 550);
	tempWords.str("");
	tempWords << "Score: " << score;
	hudFont.print(tempWords.str().c_str(), 100, 550);
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
	fstream fin;
	fin.open(fileName);
	string line = "";
	float zoom;
	getline(fin,line);
	zoom = atof(line.c_str());
	testMap->camera->zoom;
	getline(fin,line);
	int numTerrain = atoi(line.c_str());
	//this->terrainNumToPrint = numTerrain;
	getline(fin,line);
	int numSpawn = atoi(line.c_str());
	//this->spawnNumToPrint = numSpawn;
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

void TestStuff::consoleCommand()
{
	std::string command = console->getCommand();
	if(command == "")
		return;
	if(command == "skip_level")
	{
		testMap->levelDone = true;
		return;
	}
	if(command == "infinite_time")
	{
		infiniteTime=!infiniteTime;
		return;
	}
}