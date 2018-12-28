#include <iostream>
#include <string>
#include "Keyboard.h"

using namespace std;

int main(int argc, char *argv[]) {
	Keyboard *keyboard = new Keyboard();

	string kb;
	
	while ((kb = keyboard->loadDeviceInfos()) == "None") {
		cout << "Veuillez connecter le clavier et appuyer sur entrée.";
		getchar();
	}

	cout << kb << " est en ligne." << endl << "\'q\' pour quitter.";

	keyboard->ledsRandom();
	
	while (kb != "q") getline(cin, kb);

	keyboard->stop();

	
	return 0;
}
