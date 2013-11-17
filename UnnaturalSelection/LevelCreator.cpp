#include "LevelCreator.h"

LevelCreator::LevelCreator()
{
	getHeight = false;
	getWidth = false;
	boxHeight = 0;
	boxWidth = 0;
	totalTerrain = 0;
	selectedTerrain = 0;
	moveObject = false;
	clicked = false;
	prevClick = false;
}

LevelCreator::~LevelCreator()
{

}

void LevelCreator::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	if(!terrainTexture.initialize(graphics,NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing terrain texture"));

	testMap = new LMap(input,graphics,1000,1000,true);
	TerrainElement* t = new TerrainElement(50,3000,VECTOR2(0, 2000));
	//t->setDegrees(0.001);
	t->generateSideEquations();
	testMap->addTerrain(t);

	if (!testMap->initialize(this,0,0,0,&terrainTexture))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the LMap object");

}

void LevelCreator::update()
{
	if(moveObject)
	{
		int x,y;
		x = testMap->camera->getRealPos(input->getMouseX(),0).x;
		y = testMap->camera->getRealPos(0,input->getMouseY()).y;
		movingObject->setX(x);
		movingObject->setY(y);
	}
	testMap->update(frameTime);
	if(input->getMouseLButton())
		prevClick = true;
	if(!input->getMouseLButton() && prevClick)
	{
		clicked = true;
		prevClick = false;
	}
	if(!moveObject && clicked)
	{
		int x,y;
		x = testMap->camera->getRealPos(input->getMouseX(),0).x;
		y = testMap->camera->getRealPos(0,input->getMouseY()).y;
		if(findEntityByClick(x,y,movingObject))
		{
			moveObject = true;
		}
		clicked = false;
	}
	if(moveObject && clicked)
	{
		moveObject = false;
		clicked = false;
		movingObject->generateSideEquations();
	}
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

	if(command == "play")
		testMap->editor = false;

	if(command == "stopPlay")
		testMap->editor = true;

	if(getHeight)
	{
		console->print(command);
		boxHeight = atoi(command.c_str());
		console->print("width");
		getHeight = false;
		getWidth = true;
		moveObject = true;
		return;
	}

	if(getWidth)
	{
		boxWidth = atoi(command.c_str());
		TerrainElement* t = new TerrainElement(boxHeight,boxWidth,VECTOR2(100,100));
		
		t->initialize(this,&terrainTexture,0);
		t->generateSideEquations();
		if(testMap->addTerrain(t))
		{
			console->print("adding block...");
			selectedTerrain = totalTerrain;
			totalTerrain++;
			moveObject = true;
			movingObject = t;
		}
		else
			console->print("block failed");
		getWidth = false;
	}

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
		getHeight = true;
		console->print("height:");
		return;
	}
}

bool LevelCreator::findEntityByClick(int x, int y, TerrainElement* selectedEnt)
{
	TerrainElement* ent;
	int entityX,entityY;
	for(int i = 0; i < testMap->addedElements; i++)
	{
		if(testMap->terrain[i]->getActive())
		{
			entityX = ent->getX();
			entityY = ent->getY();
			int temp = ent->getX();
			if(x >= entityX && x <=entityX+ent->getWidth()/2 && y >= entityY && y <= entityY + ent->getHeight()/2)
			{
				selectedEnt = ent;
				return true;
			}
		}
	}

	return false;
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