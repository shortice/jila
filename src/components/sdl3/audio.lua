--- @meta music

--- Track metdata.
--- @class Jila_TrackMeta
--- @field name string Track name [readonly]
--- @field album string Track album [readonly]
--- @field artist string Track author [readonly]
--- @field copyright string Copyright [readonly]
--- @field length integer Track length [readonly]
Jila_TrackMeta = {}

--- @class _Mixer
_Mixer = {}

--- @class _Audio
_Audio = {}

--- @class _Track
_Track = {}

--- Initialize Audio system. Return nil when error.
---
--- @return _Mixer?
--- @overload fun(channels: number, freq: number): _Mixer?
---
--- @see Jila_GetError for read error.
---
--- @nodiscard
function Jila_InitMixer() end

--- Deinit audio system.
---
--- @param mixer _Mixer
function Jila_QuitMixer(mixer) end

--- Loading audio.
---
--- @param mixer _Mixer
--- @param path string|Jila_IO Path of the music file. If you use Jila_IO, this IO is auto close after execute this function.
--- @return _Audio? Audio or nil when error.
---
--- @see Jila_GetError for read error.
---
--- @nodiscard
function Jila_CreateAudio(mixer, path) end

--- Create audio track.
---
--- @param mixer _Mixer
---
--- @return _Track? Track or nil when error.
---
--- @see Jila_GetError for read error.
--- 
--- @nodiscard
function Jila_CreateTrack(mixer) end

--- @param track _Track
--- @param audio _Audio
--- 
--- @return boolean boolean false when error.
--- 
--- @see Jila_GetError for read error.
function Jila_SetTrackAudio(track, audio) end

--- @param track _Track
---
--- @return boolean boolean false when error.
--- 
--- @see Jila_GetError for read error.
function Jila_PlayTrack(track) end

--- @param track _Track
---
--- @return boolean boolean false when error.
--- 
--- @see Jila_GetError for read error.
function Jila_StopTrack(track) end

--- @param track _Track
---
--- @return boolean boolean false when error.
--- 
--- @see Jila_GetError for read error.
function Jila_PauseTrack(track) end

--- @param track _Track
---
--- @return boolean boolean false when error.
--- 
--- @see Jila_GetError for read error.
function Jila_ResumeTrack(track) end

--- @param track _Track
--- @param newPos number New track position
--- 
--- @return boolean boolean false when error.
--- 
--- @see Jila_GetError for read error.
function Jila_SetTrackPosition(track, newPos) end

--- @param mixer _Mixer
--- @param volume number Volume from 0 to 255.
--- @return boolean boolean false when error.
--- 
--- @see Jila_GetError for read error.
function Jila_SetMixerVolume(mixer, volume) end

--- @param track _Track
--- @return boolean
function Jila_TrackIsPlaying(track) end

--- @param audio _Audio
--- @return Jila_TrackMeta MusicMeta
function Jila_GetAudioMeta(audio) end

--- @param track _Track
--- @return number number
function Jila_GetTrackPosistion(track) end
