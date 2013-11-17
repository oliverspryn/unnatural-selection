#include "LevelCreator.h"

LevelCreator::LevelCreator()
{
	getHeight = false;
	getWidth = false;
	saveFile = false;
	boxHeight = 0;
	boxWidth = 0;
	totalTerrain = 0;
	selectedTerrain = 0;
	moveObject = false;
	clicked = false;
	objectChosen = false;
	prevClick = false;
	chooseA = false;
	chooseR = false;
	chooseG = false;
	chooseB = false;
	multipleBlocks = false;
	firstBlock = false;
	loadFile = false;
	oldColor = graphicsNS::BLACK;
}

LevelCreator::~LevelCreator()
{

}

void LevelCreator::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	if(!terrainTexture.initialize(graphics,NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing terrain texture"));

	testMap = new LMap(input,graphics,10000,1000,true);

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
	//selecting an object
	if(!moveObject && clicked)
	{
		int x,y;
		x = testMap->camera->getRealPos(input->getMouseX(),0).x;
		y = testMap->camera->getRealPos(0,input->getMouseY()).y;
		//if they click off object to deselect
		if(objectChosen)
		{
			objectChosen = false;
			movingObject->color = oldColor;
		}
		bool found = false;
		movingObject = findEntityByClick(x,y,found);
		if(found)
		{
			oldColor = movingObject->color;
			objectChosen = true;
			movingObject->color = graphicsNS::BLUE;
		}
		clicked = false;
	}
	//placing an object
	if(moveObject && clicked)
	{
		moveObject = false;
		clicked = false;
		//if they want a bunch of blocks make them
		if(firstBlock && multipleBlocks)
		{
			//redo color and sides of old one
			movingObject->color = oldColor;
			movingObject->generateSideEquations();
			//make new one
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
		}
		else
		{
			objectChosen = false;
			movingObject->color = oldColor;
			movingObject->generateSideEquations();
		}

	}
	if(objectChosen && input->isKeyDown(VK_SPACE))
	{
		moveObject = true;
	}
	if(objectChosen && input->isKeyDown(VK_DELETE) && !moveObject)
	{
		movingObject->setActive(false);
		movingObject->setVisible(false);

		objectChosen = false;
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

	if(command == "color" && objectChosen)
	{
		console->print("Alpha: ");
		chooseA = true;
		return;
	}

	if(chooseA)
	{
		console->print("Red: ");
		a = atoi(command.c_str());
		chooseA = false;
		chooseR = true;
		return;
	}

	if(chooseR)
	{
		console->print("Green: ");
		r = atoi(command.c_str());
		chooseR = false;
		chooseG = true;
		return;
	}

	if(chooseG)
	{
		console->print("Blue: ");
		g = atoi(command.c_str());
		chooseG = false;
		chooseB = true;
		return;
	}

	if(chooseB)
	{
		console->print("Recoloring and unselecting");
		b = atoi(command.c_str());
		chooseB = false;
		movingObject->color = SETCOLOR_ARGB(a,r,g,b);
		//unselects object
		objectChosen = false;
		return;
	}

	if(getHeight)
	{
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
	
	if(command == "blockM")
	{
		getHeight = true;
		console->print("height:");
		multipleBlocks = true;
		firstBlock = true;
		return;
	}

	if(command == "stop" && multipleBlocks)
	{
		multipleBlocks = false;
		firstBlock = false;
	}

	if(command == "save")
	{
		saveFile = true;
		console->print("FileName:");
		return;
	}
	if(saveFile)
	{
		saveFile = false;
		testMap->levelFileName = command;
		testMap->createFileFromLevel();
		return;
	}
	if(testMap->addedElements == 0 && command == "load")
	{
		loadFile = true;
		console->print("file name: ");
		return;
	}
	if(loadFile)
	{
		buildFromFile(command);
		console->print("stuff");
	}
}

void LevelCreator::buildFromFile(std::string fileName)
{
	fstream fin;
	fin.open(fileName);
	string line = "";
	getline(fin,line);
	int numTerrain = atoi(line.c_str());
	getline(fin,line);
	int height = 0, width = 0, x = 0, y = 0;
	double degree = 0;
	while(!fin.fail() && line != "--")
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
		TerrainElement* t = new TerrainElement(height,width,VECTOR2(x,y));
		t->setDegrees(degree);
		t->initialize(this,&terrainTexture,0);
		t->generateSideEquations();
		testMap->addTerrain(t);
		getline(fin,line);
	}
}

TerrainElement* LevelCreator::findEntityByClick(int x, int y, bool& found)
{
	TerrainElement* ent;
	int entityX,entityY;
	for(int i = 0; i < testMap->addedElements; i++)
	{
		if(testMap->terrain[i]->getActive())
		{
			ent = testMap->terrain[i];
			entityX = ent->getX();
			entityY = ent->getY();
			int temp = ent->getX();
			if(x >= entityX && x <=entityX+ent->getWidth() && y >= entityY && y <= entityY + ent->getHeight())
			{
				found = true;
				return ent;
			}
		}
	}
	found = false;
	return 0;
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