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
const uint32_t FRAME_RATE = 200;
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

	int vidas;
	int comida;
	bool ganado;

	void LeeMapa();
public:
	Game();
	~Game();

	int GetNFils() const;
	int GetNCols() const;
	bool NextCell(const Vector2D& dir,const Vector2D& pos) const;

	MapCell contenidoCelda(int y, int x) const{
		return mapa->celdasMapa[y][x];;
	}

	//Para que los fantasmas sepan donde est� el pacman para saber si hay que comerselo o no
	Point2D getPacManPosAct() const { return pacman->posAct; }
    
	//Este m�todo es para indicar a los fantasmas si el pacman est� comiendo, para que sepan si tienen que comerselo o ser comidos
	bool pacmanEating() const { return pacman->eating; };

	//lleva al pacman a la posici�n inicial y resta una vida, si no le quedan vidas se encarga de finalizar la partida
	void pacManRespawn();
	
	void Comida() {
		comida--;
	};

	void EmptyCell(int y, int x) {
		mapa->celdasMapa[y][x] = Empty;
	};

	void run();
	void render() const;
	void handleEvents();
	void update();

};

