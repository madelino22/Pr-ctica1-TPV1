#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Texture.h"
#include "Pacman.h"
#include "GameMap.h"
#include <fstream>
#include "Ghost.h"

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
	// uint winWidth, winHeight; // Tambi�n podr�an estar aqu�
	Pacman* pacman = nullptr;
	GameMap* mapa = nullptr;
	Ghost** ghosts = nullptr;
	bool exit = false;
	Texture* textures[NUM_TEXTURES];

	void LeeMapa();
	MapCell devuelveEnum(int x);
public:
	Game();
	~Game();

	int GetNFils() const;
	int GetNCols() const;
	bool NextCell(const Vector2D& dir,const Vector2D& pos) const;
	void run();
	void render() const;
	void handleEvents();
	void update();

};

