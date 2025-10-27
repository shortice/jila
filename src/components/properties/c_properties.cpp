#include "components/properties/c_properties.hpp"

namespace Jila {

CharProperty::CharProperty(size_t size) : size(size) {
  str = (char *)calloc(1, size * sizeof(char));
}

CharProperty::CharProperty(std::string _str) : size(_str.size()) {
  str = (char *)calloc(1, size * sizeof(size));
  strcpy(str, _str.data());
}

std::string CharProperty::toStr() const { 
    return std::string(str); 
}

CharProperty::~CharProperty() { 
    free(str); 
}

namespace PropertiesComponent {

bool Init(sol::state *state) {
    BindProperty<int>("Int", *state);
    BindProperty<float>("Float", *state);
    BindProperty<bool>("Bool", *state);

    state->new_usertype<CharProperty>(
	    "CharProperty",
        sol::constructors<
            CharProperty(size_t),
            CharProperty(std::string)
        >(),
	    "str", sol::property(&CharProperty::toStr)
	);

    return true;
}

void Quit(sol::state *state) {}

} // namespace PropertiesComponent

} // namespace Jila