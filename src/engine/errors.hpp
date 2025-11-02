#pragma once

#include "sol/sol.hpp"
#include <string>

namespace Jila {

void CriticalError(std::string func);
void RenderError(sol::protected_function_result& result);

}
