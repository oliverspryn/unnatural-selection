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

	testProjectile = new Projectile(&projectileTM, this, 8, 8, entityNS::CIRCLE, 1);

	testMag = new Magazine(30, 4000, 4000, 1, 100, 100, ONE, testProjectile); 
	testGun = new Gun(10, 2*60*60, 100, 2000, 1000, 100, 30, 2.0, 0, ONE);
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

	TerrainElement* sp = new TerrainElement(10,10,VECTOR2(0,0));
	sp->color = graphicsNS::RED;
	sp->setVisible(true);
	testMap->addSpawnPoint(sp);

	if (!testMap->initialize(this,0,0,0,&terrainTexture))
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

	//The camera boxing
	if(camera->centerPosition.y + 3*(camera->height/2)/4 < player->corners[1].y)
	{
		camera->centerPosition.y = player->corners[1].y - 3*(camera->height/2)/4;
	}
	else if(camera->centerPosition.y - 3*(camera->height/2)/4 > player->corners[1].y)
	{
		camera->centerPosition.y = player->corners[1].y + 3*(camera->height/2)/4;
	}
	if(camera->centerPosition.x + 3*(camera->width/2)/4 < player->corners[1].x)
	{
		camera->centerPosition.x = player->corners[1].x - 3*(camera->width/2)/4;
	}
	else if(camera->centerPosition.x - 3*(camera->width/2)/4 > player->corners[1].x)
	{
		camera->centerPosition.x = player->corners[1].x + 3*(camera->width/2)/4;
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