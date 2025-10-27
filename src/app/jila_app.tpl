#include "app/jila_app.hpp"

namespace LuaApplication {

std::vector<const char*> modules {
{{modules}}
};

std::vector<const char*> GetCode() {
    return modules;
}

}
