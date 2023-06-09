#pragma once
#include "ISoundSystem.h"
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>

struct Mix_Chunk;
class SDLSoundSystem final : public ISoundSystem
{
public:
	SDLSoundSystem();
	~SDLSoundSystem() override;

	void Play(const Sound_Id soundId, const float volume) override;
	void Load(std::pair<std::string, Mix_Chunk*>& sound);

	void LoadingThread();

	void RegisterSound(const Sound_Id soundId, const std::string& filepath) override;

private:
	std::map<Sound_Id, std::pair<std::string, Mix_Chunk*>> m_Sounds;
	std::thread m_Thread;
	bool m_IsRunning{ true };

	std::mutex m_LoadQueueMutex;
	std::condition_variable m_LoadConditionVariable;

	std::queue<std::pair<Sound_Id, float>> m_LoadQueue{};
	std::queue<std::pair<Sound_Id, float>> m_BackupQueue{};
};