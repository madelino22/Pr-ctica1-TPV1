#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Texture.h"
#include "Vector2D.h"
#include <cstdlib>

using namespace std;

using uint = unsigned int;
class Game; // para que pueda guardar el juego y no haya inclusiones circulares



class Ghost
{
	friend class Game;

private:

	Vector2D posAct, posIni;
	Vector2D dir, newDir;
	Game* game;
	int color;




	Texture* texture = nullptr;
public:
	Ghost() {}
	Ghost(Vector2D pIni, Game* g, Texture* t, int c) :
		posIni(pIni), posAct(pIni), game(g), texture(t), dir(Vector2D(-1, 0)), newDir(Vector2D(-1, 0)), color(c) {}
	~Ghost() {}
	void render() const;
	void update();
	void handleEvents(const SDL_Event& event);
};

