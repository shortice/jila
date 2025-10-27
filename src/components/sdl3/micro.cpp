// Experiemental.
#include "SDL3/SDL_audio.h"
#include "components/sdl3/micro.hpp"
#include "SDL3/SDL_audio.h"
#include "misc.hpp"
#include "cstdint"
#include <fstream>

namespace Jila {

// TODO: in functional style
// This class stolen from the whisper.cpp project (MIT License).
// Source: https://github.com/ggml-org/whisper.cpp/blob/f16c12f3f55f5bd3d6ac8cf2f31ab90a42c884d5/examples/common.h#L138
class wav_writer {
    private:
        std::ofstream file;
        uint32_t dataSize = 0;
        std::string wav_filename;

        bool write_header(
            const uint32_t sample_rate,
            const uint16_t bits_per_sample,
            const uint16_t channels
        ) {

            file.write("RIFF", 4);
            file.write("\0\0\0\0", 4);    // Placeholder for file size
            file.write("WAVE", 4);
            file.write("fmt ", 4);

            const uint32_t sub_chunk_size = 16;
            const uint16_t audio_format = 1;      // PCM format
            const uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
            const uint16_t block_align = channels * bits_per_sample / 8;

            file.write(reinterpret_cast<const char *>(&sub_chunk_size), 4);
            file.write(reinterpret_cast<const char *>(&audio_format), 2);
            file.write(reinterpret_cast<const char *>(&channels), 2);
            file.write(reinterpret_cast<const char *>(&sample_rate), 4);
            file.write(reinterpret_cast<const char *>(&byte_rate), 4);
            file.write(reinterpret_cast<const char *>(&block_align), 2);
            file.write(reinterpret_cast<const char *>(&bits_per_sample), 2);
            file.write("data", 4);
            file.write("\0\0\0\0", 4);    // Placeholder for data size

            return true;
        }

        // It is assumed that PCM data is normalized to a range from -1 to 1
        bool write_audio(const float * data, size_t length) {
            for (size_t i = 0; i < length; ++i) {
                const int16_t intSample = int16_t(data[i] * 32767);
                file.write(reinterpret_cast<const char *>(&intSample), sizeof(int16_t));
                dataSize += sizeof(int16_t);
            }
            if (file.is_open()) {
                file.seekp(4, std::ios::beg);
                uint32_t fileSize = 36 + dataSize;
                file.write(reinterpret_cast<char *>(&fileSize), 4);
                file.seekp(40, std::ios::beg);
                file.write(reinterpret_cast<char *>(&dataSize), 4);
                file.seekp(0, std::ios::end);
            }
            return true;
        }

        bool open_wav(const std::string & filename) {
            if (filename != wav_filename) {
                if (file.is_open()) {
                    file.close();
                }
            }
            if (!file.is_open()) {
                file.open(filename, std::ios::binary);
                wav_filename = filename;
                dataSize = 0;
            }
            return file.is_open();
        }

    public:
        bool open(
            const std::string & filename,
            const    uint32_t   sample_rate,
            const    uint16_t   bits_per_sample,
            const    uint16_t   channels
        ) {
        if (open_wav(filename)) {
            write_header(sample_rate, bits_per_sample, channels);
        } else {
            return false;
        }

        return true;
    }

    bool close() {
        file.close();
        return true;
    }

    bool write(const float * data, size_t length) {
        return write_audio(data, length);
    }

    ~wav_writer() {
        if (file.is_open()) {
            file.close();
        }
    }
};


struct _Microphone {
    SDL_AudioStream* stream;
};

typedef std::shared_ptr<_Microphone> Micro;

// 0 - failed
Micro _SDL_CreateMicro() {
    SDL_AudioSpec capture_spec_requested {
        SDL_AUDIO_F32,
        1,
        44100
    };

    SDL_AudioStream* stream = SDL_OpenAudioDeviceStream(
        SDL_AUDIO_DEVICE_DEFAULT_RECORDING,
        &capture_spec_requested,
        NULL,
        NULL
    );

    if (stream) {
        return MakeSafeMemory<_Microphone>(
            new _Microphone {stream},
            [](_Microphone* micro) {
                SDL_DestroyAudioStream(micro -> stream);
            }
        );
    }

    return 0;
}

bool _SDL_MicroPause(Micro micro) {
    return SDL_PauseAudioStreamDevice(micro -> stream);
}

bool _SDL_MicroResume(Micro micro) {
    return SDL_ResumeAudioStreamDevice(micro -> stream);
}

bool _SDL_MicroPaused(Micro micro) {
    return SDL_AudioStreamDevicePaused(micro->stream);
}

bool _SDL_MicroSaveWAV(Micro micro, std::string fileName) {
    wav_writer writer;
    std::vector<float> audioRaw;

    while (true) {
        float* buf = (float*)malloc(4096);

        int data = SDL_GetAudioStreamData(
            micro -> stream,
            buf,
            4096
        );

        if (data == -1) {
            free(buf);
            return false;
        } else {
            for (int pos = 1; pos <= (data / sizeof(float)); pos++) {
                audioRaw.push_back(
                    *(buf+pos-1)
                );
            }

            free(buf);
        }

        if (data == 0) {
            break;
        }
    }

    writer.open(
        fileName,
        44100,
        16,
        1
    );

    writer.write(audioRaw.data(), audioRaw.size());

    return true;
}

void bindSdlMicro(sol::state* state) {
    state->set_function(
        "SDL_CreateMicro",
        &_SDL_CreateMicro
    );

    state->set_function(
        "SDL_MicroPause",
        &_SDL_MicroPause
    );

    state->set_function(
        "SDL_MicroResume",
        &_SDL_MicroResume
    );

    state->set_function(
        "SDL_MicroPaused",
        &_SDL_MicroPaused
    );

    state->set_function(
        "SDL_MicroSaveWAV",
        &_SDL_MicroSaveWAV
    );
}

}
