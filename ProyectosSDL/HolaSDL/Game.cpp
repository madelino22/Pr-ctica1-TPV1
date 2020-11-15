#include "Game.h"
#include <ctime>


struct Texturas {
	string file[4]{ "..\\Imagenes\\wall3.png", "..\\Imagenes\\characters1.png", "..\\Imagenes\\burguer1.png", "..\\Imagenes\\food2.png" };
	int fils[4]{1, 4, 1, 1};
	int cols[4]{1, 14, 1, 1};
};

Game::Game() {

	srand(time(nullptr));
	// We first initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Juego con clases", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw string("Error loading SDL window or renderer");
	// We now create the textures
	Texturas texturas;
	for (uint i = 0; i < NUM_TEXTURES; i++) {
		textures[i] = new Texture(renderer);
		textures[i]->load(texturas.file[i], texturas.fils[i], texturas.cols[i]);
	}

	ghosts = new Ghost*[4];
	//textures[0]->load("..\\images\\background1.png");
	//textures[1]->load("..\\images\\dog.png", 1, 6);
	// We finally create the game objects
	//dog = new Dog(WIN_WIDTH / 8, WIN_HEIGHT / 8, 200, 200, textures[1]);
	
	comida = 0;
	vidas = 3;

	LeeMapa();
}
Game::~Game() {

	delete pacman;
	delete mapa;//invoca al destructor de mapa y todo lo que lleva consigo
	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
}


void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();

	while (!exit) { // Falta el control de tiempo
		handleEvents();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE) {
			update();
			startTime = SDL_GetTicks();

		}
		
		render();

		//meter las vidas también
		if (comida <= 0) {
			exit = true;
			ganado = true;
		}
		else if (vidas <= 0) {
			exit = true;
		}
	}

	if (ganado)
		cout << "Has ganado!\n";
	else
		cout << "Has perdido :(\n";
}
void Game::update() {

	pacman->update();
	
	for (int x = 0; x < 4; x++) {
		ghosts[x]->update();
	}
}
void Game::render() const {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	mapa->render();
	pacman->render();
	for (int x = 0; x < 4; x++) {
		ghosts[x]->render();
	}
	
	SDL_RenderPresent(renderer);

}

//Este método checkea si se ha hecho quit y si es otro evento se le pasa al pacman invocando el handleevent
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;
		pacman->handleEvents(event);
		
	}
}



void Game::LeeMapa() {
#ifndef DOMJUDGE
	std::ifstream in("..\\Mapas\\level01.dat");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

	int fils, cols;

	cin >> fils >> cols;

	mapa = new GameMap(fils, cols,this, textures[0], textures[2], textures[3]);
	//para cada celda se lle su numero, se traduce a enum, y se añade al array de GameMap
	for (int x = 0; x < fils; x++) {
		for (int y = 0; y < cols; y++) {
			int nCelda;
			cin >> nCelda;
			mapa->SetCelda(x, y,(MapCell) nCelda);

			if ((MapCell)nCelda == Food)comida++;
			if (nCelda == 9) {
				//Creación del pacman
				pacman = new Pacman(Vector2D(y, x), this, textures[1]);
			}
			else if (nCelda >= 5 && nCelda<= 8) {
				ghosts[nCelda- 5] = new Ghost(Vector2D(y, x), this, textures[1], nCelda - 5);
				//Es la misma textura que el pacman ya que es una spritesheet
				//En el método render ya se seleccionara cual es
			}
			
		}
	}

	
	//estos x y van cambiados ya que en los bucles van del revés
	for (int x = 0; x < fils; x++) {
		for (int y = 0; y < cols; y++) {
			cout << mapa->GetCelda(x, y) << " ";
		}
		cout << "\n";
	}
	

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
#endif
}


int Game::GetNFils() const {

	return mapa->fils;
}

int Game::GetNCols() const {

	return mapa->cols;
}



bool Game::NextCell(const Vector2D& dir,const Vector2D& pos) const {
	bool celdaVacia = true;
	Vector2D  nextCell = pos;
	if (dir.GetY() == -1) {
		nextCell.SetY((pos.GetY() - 1 + mapa->fils) % mapa->fils);
		if (mapa->GetCelda(nextCell.GetY(), nextCell.GetX()) == Wall) celdaVacia = false;
	}
	else if (dir.GetY() == 1) {
		nextCell.SetY((pos.GetY() + 1 + mapa->fils) % mapa->fils);
		if (mapa->GetCelda(nextCell.GetY(), nextCell.GetX()) == Wall) celdaVacia = false;
	}
	else if (dir.GetX() == - 1) {
		nextCell.SetX((pos.GetX() - 1 + mapa->fils) % mapa->fils);
		if (mapa->GetCelda(nextCell.GetY(), nextCell.GetX()) == Wall) celdaVacia = false;
	}
	else if (dir.GetX() == + 1) {
		nextCell.SetX((pos.GetX() + 1 + mapa->fils) % mapa->fils);
		if (mapa->GetCelda(nextCell.GetY(), nextCell.GetX()) == Wall) celdaVacia = false;
	}


	return celdaVacia;
}

void Game::pacManRespawn() {
	pacman->posAct = pacman->posIni;
	vidas--;
}


