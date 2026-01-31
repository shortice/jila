---
--- @type Module
local M = {
    name = "sdl",
    version = 0.1
}

function M.Begin()
    Scope.CurrentFile = Create_Char_Property()
    Scope.Audio = nil
    Scope.Mixer = Jila_InitMixer()
    Scope.Track = Jila_CreateTrack(Scope.Mixer)
    Scope.Volume = Create_Int_Property(10)
end

function M.End()
    Jila_QuitMixer(Scope.Mixer)
end

function M.Render(time)
    ImText("Current file: " .. Scope.CurrentFile.str)

    if ImButton("Open file dialog") then
        Jila_OpenFileDialog({"mp3;opus"})
    end

    if Scope.Audio == nil then
        return
    end

    if ImButton("Play") then
        Jila_PlayTrack(Scope.Track)
    end

    if ImButton("Pause") then
        Jila_PauseTrack(Scope.Track)
    end

    ImSameLine()

    if ImButton("Resume") then
        Jila_ResumeTrack(Scope.Track)
    end

    if ImSliderInt("Volume: ", Scope.Volume, 0, 100) then
        Jila_SetMixerVolume(Scope.Mixer, Scope.Volume.value)
    end
end

function M.Event(event)
    if (event.type == Jila_EventType.Jila_EVENT_USER) then
        if (event.user.code ~= 1005) then return end

        local dialog = Jila_GetDialogState(event.user)

        Scope.CurrentFile.str = dialog.selected_files[1]

        if Scope.Audio ~= nil then
            Jila_StopTrack(Scope.Track)
        end

        local io = Jila_IO_Open(Scope.CurrentFile.str, "r")

        if io == nil then
            return
        end

        Scope.Audio = Jila_CreateAudio(Scope.Mixer, io)
        Jila_SetTrackAudio(Scope.Track, Scope.Audio)
        Jila_SetMixerVolume(Scope.Mixer, Scope.Volume.value)
    end
end

return M -- Required!!!

