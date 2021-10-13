#include "SFMLSoundProvider.h"

SFMLSoundProvider::SFMLSoundProvider() : _currentSongName("") {
	/*_sound.setVolume(100.0f);*/
	//std::for_each(_currentSounds.begin(), _currentSounds.end(), sf::Sound::setVolume(100.0f));
	for (int i = 0; i < 5; i++) {
		_currentSounds->setVolume(100.0f);
	}
}

void SFMLSoundProvider::PlaySound(std::string filename) {
	//Load sounds into channels
	int availChannel = -1;
	for (int i = 0; i < MAX_SOUND_CHANNELS; i++) {
		availChannel = i;
		break;
	}

	//If all sound channels are in use, do nothing for now
	if (availChannel != -1) {
		try {
			_currentSounds[availChannel] = _soundFileCache.GetSound(filename);
			_currentSounds[availChannel].play();
		}
		catch (SoundNotFoundException& snfe) {
			//ERROR, file was not found, should handle error here

			//Currently, this will simply mean nothing happens if an error occurs
		}
	}
}

void SFMLSoundProvider::PlaySong(std::string filename, bool looping) {
	sf::Music* currentSong;
	try {
		currentSong = _soundFileCache.GetSong(filename);
	}
	catch (SoundNotFoundException&) {
		//This one is dire, means we couldn't find or load the selected song
		//Exit function
		return;
	}

	//See if prior song is still playing, if so, stop it
	if (_currentSongName != "") {
		try {
			sf::Music* priorSong = _soundFileCache.GetSong(_currentSongName);
			if (priorSong->getStatus() != sf::Sound::Stopped) {
				priorSong->stop();
			}
		}
		catch (SoundNotFoundException&) {
			//Do nothing, this exception isn't dire. It simply means the previous sound we want to stop wasn't loaded
		}
	}

	_currentSongName = filename;
	currentSong->setLoop(looping);
	currentSong->play();
}

void SFMLSoundProvider::StopAllSounds() {
	for (int i = 0; i < MAX_SOUND_CHANNELS; i++) {
		_currentSounds[i].stop();
	}

	if (_currentSongName != "") {
		sf::Music* currentSong = _soundFileCache.GetSong(_currentSongName);
		if (currentSong->getStatus() == sf::Sound::Playing) {
			currentSong->stop();
		}
	}
}

bool SFMLSoundProvider::IsSoundPlaying() {
	for (int i = 0; i < MAX_SOUND_CHANNELS; i++) {
		if (_currentSounds[i].getStatus() == sf::Sound::Playing) {
			return true;
		}
	}

	return false;
}

bool SFMLSoundProvider::IsSongPlaying() {
	if (_currentSongName != "") {
		return _soundFileCache.GetSong(_currentSongName)->getStatus() == sf::Music::Playing;
	}

	return false;
}