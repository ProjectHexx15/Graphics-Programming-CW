#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <vector>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Skybox.h"


enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();
	void linkADS();

	void run();

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	void linkGeo();
	void linkEmapping();

	Display _gameDisplay;
	GameState _gameState;
	Mesh mesh1;
	Mesh mesh2;
	Camera myCamera;
	Texture texture; 
	Shader shader;
	Shader geoShader;
	Shader eMappingShader;
	Skybox skybox;
	Shader ADS;
	Transform transform;

	vector<std::string> faces = 
	{
		"..\\res\\right.jpg",
		"..\\res\\left.jpg",
		"..\\res\\top.jpg",
		"..\\res\\bottom.jpg",
		"..\\res\\front.jpg",
		"..\\res\\back.jpg"

	};


	float counter;


};

