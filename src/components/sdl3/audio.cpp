#ifdef JILA_AUDIO
#include <memory>
#include "SDL3/SDL_properties.h"
#include "SDL3_mixer/SDL_mixer.h"
#include "components/sdl3/audio.hpp"
#include "misc.hpp"
#include "proxy.hpp"
#include "components/sdl3/fio.hpp"
#include "tracy/Tracy.hpp"

typedef Proxy<MIX_Mixer> Mixer_Proxy;
typedef Proxy<MIX_Audio> Audio_Proxy;
typedef Proxy<MIX_Track> Track_Proxy;

typedef std::shared_ptr<Mixer_Proxy> Mixer;
typedef std::shared_ptr<Audio_Proxy> Audio;
typedef std::shared_ptr<Track_Proxy> Track;

namespace Jila {

Sint64 toSeconds(Sint64 ms) {
    ZoneScoped;
    if (ms == -1) {
        SDL_ClearError();
        return NULL;
    } else {
        return ms / 1000;
    }
}

struct AudioMeta {
    std::string_view name;
    std::string_view album;
    std::string_view artist;
    std::string_view copyright;
    Sint64 length; // seconds

    static void Bind(sol::state& state) {
        state.new_usertype<AudioMeta>("Jila_TrackMeta",
            "name", sol::readonly(&AudioMeta::name),
            "album", sol::readonly(&AudioMeta::album),
            "artist", sol::readonly(&AudioMeta::artist),
            "copyright", sol::readonly(&AudioMeta::copyright),
            "length", sol::readonly(&AudioMeta::length)
        );
    }

    static AudioMeta fromAudio(Audio audio) {
        ZoneScoped;
        SDL_PropertiesID propId = MIX_GetAudioProperties(audio->proxy);

        if (propId == 0) {
            return {"", "", "", "", 0};
        }
        
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

Mixer _SDL_InitMixer() {
    ZoneScoped;
    if (!MIX_Init()) {
        return NULL;
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
    ZoneScoped;
    MIX_DestroyMixer(mixer->proxy);
    MIX_Quit();
}

Audio _SDL_CreateAudio(Mixer mixer, std::variant<std::string_view, IOStream> path) {
    ZoneScoped;
    std::string_view* path_file = std::get_if<std::string_view>(&path);
    MIX_Audio* audio;

    if (path_file) {
        audio = MIX_LoadAudio(mixer->proxy, path_file->data(), false);
    } else {
        IOStream& io = std::get<IOStream>(path);

        audio = MIX_LoadAudio_IO(
            mixer->proxy,
            io->proxy,
            false,
            false
        );
    }

    if (!audio) return NULL;

    return MakeSafeMemory<Audio_Proxy>(
        new Audio_Proxy {audio},
        [](Audio_Proxy* proxy) {
            MIX_DestroyAudio(proxy->proxy);
        }
    );
}

Track _SDL_CreateTrack(Mixer mixer) {
    ZoneScoped;
    MIX_Track* track = MIX_CreateTrack(mixer->proxy);

    if (!track) return NULL;

    return MakeSafeMemory<Track_Proxy>(
        new Track_Proxy {track},
        [](Track_Proxy* proxy) {
            MIX_DestroyTrack(proxy->proxy);
        }
    );
}

bool _SDL_SetTrackAudio(Track track, Audio audio) {
    ZoneScoped;
    return MIX_SetTrackAudio(track->proxy, audio->proxy);
}

bool _SDL_PlayTrack(Track track) {
    ZoneScoped;
    return MIX_PlayTrack(track.get()->proxy, 0);
}

bool _SDL_StopTrack(Track track) {
    ZoneScoped;
    return MIX_StopTrack(track->proxy, 0);
}

bool _SDL_PauseTrack(Track track) {
    ZoneScoped;
    return MIX_PauseTrack(track->proxy);
}

bool _SDL_ResumeTrack(Track track) {
    ZoneScoped;
    return MIX_ResumeTrack(track->proxy);
}

bool _SDL_SetTrackPosition(Track track, Sint64 newPos) {
    ZoneScoped;
    return MIX_SetTrackPlaybackPosition(
        track->proxy,
        MIX_TrackMSToFrames(
            track->proxy,
            newPos * 1000
        )
    );
}

bool _SDL_SetMixerVolume(Mixer mixer, Uint8 volume) {
    ZoneScoped;
    return MIX_SetMasterGain(mixer->proxy, (float)volume / 100);
}

bool _SDL_TrackIsPlaying(Track track) {
    ZoneScoped;
    return MIX_TrackPlaying(track->proxy);
}

AudioMeta _SDL_GetAudioMeta(Audio audio) {
    ZoneScoped;
    return AudioMeta::fromAudio(audio);
}

Sint64 _SDL_GetTrackPosistion(Track track) {
    ZoneScoped;
    Sint64 pos = MIX_GetTrackPlaybackPosition(track.get()->proxy);

    if (pos == -1) {
        return pos;
    }

    return toSeconds(pos);
}

void bindSdlAudio(sol::state* state) {
    state -> set_function(
        "Jila_InitMixer",
        &_SDL_InitMixer
    );

    state -> set_function(
        "Jila_QuitMixer",
        &_SDL_QuitMixer
    );

    AudioMeta::Bind(*state);

    state -> set_function(
        "Jila_CreateAudio",
        &_SDL_CreateAudio
    );

    state -> set_function(
        "Jila_CreateTrack",
        &_SDL_CreateTrack
    );

    state -> set_function(
        "Jila_SetTrackAudio",
        &_SDL_SetTrackAudio
    );

    state -> set_function(
        "Jila_TrackIsPlaying",
        &_SDL_TrackIsPlaying
    );

    state -> set_function(
        "Jila_PlayTrack",
        &_SDL_PlayTrack
    );

    state -> set_function(
        "Jila_StopTrack",
        &_SDL_StopTrack
    );

    state -> set_function(
        "Jila_PauseTrack",
        &_SDL_PauseTrack
    );

    state -> set_function(
        "Jila_ResumeTrack",
        &_SDL_ResumeTrack
    );

    // TODO: implement track/audio hooks
    // Maybe in the future.

    state -> set_function(
        "Jila_SetTrackPosition",
        &_SDL_SetTrackPosition
    );

    state -> set_function(
        "Jila_SetMixerVolume",
        &_SDL_SetMixerVolume
    );

    state -> set_function(
        "Jila_GetAudioMeta",
        &_SDL_GetAudioMeta
    );

    state -> set_function(
        "Jila_GetTrackPosition",
        &_SDL_GetTrackPosistion
    );
}

}
#endif