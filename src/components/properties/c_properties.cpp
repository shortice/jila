#include "components/properties/c_properties.hpp"

namespace Jila {

CharProperty::CharProperty() {} 

CharProperty::CharProperty(std::string_view _str) {
    str = _str;
}
    
std::string_view CharProperty::toStr() const {
    return str;
}

namespace PropertiesComponent {

bool Init(sol::state *state) {
    BindProperty<int>("Int", *state);
    BindProperty<float>("Float", *state);
    BindProperty<bool>("Bool", *state);

    state->set_function("Create_Char_Property",
        sol::overload(
            []() {
                return CharProperty();
            },
            [](std::string_view str) { 
            return CharProperty(str); 
            }
        )
    );

    state->new_usertype<CharProperty>(
	    "CharProperty",
	    "str", sol::property(&CharProperty::toStr)
	);

    return true;
}

void Quit(sol::state *state) {}

} // namespace PropertiesComponent

} // namespace Jila