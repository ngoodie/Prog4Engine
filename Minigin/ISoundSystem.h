#pragma once
#include <map>
#include <string>

using Sound_Id = unsigned short;
class ISoundSystem
{
public:
	virtual ~ISoundSystem() = default;
	virtual void Play(const Sound_Id soundId, const float volume) = 0;
	virtual void RegisterSound(const Sound_Id soundId, const std::string& filepath) = 0;
};