#include <memory>
#include "SDL3/SDL_properties.h"
#include "SDL3_mixer/SDL_mixer.h"
#include "components/sdl3/audio.hpp"
#include "misc.hpp"
#include "proxy.hpp"

typedef Proxy<MIX_Mixer> Mixer_Proxy;
typedef Proxy<MIX_Audio> Audio_Proxy;
typedef Proxy<MIX_Track> Track_Proxy;

typedef std::shared_ptr<Mixer_Proxy> Mixer;
typedef std::shared_ptr<Audio_Proxy> Audio;
typedef std::shared_ptr<Track_Proxy> Track;

namespace Jila {

Sint64 toSeconds(Sint64 ms) {
    if (ms == -1) {
        SDL_ClearError();
        return 0.0;
    } else {
        return ms / 1000;
    }
}

struct AudioMeta {
    std::string_view name;
    std::string_view album;
    std::string_view artist;
    std::string_view copyright;
    Sint64 lenght; // seconds

    static void Bind(sol::state& state) {
        state.new_usertype<AudioMeta>("TrackMeta",
            "name", &AudioMeta::name,
            "album", &AudioMeta::album,
            "artist", &AudioMeta::artist,
            "copyright", &AudioMeta::copyright,
            "lenght", &AudioMeta::lenght
        );
    }

    static AudioMeta fromAudio(Audio audio) {
        SDL_PropertiesID propId = MIX_GetAudioProperties(audio->proxy);

        Sint64 ms = MIX_AudioFramesToMS(
            audio->proxy,
            MIX_GetAudioDuration(audio->proxy)
        );

        return AudioMeta {
            SDL_GetStringProperty(
                propId,
                MIX_PROP_METADATA_TITLE_STRING,
                ""
            ),
            SDL_GetStringProperty(
                propId,
                MIX_PROP_METADATA_ALBUM_STRING,
                ""
            ),
            SDL_GetStringProperty(
                propId,
                MIX_PROP_METADATA_ARTIST_STRING,
                ""
            ),
            SDL_GetStringProperty(
                propId,
                MIX_PROP_METADATA_COPYRIGHT_STRING,
                ""
            ),
            toSeconds(ms)
        };
    }
};

Mixer _SDL_InitMixer(Uint8 channels, Uint16 freq) {
    if (!MIX_Init()) {
        return 0;
    }

    SDL_AudioSpec spec {SDL_AUDIO_F32, 2, 48000};
    return MakeSafeMemory<Mixer_Proxy>(
        new Mixer_Proxy(MIX_CreateMixerDevice(
            SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
            &spec
        )),
        [](Mixer_Proxy* proxy) {
            MIX_DestroyMixer(proxy->proxy);
        }
    );
}

void _SDL_QuitMixer(Mixer mixer) {
    MIX_DestroyMixer(mixer->proxy);
    MIX_Quit();
}

Audio _SDL_CreateAudio(Mixer mixer, std::string_view path) {
    MIX_Audio* audio = MIX_LoadAudio(mixer->proxy, path.data(), false);

    if (!audio) return 0;

    return MakeSafeMemory<Audio_Proxy>(
        new Audio_Proxy {audio},
        [](Audio_Proxy* proxy) {
            MIX_DestroyAudio(proxy->proxy);
        }
    );
}

Track _SDL_CreateTrack(Mixer mixer) {
    MIX_Track* track = MIX_CreateTrack(mixer->proxy);

    if (!track) return 0;

    return MakeSafeMemory<Track_Proxy>(
        new Track_Proxy {track},
        [](Track_Proxy* proxy) {
            MIX_DestroyTrack(proxy->proxy);
        }
    );
}

bool _SDL_SetTrackAudio(Track track, Audio audio) {
    return MIX_SetTrackAudio(track->proxy, audio->proxy);
}

bool _SDL_PlayTrack(Track track) {
    return MIX_PlayTrack(track.get()->proxy, 0);
}

bool _SDL_StopTrack(Track track) {
    return MIX_StopTrack(track->proxy, 0);
}

bool _SDL_PauseTrack(Track track) {
    return MIX_PauseTrack(track->proxy);
}

bool _SDL_ResumeTrack(Track track) {
    return MIX_ResumeTrack(track->proxy);
}

bool _SDL_SetTrackPosition(Track track, Sint64 newPos) {
    return MIX_SetTrackPlaybackPosition(
        track->proxy,
        MIX_TrackMSToFrames(
            track->proxy,
            newPos * 1000
        )
    );
}

bool _SDL_SetMixerVolume(Mixer mixer, Uint8 volume) {
    return MIX_SetMasterGain(mixer->proxy, (float)volume / 100);
}

bool _SDL_TrackIsPlaying(Track track) {
    return MIX_TrackPlaying(track->proxy);
}

AudioMeta _SDL_GetAudioMeta(Audio audio) {
    return AudioMeta::fromAudio(audio);
}

Sint64 _SDL_GetTrackPosistion(Track track) {
    return toSeconds(MIX_GetTrackPlaybackPosition(track.get()->proxy));
}

void bindSdlAudio(sol::state* state) {
    state -> set_function(
        "SDL_InitMixer",
        &_SDL_InitMixer
    );

    state -> set_function(
        "SDL_QuitMixer",
        &_SDL_QuitMixer
    );

    AudioMeta::Bind(*state);

    state -> set_function(
        "SDL_CreateAudio",
        &_SDL_CreateAudio
    );

    state -> set_function(
        "SDL_CreateTrack",
        &_SDL_CreateTrack
    );

    state -> set_function(
        "SDL_SetTrackAudio",
        &_SDL_SetTrackAudio
    );

    state -> set_function(
        "SDL_TrackIsPlayed",
        &_SDL_TrackIsPlaying
    );

    state -> set_function(
        "SDL_PlayTrack",
        &_SDL_PlayTrack
    );

    state -> set_function(
        "SDL_StopTrack",
        &_SDL_StopTrack
    );

    state -> set_function(
        "SDL_PauseTrack",
        &_SDL_PauseTrack
    );

    state -> set_function(
        "SDL_ResumeTrack",
        &_SDL_ResumeTrack
    );

    // TODO: implement track/audio hooks

    state -> set_function(
        "SDL_SetTrackPosition",
        &_SDL_SetTrackPosition
    );

    state -> set_function(
        "SDL_SetMixerVolume",
        &_SDL_SetMixerVolume
    );

    state -> set_function(
        "SDL_GetAudioMeta",
        &_SDL_GetAudioMeta
    );

    state -> set_function(
        "SDL_GetTrackPosition",
        &_SDL_GetTrackPosistion
    );
}

}
