#include "Audio.h"
#include "OggVorbois/OggVorbois.h" // FIXME, why does this only like to be declared in the .cpp?

void Audio::setupBackgroundMusic() {
    short *decoded;
    int channels;
    int sampleRate;

    int size;
    if((size = stb_vorbis_decode_filename(MUSIC_FILE_NAME, &channels, &sampleRate, &decoded)) == -1) {
        std::cerr << ":( \n";
    }

    alGenSources(1, &alBackgroundMusicInfo.source);
    alGenBuffers(1, &alBackgroundMusicInfo.buffer);

    ALuint format = 0; 
    if(channels == 1) {
        format = AL_FORMAT_MONO16;
    } else if(channels == 2) {
        format = AL_FORMAT_STEREO16;
    }

    alBufferData(alBackgroundMusicInfo.buffer, format, decoded, size*sizeof(short int)*channels, 44100);

    alSourcei(alBackgroundMusicInfo.source, AL_BUFFER, alBackgroundMusicInfo.buffer);
    alSourcef(alBackgroundMusicInfo.source, AL_GAIN, backgroundGain);
    alSourcei(alBackgroundMusicInfo.source, AL_LOOPING, AL_TRUE);
    alSourcePlay(alBackgroundMusicInfo.source);
}

void Audio::buyFail() {
	alSourcei(alSoundFailInfo.source, AL_BUFFER, alSoundFailInfo.buffer);
    alSourcef(alBackgroundMusicInfo.source, AL_GAIN, soundEffects);
	alSourcePlay(alSoundFailInfo.source);
}

void Audio::loadAssets() {
    // Fail sound... this might be temporary. idk
    alGenSources(1, &alSoundFailInfo.source);
    alGenBuffers(1, &alSoundFailInfo.buffer);

	unsigned sampleRate = 10000;
	size_t bufSize = 0.5 * sampleRate;
	short* samples = new short[bufSize];
	for (unsigned i = 0; i < bufSize; i++) {
		samples[i] = MAX_16_BIT * sin(3.1 * i * 440 / sampleRate);
    }
	alBufferData(alSoundFailInfo.buffer, AL_FORMAT_MONO16, samples, bufSize, sampleRate);

	delete[] samples;

    // success sound... this might be temporary. idk
    alGenSources(1, &alSoundSuccessInfo.source);
    alGenBuffers(1, &alSoundSuccessInfo.buffer);

	sampleRate = 10000;
	bufSize = 0.5 * sampleRate;
	samples = new short[bufSize];
	for (unsigned i = 0; i < bufSize; i++) {
		samples[i] = MAX_16_BIT * sin(3.1 * i * (440 + i/6) / sampleRate);
    }
	alBufferData(alSoundSuccessInfo.buffer, AL_FORMAT_MONO16, samples, bufSize, sampleRate);

	delete[] samples;
}

Audio::Audio() {
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
    loadAssets();
}

Audio::~Audio() {
    alSourceStopv(1, &alSoundFailInfo.source);		// new line
	alDeleteSources(1, &alSoundFailInfo.source); // new line
	alDeleteBuffers(1, &alSoundFailInfo.buffer); // new line

    alSourceStop(alBackgroundMusicInfo.source);
    alDeleteSources(1, &alBackgroundMusicInfo.source);
    alDeleteBuffers(1, &alBackgroundMusicInfo.buffer);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}