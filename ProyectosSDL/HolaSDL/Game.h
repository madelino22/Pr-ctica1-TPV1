#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Texture.h"
#include "Pacman.h"
#include "GameMap.h"
#include <fstream>

using namespace std;

using uint = unsigned int;




const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 4;
class Game
{
	
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	// uint winWidth, winHeight; // También podrían estar aquí
	Pacman* pacman = nullptr;
	GameMap* mapa = nullptr;
	bool exit = false;
	Texture* textures[NUM_TEXTURES];

	void LeeMapa();
	MapCell devuelveEnum(int x);
public:
	Game();
	~Game();
	void run();
	void render() const;
	void handleEvents();
	void update();

};

