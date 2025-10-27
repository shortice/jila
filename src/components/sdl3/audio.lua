--- @meta music

--- Track metdata.
--- @class AudioMeta
--- @field name string Track name.
--- @field album string Track album.
--- @field artist string Track author.
--- @field copyright string Copyright.
--- @field lenght integer Track lenght.
AudioMeta = {}

--- @class _Mixer
_Mixer = {}

--- @class _Audio
_Audio = {}

--- @class _Track
_Track = {}

--- Initialize Audio system. Return nil when error.
---
--- @return _Mixer|nil
--- @overload fun(channels: number, freq: number): _Mixer
---
--- @nodiscard
function SDL_InitMixer() end

--- Deinit audio system.
---
--- @param mixer _Mixer
function SDL_QuitMixer(mixer) end

--- Loading audio.
---
--- @param mixer _Mixer
--- @param path string Path of the music file.
--- @return _Audio|nil Audio or nil when error.
---
--- @nodiscard
function SDL_CreateAudio(mixer, path) end

--- Create audio track.
---
--- @param mixer _Mixer
---
--- @return _Track|nil
function SDL_CreateTrack(mixer) end

--- @param track _Track
--- @param audio _Audio
function SDL_SetTrackAudio(track, audio) end

--- @param track _Track
---
--- @return boolean
function SDL_PlayTrack(track) end

--- @param track _Track
---
--- @return boolean
function SDL_StopTrack(track) end

--- @param track _Track
---
--- @return boolean
function SDL_PauseTrack(track) end

--- @param track _Track
---
--- @return boolean
function SDL_ResumeTrack(track) end

--- @param track _Track
--- @param newPos number New track position
--- @return boolean boolean
function SDL_SetTrackPosition(track, newPos) end

--- @param mixer _Mixer
--- @param volume number Volume from 0 to 255.
--- @return number number
function SDL_SetMixerVolume(mixer, volume) end

--- @param track _Track
--- @return boolean
function SDL_TrackIsPlaying(track) end

--- @param audio _Audio
--- @return AudioMeta MusicMeta
function SDL_GetAudioMeta(audio) end

--- @param track _Track
--- @return number number
function SDL_GetTrackPosistion(track) end
