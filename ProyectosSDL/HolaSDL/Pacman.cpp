#include "Pacman.h"
#include "Game.h"

void Pacman::render() const {
	
	int casillaH = WIN_HEIGHT / game->GetNFils();
	int casillaW = WIN_WIDTH / game->GetNCols();
	SDL_Rect destRect;

	destRect.x = posAct.GetX() * casillaW;
	destRect.y = posAct.GetY() * casillaH;
	destRect.h = casillaH;
	destRect.w = casillaW;

	
	texture->renderFrame(destRect, 0, 10);
}

void Pacman::update() {
	int nCols = game->GetNCols();
	int nFils = game->GetNFils();
	//el primer if checkea si se puede ir a la última posición indicada por la pulsacíon, si se puede se cambika la dirección, si no sigue yendo a la que estaba yendo

	
	if (game->NextCell(newDir, posAct))dir = newDir;
	if (game->NextCell(dir, posAct)) {
		//la suma de nCols y nFils dentro del parentesis es para que al ir en velocidad negativa y llegue al borde aparezca al otro lado tmb
		posAct.SetX((posAct.GetX() + dir.GetX() + nCols) % nCols);
		posAct.SetY((posAct.GetY() + dir.GetY() + nFils) % nFils);
	}
	
}

void Pacman::handleEvents(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_UP || key == SDLK_DOWN || key == SDLK_RIGHT || key == SDLK_LEFT ){
			if (key == SDLK_UP) {
				newDir.SetX(0);
				newDir.SetY(-1);
			}
			else if (key == SDLK_DOWN) {
				newDir.SetX(0);
				newDir.SetY(1);
			}
			else if (key == SDLK_RIGHT) {
				newDir.SetX(1);
				newDir.SetY(0);
			}
			else if (key == SDLK_LEFT) {
				newDir.SetX(-1);
				newDir.SetY(0);
			}
		}
	}
}