#pragma once
#include <string>


#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Texture.h"
#include <iostream>




using uint = unsigned int;
using namespace std;


enum MapCell{Empty, Wall, Food, Vitamins};

class GameMap
{
private:
	int fils, cols;
	MapCell** celdasMapa;//Es un array din�mico de punteros a MapCell
	Texture* textureWall = nullptr;
	Texture* textureVit = nullptr;
	Texture* textureFood = nullptr;
public:
	GameMap(){};
	GameMap(int fils, int cols, Texture* textMap, Texture* textVit, Texture* textFood);
	~GameMap();

	MapCell GetCelda(int fil, int col) const { return celdasMapa[fil][col]; };

	void SetCelda(int fil, int col, MapCell cambio) { celdasMapa[fil][col] = cambio; };
	
	void render() const;

};
