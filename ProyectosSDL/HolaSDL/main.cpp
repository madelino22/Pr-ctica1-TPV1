
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Game.h"
#include "Error.h"
using namespace std;

using uint = unsigned int;



int main2() {
	try {
		Game game = Game();
		game.run();
	}
	catch (string& e) {
		cout << e;
	}
	catch (Error e) {
		std::cout << e.getMensaje() << endl;
	}
	
	//para poder leer la consola al final
	system("pause");
	
	return 0;
}

int main(int argc, char* argv[]){
	main2();
	
	return 0;
}