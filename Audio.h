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

    public:
    void al_nssleep(unsigned long nsec) {
        struct timespec ts, rem;
        ts.tv_sec = (time_t)(nsec / 1000000000ul);
        ts.tv_nsec = (long)(nsec % 1000000000ul);
        while(nanosleep(&ts, &rem) == -1 && errno == EINTR)
            ts = rem;
    }

    Audio() {
        device = alcOpenDevice(NULL);
        if (!device) {
            std::cout << "Sound device failed to load";
            exit(1);
        }
        
        ALuint error = alGetError();
        if (error != AL_NO_ERROR) {
            std::cerr << "Uhh oh... " + error << std::endl;
            // exit(1);
        }
        context = alcCreateContext(device, NULL);
        alcMakeContextCurrent(context);

        short *decoded;
        int channels, len;
        int sampleRate;

        int size;
        if((size = stb_vorbis_decode_filename(MUSIC_FILE_NAME, &channels, &sampleRate, &decoded)) == -1) {
            std::cerr << ":( \n";
        }

        alGenSources(1, &alBackgroundMusicSource);
        alGenBuffers(1, &alBackgroundMusicBuffer);

        if(channels == 1) {
            alBufferData(alBackgroundMusicSource, AL_FORMAT_MONO16, decoded, size*sizeof(short int)*1, 44100);
        } else if(channels == 2) {
            alBufferData(alBackgroundMusicBuffer, AL_FORMAT_STEREO16, decoded, size*sizeof(short int)*channels, 44100);
        }

        alSourcei(alBackgroundMusicSource, AL_BUFFER, alBackgroundMusicBuffer);

        alSourcePlay(alBackgroundMusicSource);

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