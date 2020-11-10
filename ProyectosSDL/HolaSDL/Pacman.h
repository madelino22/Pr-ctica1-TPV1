#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Texture.h"
#include "Vector2D.h"

using namespace std;

using uint = unsigned int;
class Game; // para que pueda guardar el juego y no haya inclusiones circulares


class Pacman
{
	friend class Game;

private:

	Point2D posAct, posIni;
	Vector2D dir, newDir;
	Game* game;

	
	
	
	Texture* texture = nullptr;
public:
	Pacman() {}
	Pacman(Point2D pIni,Game* g, Texture* t) :
		posIni(pIni), posAct(pIni), game(g), texture(t),  dir(Vector2D(1,0)) , newDir(Vector2D(1, 0)) {}
	~Pacman() {}
	void render() const;
	void update();
	void handleEvents(const SDL_Event& event);
};

