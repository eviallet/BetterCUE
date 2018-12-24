#include "Keyboard.h"

Keyboard::Keyboard(QObject *parent)
	: QObject(parent) {
	srand(time(0));
	_engine = new std::default_random_engine(rand());
	
	CorsairPerformProtocolHandshake();
	if (const auto error = CorsairGetLastError()) {
		qCritical() << "Handshake failed: " << errorToString(error);
		return;
	}
}

QString Keyboard::loadDeviceInfos() {
	if (CorsairGetDeviceCount() >= 1) {
		CorsairDeviceInfo* deviceInfo = CorsairGetDeviceInfo(0);
		auto ledPositions = CorsairGetLedPositions();
		if (ledPositions) {
			_leds = new std::vector<CorsairLedColor>(ledPositions->numberOfLed);
			for (auto i = 0; i < ledPositions->numberOfLed; i++) {
				auto ledId = ledPositions->pLedPosition[i].ledId;
				CorsairLedColor led = { ledId, 0, 0, 0 };
				CorsairGetLedsColors(1, &led);
				_leds->push_back(led);
			}
		}
		return deviceInfo->model;
	}
	return "None";
}

void Keyboard::ledsRandom() {
	continueExecution = !continueExecution;
	if (continueExecution) {
		_thread = new std::thread([this] {
			std::vector<CorsairLedColor> _ledsAlphabetic;
			for (char c = 'a'; c <= 'z'; c++)
				_ledsAlphabetic.push_back(_leds->at(this->ledPos(c)));
			while (continueExecution) {
				for (int i = 0; i < _ledsAlphabetic.size(); i++) {
					_ledsAlphabetic.at(i).r = this->random(0, 255);
					_ledsAlphabetic.at(i).g = this->random(0, 255);
					_ledsAlphabetic.at(i).b = this->random(0, 255);
				}
				CorsairSetLedsColorsAsync(static_cast<int>(_ledsAlphabetic.size()), _ledsAlphabetic.data(), nullptr, nullptr);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
		});
	}
}


int Keyboard::ledPos(char c) {
	CorsairLedId id = CorsairGetLedIdForKeyName(c);
	for (int i = 0; i < _leds->size(); i++)
		if (_leds->at(i).ledId == id)
			return i;
	return -1;
}

int Keyboard::random(int min, int max) {
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(*_engine);
}

Keyboard::~Keyboard() {
}

const char* Keyboard::errorToString(CorsairError error) {
	switch (error) {
	case CE_Success:
		return "CE_Success";
	case CE_ServerNotFound:
		return "CE_ServerNotFound";
	case CE_NoControl:
		return "CE_NoControl";
	case CE_ProtocolHandshakeMissing:
		return "CE_ProtocolHandshakeMissing";
	case CE_IncompatibleProtocol:
		return "CE_IncompatibleProtocol";
	case CE_InvalidArguments:
		return "CE_InvalidArguments";
	default:
		return "unknown error";
	}
}
