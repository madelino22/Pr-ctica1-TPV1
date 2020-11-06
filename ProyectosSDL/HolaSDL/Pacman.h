#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Texture.h"

using namespace std;

using uint = unsigned int;
class Pacman
{
private:
	uint w = 0; // width
	uint h = 0; // height
	uint x = 0; uint y = 0; // Posición de esquina superior izqda
	int dirX = 10; int dirY = 0; // Dirección de movimiento
	Texture* texture = nullptr;
public:
	Pacman() {}
	Pacman(uint w, uint h, uint x, uint y, Texture* t) :
		w(w), h(h), x(x), y(y), texture(t) {}
	~Pacman() {}
	void render() const;
	void update();
	void handleEvents(SDL_Event& event);
};

