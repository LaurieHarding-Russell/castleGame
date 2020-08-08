#include <iostream>
#include <string>
#include "AL/al.h"
#include "AL/alc.h"
#include "OggVorbois/OggVorbois.h"

const char* MUSIC_FILE_NAME = "external/music/file/music.ogg";



class Audio { 
    private:
    ALuint alBackgroundMusicBuffer = 0;
    ALuint alBackgroundMusicSource = 0;
    ALCcontext* context;
    ALCdevice *device = NULL;

    void setupBackgroundMusic() {
        short *decoded;
        int channels;
        int sampleRate;

        int size;
        if((size = stb_vorbis_decode_filename(MUSIC_FILE_NAME, &channels, &sampleRate, &decoded)) == -1) {
            std::cerr << ":( \n";
        }

        alGenSources(1, &alBackgroundMusicSource);
        alGenBuffers(1, &alBackgroundMusicBuffer);

        ALuint format = 0; 
        if(channels == 1) {
            format = AL_FORMAT_MONO16;
        } else if(channels == 2) {
            format = AL_FORMAT_STEREO16;
        }

        alBufferData(alBackgroundMusicBuffer, format, decoded, size*sizeof(short int)*channels, 44100);

        alSourcei(alBackgroundMusicSource, AL_BUFFER, alBackgroundMusicBuffer);
        alSourcef(alBackgroundMusicSource, AL_GAIN, 0.25); // Keeping the background music in the background
        alSourcei(alBackgroundMusicSource, AL_LOOPING, AL_TRUE);
        alSourcePlay(alBackgroundMusicSource);
    }


    public:
    Audio() {
        device = alcOpenDevice(NULL);
        if (!device) {
            std::cout << "Sound device failed to load";
            exit(1);
        }
        
        ALuint error = alGetError();
        if (error != AL_NO_ERROR) {
            std::cerr << "Uhh oh... " + error << std::endl;
        }
        context = alcCreateContext(device, NULL);
        alcMakeContextCurrent(context);

        setupBackgroundMusic();
    }


    ~Audio() {
        alSourceStop(alBackgroundMusicSource);
        alDeleteSources(1, &alBackgroundMusicSource);
        alDeleteBuffers(1, &alBackgroundMusicBuffer);
        alcMakeContextCurrent(NULL);
        alcDestroyContext(context);
        alcCloseDevice(device);
    }
};