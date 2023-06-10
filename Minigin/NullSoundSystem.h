#pragma once
#include "ISoundSystem.h"

class NullSoundSystem : public ISoundSystem
{
public:
	~NullSoundSystem() = default;
	void Play(const Sound_Id, const float) override {}
	void PlayMusic(const Sound_Id , const float , const int) override {}
	void RegisterSound(const Sound_Id, const std::string&) override {}
	void RegisterMusic(const Sound_Id, const std::string&) override {}
};