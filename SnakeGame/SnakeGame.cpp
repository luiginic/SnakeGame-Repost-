#include "snake.h"
int main()
{
	cout << endl << endl << endl << "       Press any key to exit or SPACEBAR to start the game.";
	cout << endl << "For difficulty selection press 'e' or 'h' while playing.";
	cout << endl << endl << "   To change direction use keys W, A, S, D.";
	//_getch();
	switch (_getch()) {
	case ' ':
		play();
	}
	//play();
}