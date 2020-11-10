#include "Ghost.h"
#include "Game.h"

void Ghost::render() const {

	int casillaH = WIN_HEIGHT / game->GetNFils();
	int casillaW = WIN_WIDTH / game->GetNCols();
	SDL_Rect destRect;

	destRect.x = posAct.GetX() * casillaW;
	destRect.y = posAct.GetY() * casillaH;
	destRect.h = casillaH;
	destRect.w = casillaW;

	switch (color){
	case 0:
		texture->renderFrame(destRect, 0, 0);
		break;
	case 1:
		texture->renderFrame(destRect, 0, 2);
		break;
	case 2:
		texture->renderFrame(destRect, 0, 6);
		break;
	case 3:
		texture->renderFrame(destRect, 0, 8);
		break;
	default:
		throw "El color del fantasma est� mal";
		break;
	}
	
}

//Aqui hay que hacer que decida de manera aleatoria donde ir
void Ghost::update() {
	int nCols = game->GetNCols();
	int nFils = game->GetNFils();
	
	Vector2D posibles[3];
	Vector2D dirPos = dir;
	int tam = 0;
	for (int x = 0; x < 3; x++) {
		if (game->NextCell(dirPos, posAct)) {
			posibles[tam] = dirPos;
			tam++;
		}
		//primero checkeo si en la direcion que est� yendo se puede,
		//luego una de las de al lado(perpendicular) y al final la inversa a la �ltima
		if (x == 0) dirPos.Perpendicular();
		else if (x == 1) dirPos.Invierte();
	}

	if (tam == 0) {
	    dir.Invierte();
	}
	
	else {
		int nuevaDir = rand() % tam;
		dir = posibles[nuevaDir];
	}
	
	//la suma de nCols y nFils dentro del parentesis es para que al ir en velocidad negativa y llegue al borde aparezca al otro lado tmb
	posAct.SetX((posAct.GetX() + dir.GetX() + nCols) % nCols);
	posAct.SetY((posAct.GetY() + dir.GetY() + nFils) % nFils);
	

}