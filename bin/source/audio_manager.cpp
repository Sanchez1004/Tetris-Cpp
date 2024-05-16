#include "../include/audio_manager.h"

AudioManager::AudioManager() {
    // Here new music can be added to musicAssets_ map
    musicAssets_["menu_music"] = LoadMusicStream("assets/sounds/MenuMusic.mp3");
    musicAssets_["game_music"] = LoadMusicStream("assets/sounds/GameMusic.mp3");

    // Here new sounds can be added to soundEffects_ map
    soundEffects_["rotate"] = LoadSound("assets/sounds/rotate.mp3");
    soundEffects_["clear_row"] = LoadSound("assets/sounds/clear_row.mp3");
}

AudioManager::~AudioManager() {
    for(auto&[first, second] : musicAssets_) {
        UnloadMusicStream(second);
    }
    for(auto&[first, second] : soundEffects_) {
        UnloadSound(second);
    }
}

void AudioManager::PlayMusic(const AudioState audioState) {
    switch (audioState) {
        case AudioState::MENU_MUSIC:
            PlayMusicStream(musicAssets_["menu_music"]);
            break;
        case AudioState::GAME_MUSIC:
            PlayMusicStream(musicAssets_["game_music"]);
            break;
        default: break;
    }
}

void AudioManager::StopMusic() {
    StopMusicStream(musicAssets_["menu_music"]);
    StopMusicStream(musicAssets_["game_music"]);
}

void AudioManager::PlaySoundEffect(const std::string &soundId) {
    PlaySound(soundEffects_[soundId]);
}