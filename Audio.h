#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <string>
#include "AL/al.h"
#include "AL/alc.h"

struct alSoundInfo {
    ALuint buffer;
    ALuint source;
};

const float MAX_16_BIT = 32760.0;

class Audio { 
    private:
    alSoundInfo alBackgroundMusicInfo;
    alSoundInfo alSoundFailInfo;
    alSoundInfo alSoundSuccessInfo;

    float backgroundGain = 0.25;
    float soundEffects = 0.75;

    ALCcontext* context;
    ALCdevice *device = NULL;
    const char* MUSIC_FILE_NAME = "external/music/file/music.ogg";

    void setupBackgroundMusic();
    void loadAssets();

    public:
    Audio();
    void buyFail();
    ~Audio();
};

#endif