#pragma once

#include "engine/component.hpp"

namespace Jila {

    template<typename T>
    struct _Property {
    
    T* data;
    
    _Property(T value) {
        data = new T;
        *data = value;
    }
    
    T Value() {
        return *data;
    }
    
    void SetValue(T value) {
        *data = value;
    }
    
    ~_Property() {
        delete data;
    }
    
};
    
struct CharProperty {
    
    char* str;
    size_t size;
    
    CharProperty(size_t size);
    
    CharProperty(std::string _str);
    
    inline std::string toStr() const;
    
    ~CharProperty();
    
};
    
typedef _Property<int>     IntProperty;
typedef _Property<float>   FloatProperty;
// typedef _Property<double>  DoubleProperty;
// typedef _Property<Uint64>  Int64Property;
typedef _Property<bool>    BoolProperty;
    
template<typename T>
void BindProperty(std::string name, sol::state& state) {
    state.new_usertype<
        _Property<T>
    >(
    name+ "Property",
        sol::constructors<_Property<T>(T)>(),
        "value", sol::property(
          &_Property<T>::Value,
          &_Property<T>::SetValue
        )
    );
}

namespace PropertiesComponent {

bool Init(sol::state* state);
void Quit(sol::state* state);

}

static LuaComponent ComponentProperties {
    "Properties",
    "Shortice",
    PropertiesComponent::Init,
    PropertiesComponent::Quit
};

}
