#include "Keyboard.h"

Keyboard::Keyboard() {
	srand(time(0));
	_engine = new std::default_random_engine(rand());
	
	CorsairPerformProtocolHandshake();
	if (const auto error = CorsairGetLastError()) {
		std::cout << "Handshake failed: " << errorToString(error);
		return;
	}
}

std::string Keyboard::loadDeviceInfos() {
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

void Keyboard::animateStaticKeys() {
	//continueExecution = true;
	//_thread = new std::thread([this] {
		CorsairLedColor winLock; winLock.ledId = CLK_WinLock;
		CorsairLedColor followLockScroll; followLockScroll.ledId = CLK_ScrollLock;
		CorsairLedColor lum; lum.ledId = CLK_Brightness;
		CorsairLedColor followPrntScrn; followPrntScrn.ledId = CLK_PrintScreen;
		while (true) {
			CorsairGetLedsColors(1, &followPrntScrn);
			CorsairGetLedsColors(1, &followLockScroll);
			winLock.r = followLockScroll.r;
			winLock.g = followLockScroll.g;
			winLock.b = followLockScroll.b;
			lum.r = followPrntScrn.r;
			lum.g = followPrntScrn.g;
			lum.b = followPrntScrn.b;
			CorsairSetLedsColorsAsync(1, &winLock, nullptr, nullptr);
			CorsairSetLedsColorsAsync(1, &lum, nullptr, nullptr);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	//});
}

void Keyboard::ledsRandom() {
	continueExecution = true;
	_thread = new std::thread([this] {
		std::vector<CorsairLedColor> ledsAlphabetic;
		for (char c = 'a'; c <= 'z'; c++)
			ledsAlphabetic.push_back(_leds->at(this->ledPos(c)));
		while (continueExecution) {
			for (int i = 0; i < ledsAlphabetic.size(); i++) {
				// make at least one color at max luminosity for a better effet
				int max = this->random(0, 2);
				ledsAlphabetic.at(i).r = this->random(0, 255);
				ledsAlphabetic.at(i).g = this->random(0, 255);
				ledsAlphabetic.at(i).b = this->random(0, 255);
				switch (max) {
				case 0:
					ledsAlphabetic.at(i).r = 255;
					break;
				case 1:
					ledsAlphabetic.at(i).g = 255;
					break;
				case 2:
					ledsAlphabetic.at(i).b = 255;
					break;
				}
			}
			CorsairSetLedsColorsAsync(static_cast<int>(ledsAlphabetic.size()), ledsAlphabetic.data(), nullptr, nullptr);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	});
}

void Keyboard::stop() {
	continueExecution = false;
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
