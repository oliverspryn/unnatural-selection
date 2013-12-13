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
	addSpawn = false;
	spawnChosen = false;
	targetSelected = false;
	chooseHealth = false;
	oldColor = graphicsNS::BLACK;
	terrainNumToPrint = 0;
	spawnNumToPrint = 0;
	totalTarget = 0;
	targetToPrint = 0;
}

LevelCreator::~LevelCreator()
{

}

void LevelCreator::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	this->mousePoint = new TextDX();

	if(this->mousePoint->initialize(graphics, 15, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	if(!terrainTexture.initialize(graphics,NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing terrain texture"));

	if(!targetTexture.initialize(graphics,TARGET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing target texture"));

	testMap = new LMap(input,graphics,10000,1000,10,50,100,true);

	if (!testMap->initialize(this,0,0,0,&terrainTexture,&targetTexture))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the LMap object");

	if(testMap->totalCharacters == 0)
	{
		Character* c = new Character(this,graphics);
		c->initialize();
		testMap->addCharacter(c);
	}
}

void LevelCreator::update()
{
	if(moveObject)
	{
		int x,y;
		x = testMap->camera->getRealPos(input->getMouseX(),0).x - this->blockMoveX;
		y = testMap->camera->getRealPos(0,input->getMouseY()).y - this->blockMoveY;
		movingObject->setX(x);
		movingObject->setY(y);
	}

	//camera functions
	//zoom
	if(input->isKeyDown('1'))
	{
		testMap->camera->zoom = max(0.1, testMap->camera->zoom - frameTime*.5);
	}
	if(input->isKeyDown('2'))
	{
		testMap->camera->zoom = min(10, testMap->camera->zoom + frameTime*.5);
	}

	if(input->isKeyDown(VK_LEFT) && testMap->editor)
	{
		testMap->camera->centerPosition = VECTOR2(testMap->camera->centerPosition.x-50,testMap->camera->centerPosition.y);
	}

	if(input->isKeyDown(VK_RIGHT) && testMap->editor)
	{
		testMap->camera->centerPosition = VECTOR2(testMap->camera->centerPosition.x+50,testMap->camera->centerPosition.y);
	}

	if(input->isKeyDown(VK_UP) && testMap->editor)
	{
		testMap->camera->centerPosition = VECTOR2(testMap->camera->centerPosition.x,testMap->camera->centerPosition.y-50);
	}

	if(input->isKeyDown(VK_DOWN) && testMap->editor)
	{
		testMap->camera->centerPosition = VECTOR2(testMap->camera->centerPosition.x,testMap->camera->centerPosition.y+50);
	}

	if(multipleBlocks && input->isKeyDown(VK_SPACE))
	{
		multipleBlocks = false;
		firstBlock = false;
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
			blockMoveX = x-movingObject->getX();
			blockMoveY = y-movingObject->getY();
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
				terrainNumToPrint++;
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
		if(spawnChosen)
		{
			spawnNumToPrint--;
		}
		else if(targetSelected)
		{
			this->targetToPrint--;
		}
		else
		{
			terrainNumToPrint--;
		}
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
	this->mousePoint->setFontColor(graphicsNS::WHITE);
	std::stringstream point;
	point << "X: " << testMap->camera->getRealPos(input->getMouseX(),input->getMouseY()).x << " Y: " << testMap->camera->getRealPos(input->getMouseX(),input->getMouseY()).y;
    this->mousePoint->print(point.str(),20,20);
	testMap->draw();

	graphics->spriteEnd();
}

void LevelCreator::consoleCommand()
{
	command = console->getCommand();    // get command from console
    if(command == "")                   // if no command
        return;

	if(command == "ai")
	{
		console->print("adding ai character");
		AI* a = new AI(this,graphics);
		a->initialize();
		testMap->addCharacter(reinterpret_cast<Character*>(a));
		return;
	}

	if(command == "info")
	{
		std::stringstream temp;
		if(objectChosen)
		{
			temp << "width: " << movingObject->getWidth() << " ";
			temp << "Height: " << movingObject->getHeight() << " ";
			temp << "x: " << movingObject->getX() << " ";
			temp << "y: " << movingObject->getY() << " ";
			console->print(temp.str());
		}
		return;
	}

	if(command == "play")
	{
		if(this->spawnNumToPrint>0)
		{
			testMap->editor = false;
			for(int i = 0; i < testMap->totalCharacters; i++)
			{
				testMap->chooseSpawnPoint(testMap->characters[i]);
			}
		}
		return;
	}

	if(command == "stopPlay")
	{
		testMap->editor = true;
		return;
	}

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
		double tempHeight = atof(command.c_str());
		boxHeight = tempHeight * testMap->characters[0]->getHeight();
		console->print("width");
		getHeight = false;
		getWidth = true;
		moveObject = true;
		return;
	}

	if(getWidth)
	{
		double tempWidth = atof(command.c_str());
		boxWidth = tempWidth*testMap->characters[0]->getHeight();
		TerrainElement* t = new TerrainElement(boxHeight,boxWidth,VECTOR2(100,100));
		
		t->initialize(this,&terrainTexture,0);
		t->generateSideEquations();
		if(testMap->addTerrain(t))
		{
			this->blockMoveX =boxWidth/2;
			this->blockMoveY = boxHeight/2;
			t->setX(input->getMouseX()-blockMoveX);
			t->setY(input->getMouseY()-blockMoveY);
			console->print("adding block...");
			selectedTerrain = totalTerrain;
			totalTerrain++;
			moveObject = true;
			oldColor = t->color;
			movingObject = t;
			terrainNumToPrint++;
		}
		else
			console->print("block failed");
		getWidth = false;
		return;
	}

	
	if(command == "spawn")
	{
		TerrainElement* t = new TerrainElement(50,50,VECTOR2(100,100));
		t->color = graphicsNS::RED;
		oldColor = t->color;
		t->initialize(this,&terrainTexture,0);
		t->generateSideEquations();
		if(testMap->addSpawnPoint(t))
		{
			this->blockMoveX =boxWidth/2;
			this->blockMoveY = boxHeight/2;
			t->setX(input->getMouseX()-blockMoveX);
			t->setY(input->getMouseY()-blockMoveY);
			console->print("adding spawn...");
			selectedTerrain = totalTerrain;
			moveObject = true;
			addSpawn = true;
			movingObject = t;
			spawnNumToPrint++;
		}
		else
			console->print("spawn failed");
		return;
	}

	if(command == "target")//here
	{
		TerrainElement* t = new TerrainElement(64,64,VECTOR2(100,100));
		t->color = graphicsNS::CYAN;
		oldColor = t->color;
		t->initialize(this,&targetTexture,0);//put in new texture manager here
		t->generateSideEquations();
		if(testMap->addTarget(t))
		{
			this->blockMoveX =boxWidth/2;
			this->blockMoveY = boxHeight/2;
			t->setX(input->getMouseX()-blockMoveX);
			t->setY(input->getMouseY()-blockMoveY);
			console->print("adding target...");
			console->print("select health:");
			selectedTerrain = totalTerrain;
			targetToPrint++;
			moveObject = true;
			movingObject = t;
			chooseHealth = true;
		}
		else
			console->print("target failed");
		return;
	}

	if(chooseHealth)
	{
		movingObject->setHealth(atoi(command.c_str()));
		chooseHealth = false;
		return;
	}

    if (command == "help")              // if "help" command
    {
        console->print("Console Commands:");
        console->print("fps - toggle display of frames per second");
		console->print("The unit for building items is based on the character height");
		console->print("block- build a new terrainElement of your desired size");
		console->print("blockM- build multiple blocks of the desired size");
		console->print("color- change the color of your selected block");
		console->print("save- save your level to a specific file");
		console->print("load- load a premade level into the world");
		console->print("when selecting a block hit space to move it");
		console->print("when selecting a block hit delete to remove it");
        return;
    }

    if (command == "fps")
    {
        fpsOn = !fpsOn;                 // toggle display of fps
        if(fpsOn)
            console->print("fps On");
        else
            console->print("fps Off");
		return;
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
		return;
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
		testMap->createFileFromLevel(terrainNumToPrint,spawnNumToPrint,testMap->camera->zoom);
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
		return;
	}
}

void LevelCreator::buildFromFile(std::string fileName)
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
				spawnChosen = false;
				targetSelected=false;
				return ent;
			}
		}
	}
	for(int i = 0; i < testMap->totalSpawns; i++)
	{
		if(testMap->spawnPoints[i]->getActive())
		{
			ent = testMap->spawnPoints[i];
			entityX = ent->getX();
			entityY = ent->getY();
			int temp = ent->getX();
			if(x >= entityX && x <=entityX+ent->getWidth() && y >= entityY && y <= entityY + ent->getHeight())
			{
				found = true;
				targetSelected = false;
				spawnChosen = true;
				return ent;
			}
		}
	}
	for(int i = 0; i < testMap->totalTargets; i++)
	{
		if(testMap->targets[i]->getActive())
		{
			ent = testMap->targets[i];
			entityX = ent->getX();
			entityY = ent->getY();
			int temp = ent->getX();
			if(x >= entityX && x <=entityX+ent->getWidth() && y >= entityY && y <= entityY + ent->getHeight())
			{
				found = true;
				spawnChosen = false;
				targetSelected = true;
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
	this->mousePoint->onLostDevice();
	Game::releaseAll();
}

void LevelCreator::resetAll()
{
	terrainTexture.onResetDevice();
	this->mousePoint->onResetDevice();
	Game::resetAll();
}