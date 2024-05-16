#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#pragma once

#include <map>
#include <raylib.h>

enum class MusicId {
    MENU_MUSIC,
    GAME_MUSIC,

};

enum class SoundId {
    ROTATE,
    CLEAR_ROW
};

enum class AudioState {
    MENU_MUSIC,
    GAME_MUSIC,
    SOUND_EFFECTS
};

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    void PlayMusic();
    void StopMusic();
    void PauseMusic();
    void ResumeMusic();
    void PlaySoundEffect(SoundId soundId);
    void SetAudioState(AudioState actualState);
    [[nodiscard]] AudioState GetAudioState() const;

private:
    std::map<MusicId, Music> musicAssets_;
    std::map<SoundId, Sound> soundEffects_;
    AudioState currentAudioState;
};

#endif //AUDIO_MANAGER_H