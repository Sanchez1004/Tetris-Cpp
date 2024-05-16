#include "../include/audio_manager.h"

AudioManager::AudioManager(): currentAudioState(AudioState::MENU_MUSIC) {
    // Here new music can be added to musicAssets_ map
    musicAssets_[MusicId::MENU_MUSIC] = LoadMusicStream("assets/sounds/MenuMusic.mp3");
    musicAssets_[MusicId::GAME_MUSIC] = LoadMusicStream("assets/sounds/GameMusic.mp3");

    // Here new sounds can be added to soundEffects_ map
    soundEffects_[SoundId::ROTATE] = LoadSound("assets/sounds/rotate.mp3");
    soundEffects_[SoundId::CLEAR_ROW] = LoadSound("assets/sounds/clear_row.mp3");
}

AudioManager::~AudioManager() {
    for(auto&[first, second] : musicAssets_) {
        UnloadMusicStream(second);
    }
    for(auto&[first, second] : soundEffects_) {
        UnloadSound(second);
    }
}

void AudioManager::PlayMusic() {
    switch (currentAudioState) {
        case AudioState::MENU_MUSIC:
            PlayMusicStream(musicAssets_[MusicId::MENU_MUSIC]);
            break;
        case AudioState::GAME_MUSIC:
            PlayMusicStream(musicAssets_[MusicId::GAME_MUSIC]);
            break;
        default: break;
    }
}

void AudioManager::StopMusic() {
    StopMusicStream(musicAssets_[MusicId::GAME_MUSIC]);
    StopMusicStream(musicAssets_[MusicId::GAME_MUSIC]);
}

void AudioManager::PauseMusic() {
    switch (currentAudioState) {
        case AudioState::MENU_MUSIC:
            PauseMusicStream(musicAssets_[MusicId::MENU_MUSIC]);
            break;
        case AudioState::GAME_MUSIC:
            PauseMusicStream(musicAssets_[MusicId::GAME_MUSIC]);
            break;
        default: break;
    }
}

void AudioManager::ResumeMusic() {
    switch (currentAudioState) {
        case AudioState::MENU_MUSIC:
            ResumeMusicStream(musicAssets_[MusicId::MENU_MUSIC]);
        break;
        case AudioState::GAME_MUSIC:
            PauseMusicStream(musicAssets_[MusicId::GAME_MUSIC]);
        break;
        default: break;
    }
}

void AudioManager::PlaySoundEffect(const SoundId soundId) {
    PlaySound(soundEffects_[soundId]);
}

void AudioManager::SetAudioState(const AudioState actualState) {
    currentAudioState = actualState;
}

AudioState AudioManager::GetAudioState() const {
    return currentAudioState;
}
