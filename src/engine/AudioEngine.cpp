#include "AudioEngine.h"

AudioEngine::AudioEngine() : soundOn(true), volume(128) {
	if (!MIX_Init()) {
		throw EngineException("Failed to init SDL_mixer library: ", SDL_GetError());
	}

	mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
	if (!mixer)
		throw EngineException("Failed to init SDL_mixer:", SDL_GetError());
}

AudioEngine::~AudioEngine() {
#ifdef __DEBUG
	debug("AudioEngine::~AudioEngine() started");
#endif
	if (mixer) {
		MIX_DestroyMixer(mixer); // This destroys all associated MIX_Audio objects and tracks.
		mixer = nullptr;
	}
	
MIX_Quit();

#ifdef __DEBUG
	debug("AudioEngine::~AudioEngine() finished");
#endif

}

void AudioEngine::toggleSound() {
	soundOn = !soundOn;
}

void AudioEngine::setSoundVolume(const int & _volume) {
	volume = _volume;
	MIX_SetMixerGain(mixer, volume / 128.0f);
}

int AudioEngine::getSoundVolume() {
	return volume;
}

void AudioEngine::playSound(MIX_Audio * sound) {
	playSound(sound, volume);
}

void AudioEngine::playSound(MIX_Audio * sound, const int & _volume) {
	if (soundOn) {
		MIX_Track *track = MIX_CreateTrack(mixer);

		if (track) {
			//MIX_SetTrackAudio(track, sound);
			if (!MIX_SetTrackAudio(track, sound) || !MIX_PlayTrack(track, 0)) {
				// Track never actually started, so the stopped-callback below
				// would never fire to clean it up - destroy it here instead.
				std::cout << "Failed to play sound: " << SDL_GetError() << std::endl;
				MIX_DestroyTrack(track);
				return;
			}
			MIX_SetTrackGain(track, _volume / 128.0f);
			//MIX_PlayTrack(track, 0); // times=0 plays once? wait no MIX_PlayTrack has no loops param, there's MIX_SetTrackLoops
			MIX_SetTrackStoppedCallback(track, [](void* userdata, MIX_Track* t) {
				MIX_DestroyTrack(t);
				}, nullptr);
		}
		
	}
}

void AudioEngine::playMP3(MIX_Audio * mp3, const int & times) {
	if (soundOn) {
		MIX_Track* track = MIX_CreateTrack(mixer);
		if (!track) {
			std::cout << "Failed to create track for MP3" << std::endl;
			return;
		}

		if (!MIX_SetTrackAudio(track, mp3)) {
			std::cout << "Failed to play MP3: " << SDL_GetError() << std::endl;
			MIX_DestroyTrack(track);
			return;
		}
		MIX_SetTrackLoops(track, times);
		if (!MIX_PlayTrack(track, 0)) {
			std::cout << "Failed to play MP3: " << SDL_GetError() << std::endl;
			MIX_DestroyTrack(track);
			return;
		}
		MIX_SetTrackStoppedCallback(track, [](void* userdata, MIX_Track* t) {
			MIX_DestroyTrack(t);
			}, nullptr);
	}
}
	
	
	

		