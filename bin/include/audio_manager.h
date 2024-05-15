#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#pragma once

#include <map>
#include <raylib.h>
#include <string>

enum class AudioState {
    MENU_MUSIC,
    GAME_MUSIC,
    SOUND_EFFECTS
};

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    void PlayMusic(AudioState audioState);
    void StopMusic();
    void PlaySoundEffect(const std::string& soundId);

private:
    std::map<std::string, Music> musicAssets_;
    std::map<std::string, Sound> soundEffects_;
};

#endif //AUDIO_MANAGER_H
