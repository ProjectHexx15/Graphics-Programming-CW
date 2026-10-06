#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems(); 
	gameLoop();
}

void MainGame::linkADS()
{
	// Define the light position
	glm::vec3 lightPos(20.0f, 20.0f, 20.0f);

	// Define the light color (white light)
	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

	// Define the object color (red object in this case)
	glm::vec3 objectColor(1.0f, 0.0f, 0.0f);

	glm::mat4 modelMatrix = transform.GetModel();

}


void MainGame::initSystems()
{
	_gameDisplay.initDisplay(); 
	mesh2.loadModel("..\\res\\monkey3.obj");
	skybox.init(faces);
	texture.init("..\\res\\bricks.jpg");

	//shader.init("..\\res\\shader.vert", "..\\res\\shader.frag"); //new shader
	geoShader.initGeo();
	eMappingShader.init("..\\res\\eMapping.frag", "..\\res\\eMapping.vert");
	//ADS.init("..\\res\\ADS.vert", "..\\res\\ADS.frag"); //new shader

	myCamera.initCamera(glm::vec3(0, 0, -30), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);
	counter = 0.0f;
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
	
}


void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	transform.SetPos(glm::vec3(0.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 2, 0.0));
	transform.SetScale(glm::vec3(5.0, 5.0, 5.0));

	geoShader.Bind();
	linkGeo();
	geoShader.Update(transform, myCamera);
	mesh2.draw();

	eMappingShader.Bind();
	eMappingShader.Update(transform, myCamera);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.textureID);

	counter = counter + 0.02f;

	skybox.draw(&myCamera);

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 

void MainGame::linkGeo()
{
	float randX = ((float)rand() / (RAND_MAX));
	float randY = ((float)rand() / (RAND_MAX));
	float randZ = ((float)rand() / (RAND_MAX));
	// Frag: uniform float randColourX; uniform float randColourY; uniform float randColourZ;
	geoShader.setFloat("randColourX", randX);
	geoShader.setFloat("randColourY", randY);
	geoShader.setFloat("randColourZ", randZ);
	// Geom: uniform float time;
	geoShader.setFloat("time", counter);
}

void MainGame::linkEmapping()
{
	eMappingShader.setMat4("projection", myCamera.getProjection());
	eMappingShader.setMat4("view", myCamera.getView());
	eMappingShader.setMat4("model", transform.GetModel());
	eMappingShader.setVec3("cameraPos", myCamera.getPos());
}