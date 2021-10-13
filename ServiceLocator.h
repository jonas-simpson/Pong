#pragma once

#include "IAudioProvider.h"

class ServiceLocator {
public:
	static IAudioProvider* const GetAudio() { return _audioProvider; }

	static void RegisterServiceLocator(IAudioProvider* provider) { _audioProvider = provider; }

private:
	static IAudioProvider* _audioProvider;
};