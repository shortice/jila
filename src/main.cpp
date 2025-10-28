#include "SDL3/SDL_init.h"
#define SDL_MAIN_USE_CALLBACKS

#include "SDL3/SDL_main.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_timer.h"
#include "engine/runtime.hpp"

#include "misc.hpp"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "external/font.hpp"
#include "external/fa_brands.hpp"
#include "external/fa_regular.hpp"
#include "external/fa_solid.hpp"

#include "engine/logger.hpp"
#include "engine/component.hpp"
#include "misc.hpp"


#define ICON_MIN_FA 0xe005
#define ICON_MAX_16_FA 0xf8ff
#define ICON_MAX_FA 0xf8ff

#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

const char* getScriptsLocation(char** argv) {
    argv++; // Skip executable path

    if (*argv) {
        return *argv;
    } else {
        return "./app";
    }
}

void SetupImGui(
    float mainScale,
    SDL_Window* window,
    SDL_Renderer* renderer
) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsLight();

    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(mainScale);
    style.FontScaleDpi = mainScale;
    style.FontScaleMain = 1.5f;

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    io.Fonts->Clear();
    io.Fonts -> AddFontFromMemoryCompressedTTF(
        JetBrainsMono_compressed_data,
        JetBrainsMono_compressed_size,
        13,
        NULL,
        io.Fonts -> GetGlyphRangesCyrillic()
    );

    ImFontConfig config;
    config.MergeMode = true;
    config.GlyphMinAdvanceX = 13.0f;

    io.Fonts->AddFontFromMemoryCompressedTTF(
        fa_brands_compressed_data,
        fa_brands_compressed_size,
        13.0f,
        &config
    );

    io.Fonts->AddFontFromMemoryCompressedTTF(
        fa_regular_compressed_data,
        fa_regular_compressed_size,
        13.0f,
        &config
    );

    io.Fonts->AddFontFromMemoryCompressedTTF(
        fa_solid_compressed_data,
        fa_solid_compressed_size,
        13.0f,
        &config
    );

    io.ConfigFlags |= ImGuiConfigFlags_IsTouchScreen;
    io.IniFilename = nullptr;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    Jila::Logger::named("Runtime").info("Starting...");

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        Jila::CriticalError("SDL_Init");
    }

    float main_scale = SDL_GetDisplayContentScale(
        SDL_GetPrimaryDisplay()
    );

    SDL_WindowFlags window_flags = (
        SDL_WINDOW_RESIZABLE |
        SDL_WINDOW_HIDDEN |
        SDL_WINDOW_HIGH_PIXEL_DENSITY
    );

    SDL_Window* window = SDL_CreateWindow(
        "Jila Engine",
        (int)(1280 * main_scale),
        (int)(720 * main_scale),
        window_flags
    );

    if(!window) Jila::CriticalError("SDL_CreateWindow");

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderVSync(renderer, 1);

    if(!renderer) Jila::CriticalError("SDL_CreateRenderer");;

    #ifndef __ANDROID__
    SDL_SetWindowPosition(
        window,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED
    );
    #endif

    SetupImGui(main_scale, window, renderer);

    Jila::AppState* state = new Jila::AppState {
        window,
        renderer,
        Jila::InitRuntime(getScriptsLocation(argv)),
        &ImGui::GetIO()
    };

    Jila::SetState(state);
    Jila::loadFiles(state -> state);

    SDL_ShowWindow(state->window);
    (*appstate) = state;

    Jila::LuaModule* module = Jila::LuaModule::GetModule("main");

    if (!module) return SDL_APP_CONTINUE;
    if (!module -> BeginMainLoop) return SDL_APP_CONTINUE;

    module->BeginMainLoop();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    Jila::LuaModule* module = Jila::LuaModule::GetModule("main");
    Jila::AppState* state = (Jila::AppState*)appstate;

    if (SDL_GetWindowFlags(state->window) & SDL_WINDOW_MINIMIZED) {
        SDL_Delay(10);
        return SDL_APP_CONTINUE;
    }

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    if (module) {
        auto result = module->Render(SDL_GetTicks());

        // TODO: Improve error messages?
        if (!result.valid()) {
            sol::error err = result;

            ImGui::SetTooltip("%s %s\n",
                "Error when render!\n\n",
                err.what()
            );

            ImGui::End();
        }
    }

    ImGui::Render();
    SDL_SetRenderScale(
        state->renderer,
        state->io -> DisplayFramebufferScale.x,
        state->io -> DisplayFramebufferScale.y
    );
    SDL_RenderClear(state->renderer);
    ImGui_ImplSDLRenderer3_RenderDrawData(
        ImGui::GetDrawData(),
        state->renderer
    );
    SDL_RenderPresent(state->renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    ImGui_ImplSDL3_ProcessEvent(event);

    Jila::LuaModule* module = Jila::LuaModule::GetModule("main");
    SDL_Event& _event = *event;

    if (module) module->Event(_event); // TODO: TryCall func?

    if (event->type == SDL_EVENT_USER) {
        if (event->user.code == 1001) {
            Jila::ReloadAll();
        }
    }

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    Jila::QuitRuntime();

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(
        ((Jila::AppState*)appstate)->renderer
    );
    SDL_DestroyWindow(
        ((Jila::AppState*)appstate)->window
    );
    SDL_Quit();

    delete (Jila::AppState*)appstate;
}
