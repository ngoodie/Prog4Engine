#include "SDL_mixer.h"
#include "SDLSoundSystem.h"

SDLSoundSystem::SDLSoundSystem()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

SDLSoundSystem::~SDLSoundSystem()
{
    for (auto& sound : m_Sounds)
    {
        Mix_FreeChunk(sound.second.second);
        //delete sound.second.second;
        sound.second.second = nullptr;
    }
}

void SDLSoundSystem::Play(const Sound_Id soundId, const float volume)
{
    std::cout << "soundId = " << soundId << std::endl;
    volume;

    if (m_Sounds[soundId].second == nullptr)
    {
        // load via different thread
        m_Sounds[soundId].second = Mix_LoadWAV(m_Sounds[soundId].first.c_str());
    }

    if (m_Sounds[soundId].second == nullptr)
    {
        std::cerr << "Error loading sound: " << Mix_GetError() << std::endl;
        return;
    }

    if (Mix_PlayChannel(-1, m_Sounds[soundId].second, 0) == -1)
    {
        std::cerr << "Error playing sound: " << Mix_GetError() << std::endl;
        return;
    }
}

void SDLSoundSystem::RegisterSound(const Sound_Id soundId, const std::string& filepath)
{
    std::pair<std::string, Mix_Chunk*> soundData;
    soundData.first = filepath;
    soundData.second = nullptr;
    m_Sounds[soundId] = soundData;
}