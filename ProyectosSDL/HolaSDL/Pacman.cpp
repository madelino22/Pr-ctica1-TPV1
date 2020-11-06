#include "Pacman.h"

void Pacman::render() const {
	SDL_Rect destRect;

	destRect.x = x;
	destRect.y = y;
	destRect.h = h;
	destRect.w = w;


	//texture->render(destRect);
	texture->renderFrame(destRect, 0, 1);
}

void Pacman::update() {
	
	/*
	x = (x + dirX);
	y = (y + dirY);
	*/
}

void Pacman::handleEvents(SDL_Event& event) {

}