#include "TestStuff.h"

TestStuff::TestStuff()
{
	
}

TestStuff::~TestStuff()
{
	delete testMap;
}

void TestStuff::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	if(!terrainTexture.initialize(graphics,NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing terrain texture"));
	/*testTerrain = new StraightPath(5,1000,VECTOR2(100,100));
	if (!testTerrain->initialize(this, &terrainTexture,1))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the terrain object");*/
	testMap = new LMap(input,graphics);
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

	//t = new StraightPath(20,100,VECTOR2(100,400));
	////t->setDegrees(0.001);
	//t->generateSideEquations();
	//testMap->addTerrain(t);

	/*t = new StraightPath(5,300,VECTOR2(500,450));
	t->setRadians(PI/8);
	t->generateSideEquations();
	testMap->addTerrain(t);*/

	//testMap->buildFromFile("level.txt");

	if (!testMap->initialize(this,0,0,0,&terrainTexture))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the LMap object");
}

void TestStuff::update()
{
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