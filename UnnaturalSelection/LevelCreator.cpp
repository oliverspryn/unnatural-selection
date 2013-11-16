#include "LevelCreator.h"

LevelCreator::LevelCreator()
{

}

LevelCreator::~LevelCreator()
{

}

void LevelCreator::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	if(!terrainTexture.initialize(graphics,NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing terrain texture"));

	testMap = new LMap(input,graphics,true);
	if (!testMap->initialize(this,0,0,0,&terrainTexture))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the LMap object");
}

void LevelCreator::update()
{
	testMap->update(frameTime);
}

void LevelCreator::ai()
{

}

void LevelCreator::collisions()
{

}

void LevelCreator::render()
{
	graphics->spriteBegin();

	graphics->setBackColor(graphicsNS::TEAL);
	testMap->draw();

	graphics->spriteEnd();
}

void LevelCreator::consoleCommand()
{
	command = console->getCommand();    // get command from console
    if(command == "")                   // if no command
        return;

    if (command == "help")              // if "help" command
    {
        console->print("Console Commands:");
        console->print("fps - toggle display of frames per second");
        return;
    }

    if (command == "fps")
    {
        fpsOn = !fpsOn;                 // toggle display of fps
        if(fpsOn)
            console->print("fps On");
        else
            console->print("fps Off");
    }
	if(command == "block")
	{
		TerrainElement* t = new TerrainElement(10000,10000,VECTOR2(100,100));
		t->initialize(this,&terrainTexture,0);
		testMap->addTerrain(t);
		console->print("adding block...");
	}
}

void LevelCreator::releaseAll()
{
	terrainTexture.onLostDevice();
	Game::releaseAll();
}

void LevelCreator::resetAll()
{
	terrainTexture.onResetDevice();
	Game::resetAll();
}