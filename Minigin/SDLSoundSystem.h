#pragma once
#include "ISoundSystem.h"
#include <iostream>

struct Mix_Chunk;
class SDLSoundSystem final : public ISoundSystem
{
public:
	SDLSoundSystem();
	~SDLSoundSystem() override;

	void Play(const Sound_Id soundId, const float volume) override;

	void RegisterSound(const Sound_Id soundId, const std::string& filepath) override;

private:
	std::map<Sound_Id, std::pair<std::string, Mix_Chunk*>> m_Sounds;
};