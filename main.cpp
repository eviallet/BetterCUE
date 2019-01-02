#include <iostream>
#include <string>
#include "Keyboard.h"

using namespace std;

int main() {

	Keyboard keyboard;

	string kb;
	
	if ((kb = keyboard.loadDeviceInfos()) != "None") {
		keyboard.animateStaticKeys();
	}
	
	return 0;
}
