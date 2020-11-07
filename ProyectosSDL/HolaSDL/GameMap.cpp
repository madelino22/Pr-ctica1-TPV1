#include "GameMap.h"
#include "Game.h"

GameMap::GameMap(int nFils, int nCols, Game* g, Texture* textWall, Texture* textVit, Texture* textFood) {
	fils = nFils;
	cols = nCols;
	celdasMapa = new MapCell * [fils];
	for (int x = 0; x < fils; x++) {
		celdasMapa[x] = new MapCell[cols];
	}
	game = g;
	textureWall = textWall;
	textureVit = textVit;
	textureFood = textFood;

	//Al construir creear el mapa vac�o
	for (int x = 0; x < fils; x++) {
		for (int y = 0; y < cols; y++) {
			celdasMapa[x][y] = Empty;
		}
	}

	casillaH = WIN_HEIGHT / fils;
	casillaW = WIN_WIDTH / cols;

}


void GameMap::render() const {

	
	for (int x = 0; x < fils; x++) {
		for (int y = 0; y < cols; y++) {
			MapCell tipo = celdasMapa[x][y];

			SDL_Rect destRect;
			destRect.x = y * casillaW;
			destRect.y = x * casillaH;
			destRect.h = casillaH;
			destRect.w = casillaW;

			if (tipo == Wall) {
				textureWall->renderFrame(destRect, 0, 0);
			}
			else if (tipo == Food) {
				textureFood->renderFrame(destRect, 0, 0);
			}
			else if (tipo == Vitamins) {
				textureVit->renderFrame(destRect, 0, 0);
			}
		}
	}
}
