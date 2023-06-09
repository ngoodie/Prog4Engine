#pragma once
#include "ISoundSystem.h"

class NullSoundSystem : public ISoundSystem
{
public:
	void Play(const Sound_Id, const float) override {}
	void RegisterSound(const Sound_Id, const std::string&) override {}
};