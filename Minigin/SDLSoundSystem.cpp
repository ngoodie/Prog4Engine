#include "SDL_mixer.h"
#include "SDLSoundSystem.h"

SDLSoundSystem::SDLSoundSystem()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }

    m_Thread = std::thread(&SDLSoundSystem::LoadingThread, this);
}

void SDLSoundSystem::LoadingThread()
{
    while (m_IsRunning)
    {
        std::unique_lock<std::mutex> lock(m_LoadQueueMutex);
        m_LoadConditionVariable.wait(lock, [this] { return !m_IsRunning || !m_LoadQueue.empty() || !m_BackupQueue.empty(); });

        // if the load queue is empty AND backup queue isn't
        if (m_LoadQueue.empty() && !m_BackupQueue.empty())
        {
            // move the sounds from the backup queue to the main queue
            while (!m_BackupQueue.empty())
            {
                m_LoadQueue.push(m_BackupQueue.front());
                m_BackupQueue.pop();
            }
        }

        // process queue, load & play sounds
        if (!m_LoadQueue.empty())
        {
            Load(m_Sounds[m_LoadQueue.front().first]);
            Play(m_LoadQueue.front().first, m_LoadQueue.front().second);

            m_LoadQueue.pop();
        }
    }
}

SDLSoundSystem::~SDLSoundSystem()
{
    m_IsRunning = false;
    m_Thread.join();

    for (auto& sound : m_Sounds)
    {
        Mix_FreeChunk(sound.second.second);
        sound.second.second = nullptr;
    }

    Mix_CloseAudio();
}

void SDLSoundSystem::Play(const Sound_Id soundId, const float volume)
{
    if (m_Sounds[soundId].second == nullptr) // Load sound
    {
        if (m_LoadQueueMutex.try_lock())
        {
            m_LoadQueue.emplace(soundId, volume);
            m_LoadQueueMutex.unlock();
            m_LoadConditionVariable.notify_one();

            //std::cout << soundId << " placed in queue\n";
        }
        else
        {
            m_BackupQueue.emplace(soundId, volume);
            m_LoadConditionVariable.notify_one();

            //std::cout << soundId << " placed in backup queue\n";
        }
    }
    else // Play sound
    {
        //std::cout << "play\n";
        Mix_VolumeChunk(m_Sounds[soundId].second, int(MIX_MAX_VOLUME * volume));
        if (Mix_PlayChannel(-1, m_Sounds[soundId].second, 0) == -1)
        {
            std::cerr << "Error playing sound: " << Mix_GetError() << std::endl;
            return;
        }
    }
}

void SDLSoundSystem::Load(std::pair<std::string, Mix_Chunk*>& sound)
{
    sound.second = Mix_LoadWAV(sound.first.c_str());
    //std::cout << sound.first << " loaded\n";
}

void SDLSoundSystem::RegisterSound(const Sound_Id soundId, const std::string& filepath)
{
    std::pair<std::string, Mix_Chunk*> soundData;
    soundData.first = filepath;
    soundData.second = nullptr;
    m_Sounds[soundId] = soundData;
}