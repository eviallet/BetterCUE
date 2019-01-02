#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <random>
#include <thread>
#include <atomic>
#include <iostream>
#include "lib/CUESDK/include/CUESDK.h"
#include "lib/CUESDK/include/CUESDKGlobal.h"
#include "lib/CUESDK/include/CorsairKeyIdEnum.h"
#include "lib/CUESDK/include/CorsairLedIdEnum.h"

class Keyboard {
public:
	Keyboard();
	std::string loadDeviceInfos();
	~Keyboard();
	void animateStaticKeys();
	void ledsRandom();
	void stop();
private:
	int ledPos(char a);
	int random(int min, int max);
	static const char* errorToString(CorsairError error);
private:
	std::default_random_engine *_engine;
	std::vector<CorsairLedColor> *_leds;
	std::thread *_thread;
	std::atomic_bool continueExecution = false;
};

#endif // KEYBOARD_H 