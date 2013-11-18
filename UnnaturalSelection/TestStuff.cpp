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

	//terrain generation
#pragma region
	TerrainElement* t = new TerrainElement(2000,50,VECTOR2(0, 0));
	//t->setDegrees(0.001);
	t->generateSideEquations();
	testMap->addTerrain(t);

	t = new TerrainElement(2000,50,VECTOR2(2950,0));
	////t->setDegrees(0.001);
	t->generateSideEquations();
	testMap->addTerrain(t);

	t = new TerrainElement(50,3000,VECTOR2(0, 2000));
	//t->setDegrees(0.001);
	t->generateSideEquations();
	testMap->addTerrain(t);

	t = new TerrainElement(50,400,VECTOR2(500,2000-150));
	//t->setDegrees(-30);
	t->generateSideEquations();
	testMap->addTerrain(t);

	t = new TerrainElement(50,400,VECTOR2(1000,2000-300));
	//t->setDegrees(-30);
	t->generateSideEquations();
	testMap->addTerrain(t);

	t = new TerrainElement(50,400,VECTOR2(1500,2000-450));
	//t->setDegrees(-30);
	t->generateSideEquations();
	testMap->addTerrain(t);

	t = new TerrainElement(50,400,VECTOR2(2000,2000-600));
	//t->setDegrees(-30);
	t->generateSideEquations();
	testMap->addTerrain(t);

	t = new TerrainElement(50,400,VECTOR2(2500,2000-750));
	//t->setDegrees(-30);
	t->generateSideEquations();
	testMap->addTerrain(t);

	t = new TerrainElement(50,400,VECTOR2(2000,2000-900));
	//t->setDegrees(-30);
	t->generateSideEquations();
	testMap->addTerrain(t);

	t = new TerrainElement(50,400,VECTOR2(1500,2000-1050));
	//t->setDegrees(-30);
	t->generateSideEquations();
	testMap->addTerrain(t);

	t = new TerrainElement(50,400,VECTOR2(1000,2000-1200));
	//t->setDegrees(-30);
	t->generateSideEquations();
	testMap->addTerrain(t);

	t = new TerrainElement(50,400,VECTOR2(500,2000-1350));
	//t->setDegrees(-30);
	t->generateSideEquations();
	testMap->addTerrain(t);

	t = new TerrainElement(50,400,VECTOR2(1000,2000-1500));
	//t->setDegrees(-30);
	t->generateSideEquations();
	testMap->addTerrain(t);

	t = new TerrainElement(50,400,VECTOR2(1500,2000-1650));
	//t->setDegrees(-30);
	t->generateSideEquations();
	testMap->addTerrain(t);

	t = new TerrainElement(50,400,VECTOR2(2000,2000-1800));
	//t->setDegrees(-30);
	t->generateSideEquations();
	testMap->addTerrain(t);

	t = new TerrainElement(50,400,VECTOR2(1500,2000-1950));
	//t->setDegrees(-30);
	t->generateSideEquations();
	testMap->addTerrain(t);
#pragma endregion

	for(int i = 0; i < 10; i++)
	{
		t = new TerrainElement(50,100,VECTOR2(2000-(50*i),2000-(bodyNS::HEIGHT/4)*i));
		//t->setDegrees(-30);
		t->generateSideEquations();
		testMap->addTerrain(t);
	}

	//testMap->buildFromFile("level.txt");
	Character* c = new Character(this,graphics);
	testMap->addCharacter(c);

	TerrainElement* sp = new TerrainElement(10,10,VECTOR2((testMap->maxX+testMap->minX)/2,testMap->maxY-200));
	sp->color = graphicsNS::RED;
	sp->setVisible(true);
	testMap->addSpawnPoint(sp);

	TerrainElement* target = new TerrainElement(50,50,VECTOR2((testMap->maxX+testMap->minX)/2,testMap->maxY-200));
	target->setHealth(10000);
	target->color = graphicsNS::BLUE;
	target->setVisible(true);
	testMap->addTarget(target);

	if (!testMap->initialize(this,0,0,0,&terrainTexture,&terrainTexture))
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
	


	testMap->update(frameTime);
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