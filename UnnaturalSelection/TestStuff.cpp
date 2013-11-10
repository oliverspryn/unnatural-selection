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
	testMap = new LMap(input);
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
	testMap->collision();
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