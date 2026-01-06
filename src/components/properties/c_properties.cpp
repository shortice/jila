#include "components/properties/c_properties.hpp"

namespace Jila {

CharProperty::CharProperty(size_t size) : size(size) {
    str = std::string(size, '\0');
}

// Hm... I know this don't supports UTF16-32 symbols... but
// i don't have any problems why i need use this symbols at this moment.
CharProperty::CharProperty(std::string_view _str) : size(_str.size()) {
    str = _str;
}

std::string_view CharProperty::toStr() const { 
    return std::string_view(str); 
}

namespace PropertiesComponent {

bool Init(sol::state *state) {
    BindProperty<int>("Int", *state);
    BindProperty<float>("Float", *state);
    BindProperty<bool>("Bool", *state);

    state->set_function("Create_Char_Property", sol::overload(
        [](size_t size) { 
            return CharProperty(size); 
        },
        [](std::string str) { 
            return CharProperty(str); 
        }
    ));

    state->new_usertype<CharProperty>(
	    "CharProperty",
	    "str", sol::property(&CharProperty::toStr)
	);

    return true;
}

void Quit(sol::state *state) {}

} // namespace PropertiesComponent

} // namespace Jila