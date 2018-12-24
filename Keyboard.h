#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QObject>
#include <qdebug.h>
#include <random>
#include <thread>
#include "lib/CUESDK/include/CUESDK.h"
#include "lib/CUESDK/include/CUESDKGlobal.h"
#include "lib/CUESDK/include/CorsairKeyIdEnum.h"
#include "lib/CUESDK/include/CorsairLedIdEnum.h"

class Keyboard : public QObject {
	Q_OBJECT
public:
	Keyboard(QObject *parent);
	QString loadDeviceInfos();
	~Keyboard();
public slots:
	void ledsRandom();
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