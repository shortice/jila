#include "SDL3/SDL_error.h"
#include "imgui.h"
#include "errors.hpp"
#include "engine/logger.hpp"

namespace Jila {

void CriticalError(std::string func) {
    Jila::Logger::named("Runtime").error(
        std::string("Error when calling %s: %s\n") +
        func +
        SDL_GetError()
    );
    std::exit(-1);
}

void RenderError(sol::protected_function_result& result) {
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

}
