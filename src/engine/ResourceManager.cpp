#include "ResourceManager.h"
#include "XCube2d.h"

std::map<std::string, SDL_Texture *> ResourceManager::textures;
std::map<std::string, TTF_Font *> ResourceManager::fonts;
std::map<std::string, MIX_Audio *> ResourceManager::sounds;
std::map<std::string, MIX_Audio *> ResourceManager::mp3files;

SDL_Texture * ResourceManager::loadTexture(std::string file, SDL_Color trans) {
	SDL_Texture * texture = nullptr;

	SDL_Surface * surf = IMG_Load(file.c_str());
	if (nullptr == surf)
		throw EngineException(SDL_GetError(), file);

	SDL_SetSurfaceColorKey(surf, 1, SDL_MapSurfaceRGB(surf, trans.r, trans.g, trans.b));
	
	texture = GFX::createTextureFromSurface(surf);
	if (nullptr == texture) {
		//throw EngineException(SDL_GetError(), file);

	//SDL_DestroySurface(surf);

		SDL_DestroySurface(surf);
		throw EngineException("GFX::createTextureFromSurface() failed", SDL_GetError());

	}
	textures[file] = texture;
	SDL_DestroySurface(surf);

	return texture;
}

TTF_Font * ResourceManager::loadFont(std::string file, const int & pt) {
	//TTF_Font * font = TTF_OpenFont(file.c_str(), (float)pt);
	TTF_Font* font = TTF_OpenFont(file.c_str(), static_cast<float>(pt));
	if (nullptr == font)
		//throw EngineException(SDL_GetError(), file);
		throw EngineException("TTF_OpenFont() failed", SDL_GetError());
	fonts[file] = font;
	return font;
}


MIX_Audio* ResourceManager::loadSound(std::string file) {
	auto existing = sounds.find(file);
	if (existing != sounds.end() && existing->second != nullptr) {
		return existing->second;
	}

	MIX_Audio* sound = MIX_LoadAudio(XEngine::getInstance()->getAudioEngine()->getMixer(), file.c_str(), false);
	if (nullptr == sound)
		throw EngineException(SDL_GetError(), file);

	sounds[file] = sound;
	return sound;
}


MIX_Audio * ResourceManager::loadMP3(std::string file) {
	//MIX_Audio * mp3 = MIX_LoadAudio(XEngine::getInstance()->getAudioEngine()->getMixer(), file.c_str(), false);
	MIX_Audio* mp3 = MIX_LoadAudio(XEngine::getInstance()->getAudioEngine()->getMixer(), file.c_str(), true);

	if (nullptr == mp3)
		throw EngineException(SDL_GetError(), file);
	mp3files[file] = mp3;
	return mp3;
}

void ResourceManager::freeResources() {
	for (auto pair : fonts) {
		if (pair.second) {
			TTF_CloseFont(pair.second);
#ifdef __DEBUG
			debug("Font freed:");
			debug(pair.first.c_str());
#endif
		}
	}

	fonts.clear(); // Clear the map after freeing resource

	for (auto pair : textures) {
		if (pair.second) {
			SDL_DestroyTexture(pair.second);
#ifdef __DEBUG
			debug("Texture destroyed:");
			debug(pair.first.c_str());
#endif
		}
	}

	textures.clear(); // Clear the map after freeing resources



	for (auto pair : sounds) {
		if (pair.second) MIX_DestroyAudio(pair.second);
	}
	sounds.clear();

	for (auto pair : mp3files) {
		if (pair.second) MIX_DestroyAudio(pair.second);
	}
	mp3files.clear();


#ifdef __DEBUG
	debug("ResourceManager::freeResources() finished");
#endif
}

SDL_Texture * ResourceManager::getTexture(std::string fileName) {
	auto it = textures.find(fileName);
	if (it != textures.end()) {
		return it->second;
	}

	//return textures[fileName];
	return nullptr;
}

TTF_Font * ResourceManager::getFont(std::string fileName) {
	auto it = fonts.find(fileName);
	if (it != fonts.end()) {
		return it->second;
	}
	
	return nullptr;
	//return fonts[fileName];
}

MIX_Audio * ResourceManager::getSound(std::string fileName) {
	auto it = sounds.find(fileName);
	if (it != sounds.end()) {
		return it->second;
	}
	return nullptr;
}


MIX_Audio * ResourceManager::getMP3(std::string fileName) {
	auto it = mp3files.find(fileName);
	if (it != mp3files.end()) {
		return it->second;
	}
	return nullptr;
}
