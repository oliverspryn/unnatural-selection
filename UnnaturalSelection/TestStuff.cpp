#include "TestStuff.h"

TestStuff::TestStuff()
{
	
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
	testGun = new Gun(10, 20*60*60, 100, 2000, 1000, 100, 30, 2.0, 0, ONE);
	testGun->loadNewMag(testMag);
	testGun->initialize(this, 128, 32, entityNS::NONE, &gunTM);
	//testGun->setX(100);
	//testGun->setY(100);

	/*testTerrain = new StraightPath(5,1000,VECTOR2(100,100));
	if (!testTerrain->initialize(this, &terrainTexture,1))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the terrain object");*/
	testMap = new LMap(input,graphics);

	this->buildFromFile("testLevel.txt");

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
}

void TestStuff::update()
{
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
	if(testMap->levelDone)
	{
		delete testMap;
		testMap = new LMap(input,graphics);
		this->buildFromFile("testLevel.txt");
		Character* c = new Character(this,graphics);
		//c->initialize();
		testMap->addCharacter(c);

		//WeaponStuff
		testMag = new Magazine(30000, 40000, 40000, 1, 100, 103, ONE, testProjectile); 
		testGun = new Gun(10, 20*60*60, 100, 2000, 1000, 100, 30, 2.0, 0, ONE);
		testGun->loadNewMag(testMag);
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

	graphics->setBackColor(graphicsNS::GRAY);
	testMap->draw();

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