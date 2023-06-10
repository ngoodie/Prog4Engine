#pragma once
#include <map>
#include <string>

using Sound_Id = unsigned short;
class ISoundSystem
{
public:
	virtual ~ISoundSystem() = default;
	virtual void Play(const Sound_Id soundId, const float volume) = 0;
	virtual void PlayMusic(const Sound_Id musicId, const float volume, const int loops = -1) = 0;
	virtual void RegisterSound(const Sound_Id soundId, const std::string& filepath) = 0;
	virtual void RegisterMusic(const Sound_Id musicId, const std::string& filepath) = 0;
};